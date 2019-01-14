//
//  EiThreadHelper.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/25.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiThreadHelper_hpp
#define EiThreadHelper_hpp

#include "../../EiMacro.h"
#include "EiThread.hpp"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
#include "MacOS_Build/EiThread_MacOS_Adapter.hpp"
#endif

#ifdef Ei_Android_Build
//#include "MacOS_Build/EiThread_MacOS_Adapter.hpp"
#endif

#ifdef Ei_Windows_Build
//#include "MacOS_Build/EiThread_MacOS_Adapter.hpp"
#endif

namespace EiThreadHelper {
    inline EiThread* createEiThread()
    {
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
        return new EiThread_MacOS_Adapter;
#endif
        return nullptr;
    }
}

#endif /* EiThreadHelper_hpp */
