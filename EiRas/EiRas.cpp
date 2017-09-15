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

bool enabelMerge;

vec4 alphaMerge(vec4 _background, vec4 _foreground);


void initEi()
{
    enabelMerge = false;
    
    frame = new vec4[g_width * g_height];
    depthBuffer = new float[g_width * g_height];
    
    for(int i =0;i<g_width * g_height;i++)
        depthBuffer[i] = MAXFLOAT;
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
    float x = p.x;
    float y = p.y;
    
    if(coordinate2frame(x, y))
    {
        
        if(!enabelMerge && depthBuffer[(int)y*g_width + (int)x] < z)
            return;
        if(enabelMerge)
            frame[(int)y*g_width + (int)x] = alphaMerge(frame[(int)y*g_width + (int)x], color);
        else
            frame[(int)y*g_width + (int)x] = color;
        
        if(depthBuffer[(int)y*g_width + (int)x] < z)
            depthBuffer[(int)y*g_width + (int)x] = z;
        
    }
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
    x = x * (float)g_width/2.0;
    y = -y * (float)g_height/2.0;
    x += g_width/2.0;
    y += g_height/2.0;
    
    if(x >= 0 && y>=0 && x<g_width && y<g_height)
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




void setProjMatrix(matrix4X4 mat)
{
    mat4X4Proj = mat;
}

vec4 Ei_Proj(vec4 point)
{
    point.a =1;
    return matrix4X4::mul(mat4X4Proj, point);
}

void matMatrix44PerspectiveFovLH(matrix4X4 &mat, const float fov, const float aspect, const float ZNear, const float ZFar )
{
    const float fViewSpaceHeight = 1.0f / tanf( fov * 0.5f );
    const float fViewSpaceWidth = fViewSpaceHeight / aspect ;
    
    mat.m11 = fViewSpaceWidth; mat.m12 = 0.0f; mat.m13 = 0.0f; mat.m14 = 0.0f;
    mat.m21 = 0.0f; mat.m22 = fViewSpaceHeight; mat.m23 = 0.0f; mat.m24 = 0.0f;
    mat.m31 = 0.0f; mat.m32 = 0.0f; mat.m33 = ZFar / ( ZFar - ZNear ); mat.m34 = -ZNear * ZFar / ( ZFar - ZNear );
    mat.m41 = 0.0f; mat.m42 = 0.0f; mat.m43 = 1.0f; mat.m44 = 0.0f;
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
