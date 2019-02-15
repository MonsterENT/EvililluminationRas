//
//  EiLockHelper.hpp
//  EiRasMacBuild
//
//  Created by MonsterENT on 2/13/19.
//  Copyright © 2019 MonsterEntertainment. All rights reserved.
//

#ifndef EiLockHelper_hpp
#define EiLockHelper_hpp

#include "../../EiMacro.h"
#include "EiLock.hpp"
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
#include "MacOS_Build/EiLock_MacOS_Adapter.hpp"
#endif

namespace EiLockHelper {
    inline EiLock* createEiLock()
    {
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
        return new EiLock_MacOS_Adapter;
#endif
        return nullptr;
    }
}


#endif /* EiLockHelper_hpp */
