//
//  EiPresenter.cpp
//  EiRasiOSBuild
//
//  Created by MonsterENT on 2/10/19.
//  Copyright © 2019 yang. All rights reserved.
//

#include "EiPresenter.hpp"
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
#import "MacOS_Build/EiPresenter_MacOS_Bridge.hpp"
#endif

void present2platform(EiRas* device, void* target)
{
    if(!target)
    {
        return;
    }
    #if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
    present(device, target);
    #endif
}
