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
//
//const vec2 MSAA16XSampleMatrix[]= {
//    vec2(-1 , -1), vec2(1, -1),
//    vec2(-1 , +1), vec2(+1 , +1)
//};
//
//const vec2 MSAA4XSampleMatrix[]= {
//    vec2(0 , 0), vec2(1 , 0),
//    vec2(0 , +1), vec2(+1 , +1)
//};

vec2_Int frameSize;
vec2 dxy;

void EiRas::initEi(vec2_Int _frameSize)
{
    enableMerge = true;
    
    frameSize = _frameSize;
    dxy = vec2(1.f / (float)frameSize.x, 1.f / (float)frameSize.y);
    
    frame = new vec4[frameSize.x * frameSize.y];
    depthBuffer = new float[frameSize.x * frameSize.y];
    
    for(int i = 0; i < frameSize.x * frameSize.y; i++)
    {
        depthBuffer[i] = MAXFLOAT;
    }
    
    NDC2FrameWidth = frameSize.x;
    NDC2FrameHeight = frameSize.y;
    
    commandBuffer = new EiCommandBuffer(50, this);
}



void EiRas::setPixel(int x,int y,vec4 color)
{
    if(coordinate2frame(x, y))
    {
        if(enableMerge)
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
    static vec2* subPixel = new vec2[4];
    
    
    for(int index = 0; index < 4; index++)
    {
        subPixel[index].x = p.x + MSAAPosMatrix[index].x * dxy.x;
        subPixel[index].y = p.y + MSAAPosMatrix[index].y * dxy.y;
    }
    
    for(int i = 0; i < 4; i++)
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
            
            if(enableMerge)
            {
                frame[y * NDC2FrameWidth + x] = alphaMerge(frame[y * NDC2FrameWidth + x], color / 4.0);
            }
            else
            {
                frame[y * NDC2FrameWidth + x] = color / 4.0;
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
            
            int sampledCount = 0;
            for(int index = 0; index < 4; index++)
            {
                const vec2* SampleMatrix = MSAAPosMatrix;
                
                if(sampleFrame(x  + (int)(SampleMatrix[index].x) * dxy.x, y + (int)(SampleMatrix[index].y) * dxy.y , MixedColor))
                {
                    sampledCount ++;
                }
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

void EiRas::clearFrameAndDepth(vec4 clearColor)
{
    EiCommand* command = new EiCommand;
    //    //pipe line state
    //    vec4 clearColor;
    //    bool isClearFrame = false;
    //    bool isPresent = false;
    //
    //    bool enableMerge;
    //    EiPrimitive** primitives;
    //    unsigned int primitiveCount;
    //    bool* destoryFlag;
    command->clearColor = clearColor;
    command->isClearFrame = true;
    commandBuffer->addCommand(command);
}

void EiRas::drawPrimitives(EiPrimitive** primitives, int count)
{
    EiCommand* command = new EiCommand;
    
    EiPrimitive** copy_array = new EiPrimitive*[count];
    for(int i = 0; i < count; i++)
    {
        copy_array[i] = primitives[i]->copy();
    }
    
    command->primitives = copy_array;
    command->primitiveCount = count;
    command->enableMerge = enableMerge;
    command->destoryPrimitiveArray = true;
    commandBuffer->addCommand(command);
}

void EiRas::drawPrimitive(EiPrimitive* primitive)
{
    EiPrimitive** array = new EiPrimitive*[1];
    array[0] = primitive->copy();
    EiCommand* command = new EiCommand;
    command->primitives = array;
    command->primitiveCount = 1;
    command->enableMerge = enableMerge;
    command->destoryPrimitiveArray = true;
    commandBuffer->addCommand(command);
}

void EiRas::present()
{
    EiCommand* command = new EiCommand;
    command->isPresent = true;
    commandBuffer->addCommand(command);
}

void EiRas::_clearFrameAndDepth(vec4& clearColor)
{
    for(int i = 0; i < frameSize.x * frameSize.y; i++)
    {
        frame[i] = clearColor;
        depthBuffer[i] = MAXFLOAT;
    }
}

void EiRas::_drawPrimitives(EiPrimitive** primitives, int count)
{
    for(int i = 0; i < count; i++)
    {
        EiPrimitive* primitive = primitives[i];
        primitive->draw(this);
    }
}

void EiRas::_present(EiCommand** commands, int count)
{
    for(int i = 0; i < count; i++)
    {
        EiCommand* command = commands[i];
        _drawPrimitives(command->primitives, command->primitiveCount);
        delete command;
    }
    
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
#warning 记得移除
#warning enableMerge TODO
#endif
    presentToFile("OutPutFileMSAA.ppm");
}
