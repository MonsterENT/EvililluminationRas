//
//  RingBuffer.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 12/23/18.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "RingBuffer.hpp"

RingBuffer::RingBuffer(unsigned int _bufferSize)
{
    bufferSize = _bufferSize;
    buffer = new void*[_bufferSize + 1];
    readPos = 0;
    writePos = 0;
}

bool RingBuffer::isEmpty()
{
    if(readPos == writePos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool RingBuffer::isFull()
{
    if((writePos + 1) % (bufferSize + 1) == readPos)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void RingBuffer::clear(RingBufferCallBack callBack)
{
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
}

bool RingBuffer::readBuffer(void* &retDataPtr)
{
    if(isEmpty())
    {
        return false;
    }
    retDataPtr = buffer[readPos];
    readPos = (readPos + 1) % (bufferSize + 1);
    return true;
}
bool RingBuffer::writeBuffer(void* dataPtr)
{
    if(isFull())
    {
        return false;
    }
    buffer[writePos] = dataPtr;
    writePos = (writePos + 1) % (bufferSize + 1);
    return true;
}
