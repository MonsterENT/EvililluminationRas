//
//  EiRas.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiRas.hpp"
#include <stdio.h>
#include "EiPresenter/EiPresenter.hpp"

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
    
    frame_back = new vec4[frameSize.x * frameSize.y];
    frame_front = new vec4[frameSize.x * frameSize.y];
    depthBuffer = new float[frameSize.x * frameSize.y];
    
    NDC2FrameWidth = frameSize.x;
    NDC2FrameHeight = frameSize.y;
    
    commandBuffer = new EiCommandBuffer(50, this);
}



void EiRas::setPixel(int x,int y, vec4 color)
{
    setPixel(vec2(x, y), color);
}

void EiRas::setPixel(vec2 p, vec4 color)
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
            
            if(enableMerge)
            {
                frame_back[y * frameSize.x + x] = alphaMerge(frame_back[y * frameSize.x + x], color / 4.0);
            }
            else
            {
                frame_back[y * frameSize.x + x] = color / 4.0;
            }
        }
    }
}

void EiRas::setPixelWithDepthTest(vec2 p, float z, vec4 color)
{
    if(!depthTest((int)p.x, (int)p.y, z))
    {
        return;
    }
    
    depthBuffer[(int)p.y * frameSize.x + (int)p.x] = z;
    
    setPixel(p, color);
}

void EiRas::setPixelWithDepthTest(vec3 p, vec4 color)
{
    if(!depthTest((int)p.x, (int)p.y, (int)p.z))
    {
        return;
    }
    
    depthBuffer[(int)p.y * frameSize.x + (int)p.x] = (int)p.z;
    
    setPixel(p, color);
}


void EiRas::presentToFile(const char* fileName)
{
    FILE* f = NULL;
    f = fopen(fileName, "w");
    if(!f)
    {
        return;
    }
    
    fprintf(f, "P3\n%d %d\n%d\n", getFrameSize().x, getFrameSize().y, 255);
    
    for(int y = 0; y < getFrameSize().y; y++)
    {
        for(int x = 0; x < getFrameSize().x; x++)
        {
            vec4 tmpColor = vec4(0, 0, 0, 0);
            sampleFrame(x, y, tmpColor, getFrameBuffer());
            fprintf(f,"%d %d %d ", EiMath_Q::toInt(tmpColor.r), EiMath_Q::toInt(tmpColor.g), EiMath_Q::toInt(tmpColor.b));
        }
    }
    fclose(f);
}

bool EiRas::sampleFrame(int x,int y, vec4 &Color, vec4* frame)
{
    if(!frame)
    {
        frame = frame_back;
    }
    if(x >= 0 && y >= 0 && x < frameSize.x && y < frameSize.y)
    {
        Color += frame[y * frameSize.x + x];
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

bool EiRas::depthTest(int x, int y, int z)
{
    if(depthBuffer[y * frameSize.x + x] < z)
    {
        return false;
    }
    return true;
}

vec4* EiRas::getFrameBuffer()
{
    return frame_front;
}

float* EiRas::getDepthBuffer()
{
    return depthBuffer;
}

void EiRas::clearFrameAndDepth(vec4 clearColor)
{
    //    //pipe line state
    //    vec4 clearColor;
    //    bool isClearFrame = false;
    //    bool isPresent = false;
    //
    //    bool enableMerge;
    //    EiPrimitive** primitives;
    //    unsigned int primitiveCount;
    //    bool* destoryFlag;
    
    EiCommand* cmd = commandBuffer->addCommand();
    if(cmd)
    {
        cmd->refreshStatus();
        cmd->clearColor = clearColor;
        cmd->isClearFrame = true;
        commandBuffer->addCommandFinish();
    }
}

void EiRas::drawPrimitives(EiPrimitive** primitives, int count)
{
    EiCommand* cmd = commandBuffer->addCommand();
    if(cmd)
    {
        cmd->refreshStatus();
        EiPrimitive** copy_array = new EiPrimitive*[count];
        for(int i = 0; i < count; i++)
        {
            copy_array[i] = primitives[i]->copy();
        }
        
        cmd->primitives = copy_array;
        cmd->primitiveCount = count;
        cmd->enableMerge = enableMerge;
        cmd->destoryPrimitiveArray = true;
        commandBuffer->addCommandFinish();
    }
}

void EiRas::drawPrimitive(EiPrimitive* primitive)
{
    EiCommand* cmd = commandBuffer->addCommand();
    if(cmd)
    {
        cmd->refreshStatus();
        EiPrimitive** array = new EiPrimitive*[1];
        array[0] = primitive->copy();
        cmd->primitives = array;
        cmd->primitiveCount = 1;
        cmd->enableMerge = enableMerge;
        cmd->destoryPrimitiveArray = true;
        commandBuffer->addCommandFinish();
    }
}

void EiRas::present()
{
    EiCommand* cmd = commandBuffer->addCommand();
    if(cmd)
    {
        cmd->refreshStatus();
        cmd->isPresent = true;
        commandBuffer->addCommandFinish();
    }
}

void EiRas::_clearFrameAndDepth(vec4& clearColor)
{
    for(int i = 0; i < frameSize.x * frameSize.y; i++)
    {
        frame_back[i] = clearColor;
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
        if(command->primitives)
        {
            _drawPrimitives(command->primitives, command->primitiveCount);
        }
    }
    
    resolveAAFrame();
#ifdef Ei_iOS_Build
    present2platform(this, presenterTarget);
#endif
    
#ifdef Ei_Windows_Build
    presentToFile("OutPutFileMSAA.ppm");
#endif
    
#ifdef Ei_MacOS_Build
    present2platform(this, presenterTarget);
#endif
}

void EiRas::resolveAAFrame()
{
    for(int y = 0; y < frameSize.y; y++)
    {
        for(int x = 0; x < frameSize.x; x++)
        {
            vec4 mixedColor = vec4(0, 0, 0, 0);
            
            int sampledCount = 0;
            for(int index = 0; index < 4; index++)
            {
                const vec2* sampleMatrix = MSAAPosMatrix;
                
                if(sampleFrame(x  + (int)(sampleMatrix[index].x) * dxy.x, y + (int)(sampleMatrix[index].y) * dxy.y , mixedColor))
                {
                    sampledCount ++;
                }
            }
            frame_front[y * frameSize.x + x] = mixedColor;
        }
    }
}
