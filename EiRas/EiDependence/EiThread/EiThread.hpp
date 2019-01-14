//
//  EiThread.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/25.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiThread_hpp
#define EiThread_hpp

typedef void(*EiThreadFunc)(void* data);
#include "../../EiMacro.h"
#include "../../EiRasObject.hpp"

class EiThread : public EiRasObject
{
public:
    virtual void run(EiThreadFunc func, void* data){};
    virtual ~EiThread(){}
    
    void destoryWhenFinished(EiThread** _pptrThread)
    {
        shouldDestoryFinished = true;
        pptrThread = _pptrThread;
    }
    
protected:
    EiThread** pptrThread;
    bool shouldDestoryFinished;
};

#endif /* EiThread_hpp */
