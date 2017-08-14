//
//  Ei_triangel.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/2/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef Ei_triangel_hpp
#define Ei_triangel_hpp

#include "Eiobject.hpp"
#include <vector>
//#include <algorithm>
#include "Transform2D.hpp"
using std::vector;




class Ei_triangel : public Eiobject
{
public:
    
    vec2 pA,pB,pC;
    vec4 colorA,colorB,colorC;
    
    Ei_triangel(vec2 _pA,vec2 _pB,vec2 _pC);
    
    ~Ei_triangel()
    {
        
    }
    
    void MatrixTransform(matrix3X3 &mat);
    
    
    void draw();
    
    
    private:
    
    vector<float>angel_line;
    vector<vec2>axis_line;
    
    vector<vec2> translation_offset_line;
    
    
    
    std::vector<vec2> pointLine;
    vec2 pM;
    float k_p0_p2,b_p0_p2; bool Max_k_p0_p2;
    float k_p0_p1,b_p0_p1; bool Max_k_p0_p1;
    float k_p2_p1,b_p2_p1; bool Max_k_p2_p1;
    
    bool flag_0;//下低平
    bool flag_1;//上底平
    
    
    
    inline vec4 lerpColor(vec2 p)
    {
        
        float v = ((p.y- pA.y)*(pB.x - pA.x) + (pA.y - pB.y)*(p.x - pA.x)) / ((pC.y -pA.y) * (pB.x - pA.x) - (pA.y - pB.y) *(pA.x - pC.x));
        float u = (p.x + (v-1.0)*pA.x -v * pC.x)/(pB.x - pA.x);
        
        return colorA*(u) + colorB*(v) + colorC*(1 - v -u);
        
    }
    
    void ProcessPoint();
};



#endif /* Ei_triangel_hpp */
