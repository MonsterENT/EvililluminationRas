//
//  EiLine.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiLine_hpp
#define EiLine_hpp

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
    
    void draw(EiRas* device);

private:
    vec2 p1,p2;
    vec4 color;
    float k;
    float width;
    float xIncrement,yIncrement;
    int steps;
};
#endif /* EiLine_hpp */
