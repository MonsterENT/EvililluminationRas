//
//  EiThread_MacOS.m
//  EvililluminationRas
//
//  Created by yang on 2018/12/25.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiThread_MacOS_Bridge.hpp"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#import "EiThread_MacOS_Build.h"

void* createThread_macos_ptr()
{
    EiThread_MacOS_Build* thread = [EiThread_MacOS_Build new];
    thread.self_retain_ptr = thread;
    return (__bridge void*)thread;
}

void run_thread_macos_ptr(void* thread_ptr, EiThreadFunc func, void * data, bool shouldDestoryFinished, EiThread** pptrThread)
{
    if(func)
    {
        EiThread_MacOS_Build* thread = (__bridge EiThread_MacOS_Build*)thread_ptr;
        [thread runWithBlock:^{
            func(data);
            if(shouldDestoryFinished)
            {
                delete (*pptrThread);
                *pptrThread = nullptr;
            }
        }];
    }
}

void release_thread_macos_ptr(void* thread_ptr)
{
    EiThread_MacOS_Build* thread = (__bridge EiThread_MacOS_Build*)thread_ptr;
    thread.self_retain_ptr = nullptr;
    thread = nullptr;
}
#endif
