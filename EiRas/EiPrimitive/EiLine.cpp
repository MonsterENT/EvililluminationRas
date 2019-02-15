//
//  EiLine.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiLine.hpp"
#include "../EiRas.hpp"

EiLine::EiLine(float x1,float y1,float x2,float y2)
{
    EiLine(vec2(x1, y1), vec2(x2, y2));
}

EiLine::EiLine(vec2 _p1, vec2 _p2)
{
    width = 0;
    
    p1 = _p1;
    p2 = _p2;
    if(fabs(_p1.x - _p2.x) < _ESP0X10)
    {
        _p1.x = _p2.x + _ESP0X10;
    }
    k = fabs(_p1.y - _p2.y) - fabs(_p1.x - _p2.x);
    if(k > 0)
    {
        steps = fabs(p2.y - p1.y);
    }
    else
    {
        steps = fabs(p2.x - p1.x);
    }
    
    stepGap = EiRas::getFrameDxy().x;
    if(k > 0)
    {
        stepGap = EiRas::getFrameDxy().y;
    }
    
    xIncrement = (p2.x - p1.x) / steps * stepGap;
    yIncrement = (p2.y - p1.y) / steps * stepGap;
    
    color = ColorGray(1);
}

void EiLine::draw(EiRas* device)
{
    vec2 pos(p1);
    
    for(float i = 0; i < steps; i += stepGap)
    {
        device->setPixel(pos, color);
        if(width > 0)
        {
            if(k > 1)
            {
                for(float i = -width / 2.0; i <= width / 2.0; i += EiRas::getFrameDxy().x)
                {
                    device->setPixel(vec2(pos.x + i, pos.y), color);
                }
            }
            else
            {
                for(float i = -width / 2.0; i <= width / 2.0; i += EiRas::getFrameDxy().x)
                {
                    device->setPixel(vec2(pos.x, pos.y + i), color);
                }
            }
        }
        pos.x += xIncrement;
        pos.y += yIncrement;
    }
}
