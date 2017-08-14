//
//  Ei_line.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef Ei_line_hpp
#define Ei_line_hpp

#include "Eiobject.hpp"


class Line : public Eiobject
{
    
public:
    
    vec2 p1,p2;
    vec4 color;
    float k;
    float width;
    
    
    Line(float x1,float y1,float x2,float y2);
    Line(vec2 _p1, vec2 _p2);
    
    ~Line()
    {
        
    }
    
    
    void draw();
    
    
private:
    float xIncrement,yIncrement;
    int steps;
    
};


#endif /* Ei_line_hpp */
