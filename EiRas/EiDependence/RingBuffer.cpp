//
//  RingBuffer.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 12/23/18.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "RingBuffer.hpp"

RingBuffer::RingBuffer(unsigned int _bufferSize, bool enableStaticMode)
{
    lock = EiLockHelper::createEiLock();
    staticMode = enableStaticMode;
    bufferSize = _bufferSize;
    buffer = new void*[_bufferSize + 1];
    for(int i = 0; i < _bufferSize + 1; i++)
    {
        buffer[i] = 0;
    }
    readPos = 0;
    writePos = 0;
    readPos_static = 0;
}

bool RingBuffer::isEmpty()
{
    lock->lock();
    if(readPos == writePos)
    {
        lock->unlock();
        return true;
    }
    else
    {
        lock->unlock();
        return false;
    }
}

bool RingBuffer::isEmpty_static()
{
    lock->lock();
    if(readPos_static == writePos)
    {
        lock->unlock();
        return true;
    }
    else
    {
        lock->unlock();
        return false;
    }
}

bool RingBuffer::isFull()
{
    lock->lock();
    if((writePos + 1) % (bufferSize + 1) == readPos)
    {
        lock->unlock();
        return true;
    }
    else
    {
        lock->unlock();
        return false;
    }
}

void RingBuffer::clear(RingBufferCallBack callBack)
{
    if(staticMode)
    {
        clear_static(callBack);
        return;
    }
    lock->lock();
    while (1) {
        void* retData = 0;
        if(readBuffer(retData))
        {
            if(callBack)
            {
                callBack(retData);
            }
        }
        else
        {
            break;
        }
    }
    lock->unlock();
}

void RingBuffer::clear_static(RingBufferCallBack callBack)
{
    if(!staticMode)
    {
        return;
    }
    lock->lock();
    readPos = 0;
    writePos = 0;
    readPos_static = 0;
    for(int i = 0; i < bufferSize; i++)
    {
        if(callBack)
        {
            callBack(buffer[i]);
            buffer[i] = 0;
        }
    }
    lock->unlock();
}

bool RingBuffer::readBuffer(void* &retDataPtr)
{
    if(isEmpty())
    {
        return false;
    }
    lock->lock();
    retDataPtr = buffer[readPos];
    readPos = (readPos + 1) % (bufferSize + 1);
    readPos_static = readPos;
    lock->unlock();
    return true;
}

bool RingBuffer::readBuffer(void** &retDataPtr)
{
    if(isEmpty())
    {
        return false;
    }
    lock->lock();
    retDataPtr = buffer + readPos;
    readPos = (readPos + 1) % (bufferSize + 1);
    readPos_static = readPos;
    lock->unlock();
    return true;
}

bool RingBuffer::readBuffer_static(void** &retDataPtr)
{
    if(isEmpty_static())
    {
        return false;
    }
    lock->lock();
    retDataPtr = buffer + readPos_static;
    readPos_static = (readPos_static + 1) % (bufferSize + 1);
    lock->unlock();
    return true;
}

void RingBuffer::readPosRedirect(int step)
{
    lock->lock();
    readPos = readPos_static;
    lock->unlock();
}

bool RingBuffer::writeBuffer(void* dataPtr)
{
    if(isFull())
    {
        return false;
    }
    lock->lock();
    buffer[writePos] = dataPtr;
    writePos = (writePos + 1) % (bufferSize + 1);
    return true;
}

bool RingBuffer::writeBuffer_static(void* &retDataPtr, bool &shouldCreate)
{
    if(!staticMode)
    {
        return false;
    }
    if(isFull())
    {
        return false;
    }
    lock->lock();
    if(buffer[writePos] == nullptr)
    {
        shouldCreate = true;
        lock->unlock();
        return false;
    }
    retDataPtr = buffer[writePos];
    writePos = (writePos + 1) % (bufferSize + 1);
    return true;
}

void RingBuffer::writeBuffer_finish()
{
    lock->unlock();
}
