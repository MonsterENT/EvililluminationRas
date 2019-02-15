//
//  EiLock_MacOS_Adapter.cpp
//  EiRasMacBuild
//
//  Created by MonsterENT on 2/13/19.
//  Copyright © 2019 MonsterEntertainment. All rights reserved.
//

#include "EiLock_MacOS_Adapter.hpp"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#include "EiLock_MacOS_Bridge.hpp"

EiLock_MacOS_Adapter::EiLock_MacOS_Adapter()
{
    ptr_macos_lock = createLock_macos_ptr();
}

EiLock_MacOS_Adapter::~EiLock_MacOS_Adapter()
{
    release_lock_macos_ptr(ptr_macos_lock);
}

void EiLock_MacOS_Adapter::lock()
{
    lock_lock_macos_ptr(ptr_macos_lock);
}

void EiLock_MacOS_Adapter::unlock()
{
    unlock_lock_macos_ptr(ptr_macos_lock);
}


#endif
