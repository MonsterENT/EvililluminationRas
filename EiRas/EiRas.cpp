//
//  EiRas.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "EiRas.hpp"

vec4* frame =  nullptr;

float* depthBuffer = nullptr;

EiLight* g_EiLight = nullptr;

matrix4X4 mat4X4Proj;
matrix4X4 *mat4X4Camera;

bool enabelMerge;

vec4 alphaMerge(vec4 _background, vec4 _foreground);

bool sampleFrame(int x,int y,vec4 &Color);

vec2 MSAAPosMatrix[]= {
    vec2(-1,-1),vec2(1,-1),
    vec2(-1,+1),vec2(+1,+1)
};

vec2 MSAA16XSampleMatrix[]= {
    vec2(-1,-1),vec2(1,-1),
    vec2(-1,+1),vec2(+1,+1)
};
vec2 MSAA4XSampleMatrix[]= {
    vec2(0,0),vec2(1,0),
    vec2(0,+1),vec2(+1,+1)
};

int NDC2FrameWidth,NDC2FrameHeight;
int MSAASqrt;

void initEi()
{
    enabelMerge = false;
    
    frame = new vec4[g_width * g_height * MSAA4X];
    depthBuffer = new float[g_width * MSAA4X * g_height];
    
    for(int i =0;i<g_width* g_height*MSAA4X;i++)
        depthBuffer[i] = MAXFLOAT;
    
    MSAASqrt = sqrt(MSAA4X);
    NDC2FrameWidth = g_width * MSAASqrt;
    NDC2FrameHeight = g_height * MSAASqrt;
}



void setPixel(int x,int y,vec4 color)
{
    if(coordinate2frame(x, y))
    {
        if(enabelMerge)
            frame[y*g_width + x] = alphaMerge(frame[y*g_width + x], color);
        else
            frame[y*g_width + x] = color;
    }
    
    
}

void setPixel(vec2 p,vec4 color)
{
    int x = p.x;
    int y = p.y;
    
    if(coordinate2frame(x, y))
    {
        if(enabelMerge)
            frame[y*g_width + x] = alphaMerge(frame[y*g_width + x], color);
        else
            frame[y*g_width + x] = color;
    }
}

void setPixelWithDepthTest(vec2 p,float z,vec4 color)
{
    
    
    vec2* subPixel = new vec2[MSAA4X];
    
    int Level = MSAA4X / 4;
    
    
    
    for(int i =0;i<Level;i++)
    {
        for(int index = 0;index<4;index++)
        {
            subPixel[index + i*4].x = p.x + MSAAPosMatrix[index].x * (i+1) * (float)WidthGapMSAA4X/2.0;
            subPixel[index + i*4].y = p.y + MSAAPosMatrix[index].y * (i+1) * (float)HeightGapMSAA4X/2.0;
        }
    }
    
    for(int i =0;i < MSAA4X;i++)
        if(coordinate2frame(subPixel[i].x, subPixel[i].y))
        {
            
            int x = subPixel[i].x;
            int y = subPixel[i].y;
            
            
            if(depthBuffer[y*NDC2FrameWidth + x] < z)
                return;
            if(enabelMerge)
                frame[y*NDC2FrameWidth + x] = alphaMerge(frame[y*NDC2FrameWidth + x], color);
            else
                frame[y * NDC2FrameWidth + x] = color;
            
//            if(depthBuffer[y*NDC2FrameWidth + x] < z)
                depthBuffer[y*NDC2FrameWidth + x] = z;
            
        }
}

