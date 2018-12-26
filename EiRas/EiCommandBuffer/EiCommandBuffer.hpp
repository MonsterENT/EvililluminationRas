//
//  EiCommandBuffer.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/24.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiCommandBuffer_hpp
#define EiCommandBuffer_hpp

#define EiCommandBuffer_MAX_Command (50)

#include "../EiMacro.h"
#include "../EiRasObject.hpp"
#include "../EiDependence/RingBuffer.hpp"
#include "../EiPrimitive/EiPrimitive.hpp"
#include "../EiRas.hpp"
#include "../EiDependence/EiTime/EiTime.hpp"
#include "../EiDependence/EiThread/EiThreadHelper.hpp"


class EiRas;
class EiCommandBuffer;
class EiPrimitive;

class EiCommand : public EiRasObject
{
public:
    //pipe line state
    vec4 clearColor;
    bool isClearFrame;
    bool isPresent;
    bool destoryPrimitiveArray;
    
    bool enableMerge;
    EiPrimitive** primitives;
    unsigned int primitiveCount;
    bool* destoryFlag;
    
    EiCommand()
    {
        isClearFrame = false;
        isPresent = false;
        destoryPrimitiveArray = false;
        destoryFlag = nullptr;
        primitives = nullptr;
    }
    
    ~EiCommand();
    
    int hashCode();
};

struct EiCommandThreadCtl {
    EiCommandBuffer* commandBuffer;
    bool threadQuitCtl;
};

class EiCommandBuffer : public EiRasObject
{
public:
    EiCommandBuffer(unsigned int bufferSize, EiRas* _device);
    ~EiCommandBuffer();
    
    void addCommand(EiCommand* command);
    EiCommand* getCommand();
    
    EiCommand** getCommandPool();
    
    double getDeltaTime();
    
    void _clearFrameAndDepth(vec4& clearColor);
    void _present(EiCommand** commands, int count);
private:
    double lastTimestamp;
    
    RingBuffer* buffer;
    EiRas* device;
    
    EiThread* thread;
    EiTime* time;
    
    EiCommandThreadCtl* threadCtl;
//    EiCommand* commandInPool[EiCommandBuffer_MAX_Command];
    EiCommand* commandOutPool[EiCommandBuffer_MAX_Command];
};

#endif /* EiCommandBuffer_hpp */
