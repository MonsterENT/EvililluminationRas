//
//  RingBuffer.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 12/23/18.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef RingBuffer_hpp
#define RingBuffer_hpp

#include "../EiMacro.h"
#include "EiLock/EiLockHelper.hpp"

typedef void(*RingBufferCallBack)(void* ptr);

class RingBuffer {
public:
    RingBuffer(unsigned int bufferSize, bool enableStaticMode = false);
    
    bool isEmpty();
    bool isFull();
    
    //this callBack func will be invoked for every data was stored in ringBuffer
    //at callBack you can free the memory of the data
    void clear(RingBufferCallBack callBack);
    
    void clear_static(RingBufferCallBack callBack);
    
    bool readBuffer(void* &retDataPtr);
    bool readBuffer(void** &retDataPtr);
    
    bool readBuffer_static(void** &retDataPtr);
    void readPosRedirect(int step);
    
    bool writeBuffer(void* dataPtr);
    
    bool writeBuffer_static(void* &retDataPtr, bool &shouldCreate);
    void writeBuffer_finish();
    
    unsigned int getBufferSize()
    {
        return  bufferSize + 1;
    }
    
    ~RingBuffer()
    {
        delete[] buffer;
    }
private:
    
    bool isEmpty_static();
    void** buffer;
    unsigned int bufferSize;
    
    int writePos, readPos, readPos_static;
    bool staticMode;
    EiLock* lock;
};

#endif /* RingBuffer_hpp */
