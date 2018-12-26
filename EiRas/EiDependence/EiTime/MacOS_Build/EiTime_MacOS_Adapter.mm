//
//  EiTime_MacOS_Adapter.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/26.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "../../../EiMacro.h"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#include "EiTime_MacOS_Adapter.hpp"
#include <Foundation/Foundation.h>

double getTimestamp_macos()
{
    return [[NSDate date] timeIntervalSince1970] * 1000;
}

#endif
