//
//  EiTime_MacOS_Adapter.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/26.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "../../../EiMacro.h"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#ifndef EiTime_MacOS_Adapter_hpp
#define EiTime_MacOS_Adapter_hpp

double getTimestamp_macos();

#endif /* EiTime_MacOS_Adapter_hpp */
#endif
