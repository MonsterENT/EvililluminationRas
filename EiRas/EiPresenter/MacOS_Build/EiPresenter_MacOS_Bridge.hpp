//
//  EiPresenter_MacOS_Bridge.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 2/12/19.
//  Copyright © 2019 Monster. All rights reserved.
//

#include "../../EiMacro.h"
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#ifndef EiPresenter_MacOS_Bridge_hpp
#define EiPresenter_MacOS_Bridge_hpp

#include "../../EiRas.hpp"

void present(EiRas* device, void* target);

#endif /* EiPresenter_MacOS_Bridge_hpp */
#endif
