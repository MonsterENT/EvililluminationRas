//
//  EiLock_MacOS_Bridge.cpp
//  EiRasMacBuild
//
//  Created by MonsterENT on 2/13/19.
//  Copyright © 2019 MonsterEntertainment. All rights reserved.
//

#include "EiLock_MacOS_Bridge.hpp"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
#import "EiLock_MacOS_Build.h"

void* createLock_macos_ptr()
{
    EiLock_MacOS_Build* lock = [EiLock_MacOS_Build new];
    lock.self_retain_ptr = lock;
    
    return (__bridge void*)lock;
}

void lock_lock_macos_ptr(void* lock_prt)
{
    EiLock_MacOS_Build* lock = (__bridge EiLock_MacOS_Build*)lock_prt;
    [lock.lock lock];
}

void unlock_lock_macos_ptr(void* lock_prt)
{
    EiLock_MacOS_Build* lock = (__bridge EiLock_MacOS_Build*)lock_prt;
    [lock.lock unlock];
}

void release_lock_macos_ptr(void* lock_prt)
{
    EiLock_MacOS_Build* lock = (__bridge EiLock_MacOS_Build*)lock_prt;
    lock.self_retain_ptr = nullptr;
    lock = nullptr;
}

#endif
