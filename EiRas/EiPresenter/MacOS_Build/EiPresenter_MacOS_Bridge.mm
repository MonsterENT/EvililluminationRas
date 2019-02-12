//
//  EiPresenter_MacOS_Bridge.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 2/12/19.
//  Copyright © 2019 Monster. All rights reserved.
//

#include "EiPresenter_MacOS_Bridge.hpp"
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#import "EiPresenter_MacOS_Build.h"

void present(EiRas* device, void* target)
{
    [EiPresenter_MacOS_Build present:device target:target];
}
#endif
