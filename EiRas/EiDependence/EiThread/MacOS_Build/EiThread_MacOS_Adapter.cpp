//
//  EiThread_MacOS_Adapter.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/25.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiThread_MacOS_Adapter.hpp"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#include "EiThread_MacOS_Bridge.hpp"

EiThread_MacOS_Adapter::EiThread_MacOS_Adapter()
{
    ptr_macos_thread = createThread_macos_ptr();
}

void EiThread_MacOS_Adapter::run(EiThreadFunc func, void* data)
{
    run_thread_macos_ptr(ptr_macos_thread, func, data, shouldDestoryFinished, pptrThread);
}

EiThread_MacOS_Adapter::~EiThread_MacOS_Adapter()
{
    release_thread_macos_ptr(ptr_macos_thread);
}

#endif
