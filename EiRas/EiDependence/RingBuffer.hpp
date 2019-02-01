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

typedef void(*RingBufferCallBack)(void* ptr);

class RingBuffer {
public:
    RingBuffer(unsigned int bufferSize);
    
    bool isEmpty();
    bool isFull();
    
    //this callBack func will be invoked for every data was stored in ringBuffer
    //at callBack you can free the memory of the data
    void clear(RingBufferCallBack callBack = 0);
    
    bool readBuffer(void* &retDataPtr);
    bool writeBuffer(void* dataPtr);
    
    unsigned int getBufferSize()
    {
        return  bufferSize + 1;
    }
    
    ~RingBuffer()
    {
        delete[] buffer;
    }
private:
    void** buffer;
    unsigned int bufferSize;
    
    int writePos, readPos;
};

#endif /* RingBuffer_hpp */
