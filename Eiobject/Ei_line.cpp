//
//  Ei_line.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "Ei_line.hpp"


Line::Line(float x1,float y1,float x2,float y2)
{
    width = 0;
    
    p1 = vec2(x1,y1);
    
    p2 = vec2(x2,y2);
    
    k = (y1-y2)/(x1-x2);
    
    if(k>1)
    {
        steps = fabs(y2 - y1);
    }
    else steps = fabs(x2 - x1);
    
    xIncrement = (x2 - x1)/(float)steps;
    yIncrement = (y2 - y1)/(float)steps;
}

Line::Line(vec2 _p1, vec2 _p2)
{
    width = 0;
    
    p1 = _p1;
    p2 = _p2;
    
    k = (_p1.y - _p2.y)/(_p1.x - _p2.x);
}


void Line::draw()
{
    vec2 pos(p1);
    for(int i =0;i<steps;i++)
    {
        setPixel(pos.x,pos.y,color);
        if(width >0)
        {
            if(k>1)
            {
                //水平
                for(int i = -width/2.0; i<=width/2.0;i++)
                    setPixel(pos.x + i, pos.y,color);
            }
            else
            {
                for(int i = -width/2.0; i<=width/2.0;i++)
                    setPixel(pos.x, pos.y + i,color);
            }
        }
        pos.x += xIncrement;
        pos.y += yIncrement;
    }
}
