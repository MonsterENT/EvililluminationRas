//
//  EiPrimitive.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiPrimitive_hpp
#define EiPrimitive_hpp

#include "../EiMacro.h"
#include "../EiRas.hpp"
#include "../EiRasObject.hpp"

class EiRas;

class EiPrimitive : public EiRasObject
{
    friend class EiRas;
public:
    
    EiPrimitive()
    {
    };
    
    virtual ~EiPrimitive()
    {
    };
    
    virtual EiPrimitive* copy()
    {
        if(staticObj)
        {
            return this;
        }
        else
        {
            EiPrimitive* ret = new EiPrimitive;
            return ret;
        }
    }
    
    inline void chageStartEnd(float& start,float& end)
    {
        float temp;
        if(start > end)
        {
            temp = start;
            start = end;
            end = temp;
        }
        
    }
private:
    virtual void draw(EiRas* device)
    {
    };
};
#endif /* EiPrimitive_hpp */
