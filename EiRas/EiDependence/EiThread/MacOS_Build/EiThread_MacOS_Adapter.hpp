//
//  EiThread_MacOS_Adapter.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/25.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "../../../EiMacro.h"
#if (defined Ei_MacOS_Build) || (defined Ei_MacOS_Build)

#ifndef EiThread_MacOS_Adapter_hpp
#define EiThread_MacOS_Adapter_hpp

#include "../EiThread.hpp"

class EiThread_MacOS_Adapter : public EiThread
{
public:
    EiThread_MacOS_Adapter();
    
    void run(EiThreadFunc func, void* data);
    ~EiThread_MacOS_Adapter();
    
private:
    void* ptr_macos_thread;
};

#endif
#endif /* EiThread_MacOS_Adapter_hpp */
