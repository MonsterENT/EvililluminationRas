//
//  EiPrimitive.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiPrimitive_hpp
#define EiPrimitive_hpp

#include "../EiRas.hpp"

class EiPrimitive
{
public:
    
    EiPrimitive()
    {
    };
    
    virtual ~EiPrimitive()
    {
    };
    
    virtual void draw(EiRas* device)
    {
    };
    
    inline void chageStartEnd(float &start,float &end)
    {
        float temp;
        if(start > end)
        {
            temp = start;
            start = end;
            end = temp;
        }
        
    }
};
#endif /* EiPrimitive_hpp */
