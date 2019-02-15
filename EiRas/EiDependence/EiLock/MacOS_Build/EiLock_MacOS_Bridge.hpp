//
//  EiLock_MacOS_Bridge.hpp
//  EiRasMacBuild
//
//  Created by MonsterENT on 2/13/19.
//  Copyright © 2019 MonsterEntertainment. All rights reserved.
//

#ifndef EiLock_MacOS_Bridge_hpp
#define EiLock_MacOS_Bridge_hpp

#include "../../../EiMacro.h"
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

void* createLock_macos_ptr();

void lock_lock_macos_ptr(void* lock);

void unlock_lock_macos_ptr(void* lock);

void release_lock_macos_ptr(void* lock);

#endif
#endif /* EiLock_MacOS_Bridge_hpp */
