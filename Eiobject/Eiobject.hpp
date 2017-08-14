//
//  Eiobject.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//



#ifndef Eiobject_hpp
#define Eiobject_hpp

#include "Eimath.h"
#include "EiRas.hpp"


namespace Ei_triangelSort {
    inline bool comp(const vec2& obj1,const vec2& obj2)
    {
        if(obj1.y>obj2.y)
            return true;
        else return false;
    }
    
    
}

class Eiobject
{
public:
    
    Eiobject(){
    };
    
    virtual ~Eiobject(){
        
    };
    
    virtual void draw(){
    };
    
    inline void chageStartEnd(float &start,float &end)
    {
        float temp;
        if(start>end)
        {
            temp = start;
            start = end;
            end = temp;
        }
        
    }
};


#endif /* Eiobject_hpp */
