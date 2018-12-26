//
//  EiCommandBuffer.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/24.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiCommandBuffer.hpp"

void commandFunc(void* data);

int EiCommand::hashCode()
{
    int ret = enableMerge;
    for(int i = 0; i < primitiveCount; i++)
    {
        ret = 31 * ret + primitives[i]->hashCode();
    }
    ret = 31 * ret + clearColor.hashCode();
    ret = 31 * ret + isClearFrame;
    ret = 31 * ret + isPresent;
    ret = 31 * ret + destoryPrimitiveArray;
    return ret;
}

EiCommand::~EiCommand()
{
    if(destoryFlag)
    {
        delete[] destoryFlag;
    }
    if(destoryPrimitiveArray && primitives)
    {
        for(int i = 0; i < primitiveCount; i++)
        {
            delete primitives[i];
        }
        delete[] primitives;
    }
}

EiCommandBuffer::EiCommandBuffer(unsigned int bufferSize, EiRas* _device)
{
    buffer = new RingBuffer(bufferSize);
    device = _device;
    time = new EiTime();
    lastTimestamp = time->getTimestamp();
    
    threadCtl = new EiCommandThreadCtl;
    threadCtl->commandBuffer = this;
    threadCtl->threadQuitCtl = false;
    
    thread = EiThreadHelper::createEiThread();
    thread->destoryWhenFinished(&thread);
    thread->run(commandFunc, threadCtl);
}

EiCommandBuffer::~EiCommandBuffer()
{
    threadCtl->threadQuitCtl = true;
    delete buffer;
}

void EiCommandBuffer::addCommand(EiCommand* command)
{
    while (!buffer->writeBuffer(command));
}

EiCommand* EiCommandBuffer::getCommand()
{
    void* retCommand = nullptr;
    if(buffer->readBuffer(retCommand))
    {
        return (EiCommand*)retCommand;
    }
    return nullptr;
}

EiCommand** EiCommandBuffer::getCommandPool()
{
    return commandOutPool;
}

double EiCommandBuffer::getDeltaTime()
{
    double curTime = time->getTimestamp();
    double deltaTime = curTime - lastTimestamp;
    if(deltaTime > 33.33f)
    {
        lastTimestamp = curTime;
    }
    return deltaTime;
}

void EiCommandBuffer::_clearFrameAndDepth(vec4& clearColor)
{
    device->_clearFrameAndDepth(clearColor);
}

void EiCommandBuffer::_present(EiCommand** commands, int count)
{
    device->_present(commands, count);
}

void commandFunc(void* data)
{
    EiCommandThreadCtl* threadCtl = (EiCommandThreadCtl*)data;
    EiCommandBuffer* commandBuffer = threadCtl->commandBuffer;
    
    int commandCount = 0;
    
    while (!threadCtl->threadQuitCtl)
    {
        if(commandBuffer->getDeltaTime() > 33.33f)
        {
            EiCommand* command = commandBuffer->getCommand();
            if(command)
            {
                if(command->isClearFrame)
                {
                    commandCount = 0;
                    commandBuffer->_clearFrameAndDepth(command->clearColor);
                }
                else if(command->isPresent)
                {
                    commandBuffer->_present(commandBuffer->getCommandPool(), commandCount);
                }
                else
                {
                    commandBuffer->getCommandPool()[commandCount++] = command;
                }
            }
        }
    }
}
