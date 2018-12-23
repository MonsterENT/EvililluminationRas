//
//  EiLine.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiLine_hpp
#define EiLine_hpp

#include "../EiMacro.h"
#include "../EiMath/EiMath.hpp"
#include "EiPrimitive.hpp"

class EiLine : public EiPrimitive
{
public:
    EiLine(float x1, float y1, float x2, float y2);
    EiLine(vec2 _p1, vec2 _p2);
    
    ~EiLine()
    {
        
    }
    
    int hashCode()
    {
        int ret = p1.hashCode();
        ret = 31 * ret + p2.hashCode();
        ret = 31 * ret + width;
        ret = 31 * color.hashCode();
        return ret;
    }
    
    float width;
    vec4 color;
private:
    vec2 p1,p2;
    float k;
    float xIncrement,yIncrement;
    float steps;
    float stepGap;
    
    void draw(EiRas* device);
};
#endif /* EiLine_hpp */
