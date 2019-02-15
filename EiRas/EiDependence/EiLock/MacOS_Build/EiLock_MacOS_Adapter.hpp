//
//  EiLock_MacOS_Adapter.hpp
//  EiRasMacBuild
//
//  Created by MonsterENT on 2/13/19.
//  Copyright © 2019 MonsterEntertainment. All rights reserved.
//

#ifndef EiLock_MacOS_Adapter_hpp
#define EiLock_MacOS_Adapter_hpp

#include "../../../EiMacro.h"
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#include "../EiLock.hpp"

class EiLock_MacOS_Adapter : public EiLock{
public:
    EiLock_MacOS_Adapter();
    
    ~EiLock_MacOS_Adapter();
    
    void lock();
    
    void unlock();
private:
    void* ptr_macos_lock;
};

#endif
#endif /* EiLock_MacOS_Adapter_hpp */
