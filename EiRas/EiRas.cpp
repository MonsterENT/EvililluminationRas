//
//  EiRas.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiRas.hpp"
#include <stdio.h>

const vec2 MSAAPosMatrix[]= {
    vec2(-1 , -1), vec2(1 , -1),
    vec2(-1 , +1), vec2(+1 , +1)
};

const vec2 MSAA16XSampleMatrix[]= {
    vec2(-1 , -1), vec2(1, -1),
    vec2(-1 , +1), vec2(+1 , +1)
};

const vec2 MSAA4XSampleMatrix[]= {
    vec2(0 , 0), vec2(1 , 0),
    vec2(0 , +1), vec2(+1 , +1)
};

vec2_Int frameSize;
vec2 dxy;

void EiRas::initEi(vec2_Int _frameSize)
{
    enabelMerge = true;
    
    frameSize = _frameSize;
    dxy = vec2(1.f / (float)frameSize.x, 1.f / (float)frameSize.y);
    
    frame = new vec4[frameSize.x * frameSize.y * MSAA4X];
    depthBuffer = new float[frameSize.x * MSAA4X * frameSize.y];
    
    for(int i = 0; i < frameSize.x * frameSize.y * MSAA4X; i++)
    {
        depthBuffer[i] = MAXFLOAT;
    }
    
    MSAASqrt = sqrt(MSAA4X);
    NDC2FrameWidth = frameSize.x * MSAASqrt;
    NDC2FrameHeight = frameSize.y * MSAASqrt;
}



void EiRas::setPixel(int x,int y,vec4 color)
{
    if(coordinate2frame(x, y))
    {
        if(enabelMerge)
        {
            frame[y * getFrameSize().x + x] = alphaMerge(frame[y * getFrameSize().x + x], color);
        }
        else
        {
            frame[y * getFrameSize().x + x] = color;
        }
    }
}

void EiRas::setPixel(vec2 p,vec4 color)
{
    int x = p.x;
    int y = p.y;
    
    setPixel(x, y, color);
}

void EiRas::setPixelWithDepthTest(vec2 p,float z,vec4 color)
{
    vec2* subPixel = new vec2[MSAA4X];
    
    int Level = MSAA4X / 4;

    for(int i = 0; i < Level; i++)
    {
        for(int index = 0; index < 4; index++)
        {
            subPixel[index + i * 4].x = p.x + MSAAPosMatrix[index].x * (i + 1) * (float)WidthGapMSAA4X / 2.0;
            subPixel[index + i * 4].y = p.y + MSAAPosMatrix[index].y * (i + 1) * (float)HeightGapMSAA4X / 2.0;
        }
    }
    
    for(int i = 0; i < MSAA4X; i++)
    {
        if(coordinate2frame(subPixel[i].x, subPixel[i].y))
        {
            int x = subPixel[i].x;
            int y = subPixel[i].y;
            
            if(depthBuffer[y * NDC2FrameWidth + x] < z)
            {
                continue;
            }
            
            depthBuffer[y * NDC2FrameWidth + x] = z;
            
            if(enabelMerge)
            {
                frame[y * NDC2FrameWidth + x] = alphaMerge(frame[y * NDC2FrameWidth + x], color);
            }
            else
            {
                frame[y * NDC2FrameWidth + x] = color;
            }
        }
    }
}

void EiRas::presentToFile(const char* fileName)
{
    FILE* f = NULL;
    f = fopen(fileName, "w");
    fprintf(f, "P3\n%d %d\n%d\n", getFrameSize().x, getFrameSize().y, 255);
    
    for(int y = 0; y < getFrameSize().y; y++)
    {
        for(int x = 0; x < getFrameSize().x; x++)
        {
            vec4 MixedColor = vec4(0, 0, 0, 0);
            
            int Level = MSAA4X / 4;
            
            int sampledCount = 0;
            
            for(int i = 0;i < Level; i++)
            {
                for(int index = 0; index < 4; index++)
                {
                    const vec2* SampleMatrix;
                    if(Level == 1)
                    {
                        SampleMatrix = MSAA4XSampleMatrix;
                    }
                    else
                    {
                        SampleMatrix = MSAA16XSampleMatrix;
                    }
                    
                    if(sampleFrame(x * MSAASqrt + (int)(SampleMatrix[index].x) * (i + 1), y * MSAASqrt + (int)(SampleMatrix[index].y) * (i + 1), MixedColor))
                    {
                        sampledCount ++;
                    }
                }
            }
            if(sampledCount != 0)
            {
                MixedColor /= (float)sampledCount;
            }
            
            fprintf(f,"%d %d %d ", EiMath_Q::toInt(MixedColor.r), EiMath_Q::toInt(MixedColor.g), EiMath_Q::toInt(MixedColor.b));
        }
    }
    fclose(f);
}

bool EiRas::sampleFrame(int x,int y,vec4 &Color)
{
    if(x >= 0 && y >= 0 && x < NDC2FrameWidth && y < NDC2FrameHeight)
    {
        Color += frame[y * NDC2FrameWidth + x];
        return true;
    }
    return false;
}

vec4 EiRas::alphaMerge(vec4 _background, vec4 _foreground)
{
    vec4 color;
    color.r = _foreground.a * _foreground.r + (1.0 -_foreground.a) * _background.r;
    color.g = _foreground.a * _foreground.g + (1.0 -_foreground.a) * _background.g;
    color.b = _foreground.a * _foreground.b + (1.0 -_foreground.a) * _background.b;
    color.a = 1.0;
    
    return color;
}

bool EiRas::coordinate2frame(int &x, int &y)
{
    x = x * (float)NDC2FrameWidth / 2.0;
    y = -y * (float)NDC2FrameHeight / 2.0;
    x += (float)NDC2FrameWidth / 2.0;
    y += (float)NDC2FrameHeight / 2.0;
    
    if(x >= 0 && y >= 0 && x < NDC2FrameWidth && y < NDC2FrameHeight)
    {
        return true;
    }
    return false;
}

bool EiRas::coordinate2frame(float &x, float &y)
{
    x = x * (float)NDC2FrameWidth / 2.0;
    y = -y * (float)NDC2FrameHeight / 2.0;
    x += (float)NDC2FrameWidth / 2.0;
    y += (float)NDC2FrameHeight / 2.0;
    
    if(x >= 0 && y >= 0 && x < NDC2FrameWidth && y < NDC2FrameHeight)
    {
        return true;
    }
    return false;
}

vec4* EiRas::getFrameBuffer()
{
    return frame;
}

float* EiRas::getDepthBuffer()
{
    return depthBuffer;
}