void present()
{
    
    char filename[50];
    //    sprintf(filename,"EiRasDepth.ppm");
    FILE *f;
    //    fprintf(f, "P3\n%d %d\n%d\n", g_width, g_height, 255);
    //    for (int i=0; i< g_width * g_height; i++)
    //        fprintf(f,"%d %d %d ", toInt(double(getDepthBuffer()[i])),toInt(double(getDepthBuffer()[i])), toInt(double(getDepthBuffer()[i])));
    //    fclose(f);
    
    
    sprintf(filename,"EiRas.ppm");
    f = fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", g_width, g_height, 255);
    
    
    for (int y=0; y< g_height; y++)
    {
        for(int x =0;x<g_width;x++)
        {
            vec4 MixedColor = vec4(0,0,0,0);
            
            int Level = MSAA4X / 4;
            
            int sampledCount = 0;
            
            for(int i =0;i<Level;i++)
            {
                for(int index = 0;index < 4;index++)
                {
                    vec2* SampleMatrix;
                    if(Level == 1)
                        SampleMatrix = MSAA4XSampleMatrix;
                    else
                        SampleMatrix = MSAA16XSampleMatrix;
                    
                    if(sampleFrame(x * MSAASqrt + (int)(SampleMatrix[index].x)* (i+1), y * MSAASqrt + (int)(SampleMatrix[index].y) * (i+1), MixedColor))
                        sampledCount ++;
                }
            }
            if(sampledCount!=0)
                MixedColor /= (float)sampledCount;
            
            fprintf(f,"%d %d %d ", toInt(MixedColor.r),toInt(MixedColor.g), toInt(MixedColor.b));
            //            fprintf(f,"%d %d %d ", toInt(frame[y*NDC2FrameWidth +x].r),toInt(frame[y*NDC2FrameWidth +x].g), toInt(frame[y*NDC2FrameWidth +x].b));
        }
    }
    
    
    //    for (int i=0; i< g_width*4 * g_height; i++)
    //        fprintf(f,"%d %d %d ", toInt(getFrameBuffer()[i].r),toInt(getFrameBuffer()[i].g), toInt(getFrameBuffer()[i].b));
    fclose(f);
}

bool sampleFrame(int x,int y,vec4 &Color)
{
    if(x >= 0 && y>=0 && x< NDC2FrameWidth && y< NDC2FrameHeight)
    {
        Color += frame[y * NDC2FrameWidth + x];
        return true;
    }
    return false;
}

vec4 alphaMerge(vec4 _background, vec4 _foreground)
{
    vec4 color;
    color.r = _foreground.a * _foreground.r + (1.0-_foreground.a) * _background.r;
    color.g = _foreground.a * _foreground.g + (1.0-_foreground.a) * _background.g;
    color.b = _foreground.a * _foreground.b + (1.0-_foreground.a) * _background.b;
    color.a = 1.0;
    
    return color;
}

bool coordinate2frame(int &x, int &y)
{
    y = -y;
    x += g_width/2;
    y += g_height/2;
    
    if(x >= 0 && y>=0 && x<g_width && y<g_height)
    {
        return true;
    }
    return false;
}

bool coordinate2frame(float &x, float &y)
{
    x = x * (float)NDC2FrameWidth/2.0;
    y = -y * (float)NDC2FrameHeight/2.0;
    x += (float)NDC2FrameWidth/2.0;
    y += (float)NDC2FrameHeight/2.0;
    
    if(x >= 0 && y>=0 && x< NDC2FrameWidth && y< NDC2FrameHeight)
    {
        return true;
    }
    return false;
}




vec4* getFrameBuffer()
{
    return frame;
}

float* getDepthBuffer()
{
    return depthBuffer;
}


void setCamera(EiCamera* Camera)
{
    mat4X4Camera = Camera->getCameraMatrix();
    setProjMatrix(*Camera->getProjMatrix());
}

void setProjMatrix(matrix4X4 mat)
{
    mat4X4Proj = mat;
}

vec4 Ei_Proj(vec4 point)
{
    point.a =1;
    vec3 pos = matrix4X4::mul(*mat4X4Camera, point);
    return matrix4X4::mul(mat4X4Proj, pos);
}


void setEiLight(EiLight* _EiLight)
{
    g_EiLight = _EiLight;
}

EiLight* getEiLight()
{
    return g_EiLight;
}

void enableAlphaMerge()
{
    enabelMerge = true;
}
void disableAlphaMerge()
{
    enabelMerge = false;
}
