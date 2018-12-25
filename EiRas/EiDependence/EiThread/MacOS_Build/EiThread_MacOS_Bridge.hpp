//
//  EiThread_MacOS.h
//  EvililluminationRas
//
//  Created by yang on 2018/12/25.
//  Copyright © 2018 Monster. All rights reserved.
//
#include "../../../EiMacro.h"
#if (defined Ei_MacOS_Build) || (defined Ei_MacOS_Build)

#ifndef EiThread_MacOS
#define EiThread_MacOS

#include "../EiThread.hpp"

void* createThread_macos_ptr();

void run_thread_macos_ptr(void* thread_ptr, EiThreadFunc func, void * data, bool shouldDestoryFinished, EiThread** pptrThread);

void release_thread_macos_ptr(void* thread_ptr);

#endif
#endif
