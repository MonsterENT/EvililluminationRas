//
//  EiCommandBuffer.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/24.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiCommandBuffer_hpp
#define EiCommandBuffer_hpp

#include "../EiMacro.h"
#include "../EiRasObject.hpp"
#include "../EiDependence/RingBuffer.hpp"
#include "../EiPrimitive/EiPrimitive.hpp"
#include "../EiRas.hpp"

class EiRas;

class EiCommand : public EiRasObject
{
public:
    //pipe line state
    bool isClearFrame = false;
    bool isPresent = false;
    
    bool enableMerge;
    EiPrimitive** primitives;
    unsigned int primitiveCount;
    bool* destoryFlag;
    
    int hashCode()
    {
        int ret = enableMerge;
        for(int i = 0; i < primitiveCount; i++)
        {
            ret = 31 * ret + primitives[i]->hashCode();
        }
        return ret;
    }
};

class EiCommandBuffer : public EiRasObject
{
public:
    EiCommandBuffer(unsigned int bufferSize, EiRas* _device);
    ~EiCommandBuffer();
    
    void addCommand(EiCommand* command);
    
private:
    RingBuffer* buffer;
    EiRas* device;
};

#endif /* EiCommandBuffer_hpp */
