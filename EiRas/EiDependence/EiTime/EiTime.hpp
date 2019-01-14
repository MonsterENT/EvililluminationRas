//
//  EiTime.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/26.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiTime_hpp
#define EiTime_hpp

#include "../../EiMacro.h"
#include "../../EiRasObject.hpp"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
#include "MacOS_Build/EiTime_MacOS_Adapter.hpp"
#endif

class EiTime : public EiRasObject
{
public:
    
    EiTime()
    {
        tmpHashCode = getTimestamp();
    }
    
    //ms - 13
    double getTimestamp()
    {
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)
        return getTimestamp_macos();
#endif
        return -1;
    };
    
    int hashCode()
    {
        if(tmpHashCode < 0)
        {
            tmpHashCode = getTimestamp();
        }
        return tmpHashCode;
    }
    
private:
    double tmpHashCode = -1;
};

#endif /* EiTime_hpp */
