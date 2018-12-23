//
//  EiTriangel.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/19.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiTriangel_hpp
#define EiTriangel_hpp

#include "../EiMacro.h"
#include "../EiMacro.h"
#include "../EiMath/EiMath.hpp"
#include "EiPrimitive.hpp"

class EiTriangel2D : public EiPrimitive
{
public:
    vec2 pA, pB, pC;
    vec4 colorA, colorB, colorC;
    
    EiTriangel2D(vec2 _pA, vec2 _pB, vec2 _pC);
    void MatrixTransform(const matrix3X3& mat);
    
private:
    vec2 pointLine[3];
    vec2 pM;
    float k_p0_p2, b_p0_p2; bool Max_k_p0_p2;
    float k_p0_p1, b_p0_p1; bool Max_k_p0_p1;
    float k_p2_p1, b_p2_p1; bool Max_k_p2_p1;
    
    bool flag_0;//下低平
    bool flag_1;//上底平
    
    inline vec4 lerpColor(vec2 p)
    {
        float v = ((p.y - pA.y) * (pB.x - pA.x) + (pA.y - pB.y) * (p.x - pA.x)) / ((pC.y - pA.y) * (pB.x - pA.x) - (pA.y - pB.y) * (pA.x - pC.x));
        float u = (p.x + (v - 1.0) * pA.x - v * pC.x) / (pB.x - pA.x);
        
        return colorA * (u) + colorB * (v) + colorC * (1 - v - u);
    }
    
    void ProcessPoint();
    void draw(EiRas* device);
};

#endif /* EiTriangel_hpp */
