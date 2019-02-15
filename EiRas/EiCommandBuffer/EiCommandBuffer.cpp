//
//  EiCommandBuffer.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/24.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiCommandBuffer.hpp"
#include <assert.h>

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
    if(bufferSize > EiCommandBuffer_MAX_Command)
    {
        bufferSize = EiCommandBuffer_MAX_Command;
    }
    buffer = new RingBuffer(bufferSize, true);
    outCmdPool = new EiCommand*[bufferSize];
    device = _device;
    time = new EiTime();
    lastTimestamp = time->getTimestamp();
    
    threadCtl = new EiCommandThreadCtl;
    threadCtl->commandBuffer = this;
    threadCtl->threadQuitCtl = false;
    
    thread = EiThreadHelper::createEiThread();
    assert(thread != NULL);
    thread->destoryWhenFinished(&thread);
    thread->run(commandFunc, threadCtl);
}

void bufferReleaseCallBack (void* ptr)
{
    EiCommand* cmd = (EiCommand*)ptr;
    delete cmd;
}

EiCommandBuffer::~EiCommandBuffer()
{
    threadCtl->threadQuitCtl = true;
    buffer->clear_static(bufferReleaseCallBack);
    delete buffer;
}


EiCommand* EiCommandBuffer::addCommand()
{
    void* tmpCmd = NULL;
    bool shouldCreate = false;
    while (!buffer->writeBuffer_static(tmpCmd, shouldCreate))
    {
        if(shouldCreate)
        {
            tmpCmd = new EiCommand;
            while (!buffer->writeBuffer(tmpCmd));
            break;
        }
    }
    return (EiCommand*)tmpCmd;
}

void EiCommandBuffer::addCommandFinish()
{
    buffer->writeBuffer_finish();
}

EiCommand** EiCommandBuffer::getCommand()
{
    void** retCommand = nullptr;
    if(buffer->readBuffer_static(retCommand))
    {
        return (EiCommand**)retCommand;
    }
    return nullptr;
}

void EiCommandBuffer::getCommandFinish(int count)
{
    buffer->readPosRedirect(count + 2);
}

EiCommand** EiCommandBuffer::getOutCmdPool()
{
    return outCmdPool;
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
            EiCommand** cmd = commandBuffer->getCommand();
            if(cmd)
            {
                if((*cmd)->isClearFrame)
                {
                    commandCount = 0;
                    commandBuffer->_clearFrameAndDepth((*cmd)->clearColor);
                }
                else if((*cmd)->isPresent)
                {
                    commandBuffer->_present(commandBuffer->getOutCmdPool(), commandCount);
                    commandBuffer->getCommandFinish(commandCount);
                }
                else
                {
                    commandBuffer->getOutCmdPool()[commandCount++] = *cmd;
                }
            }
        }
    }
}
