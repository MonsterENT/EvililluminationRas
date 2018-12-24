//
//  EiCommandBuffer.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/24.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiCommandBuffer.hpp"

EiCommandBuffer::EiCommandBuffer(unsigned int bufferSize, EiRas* _device)
{
    buffer = new RingBuffer(bufferSize);
    device = _device;
}

EiCommandBuffer::~EiCommandBuffer()
{
    delete buffer;
}

void EiCommandBuffer::addCommand(EiCommand* command)
{
    while (!buffer->writeBuffer(command));
}
