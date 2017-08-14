//
//  Transform2D.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/3/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef Transform2D_hpp
#define Transform2D_hpp


#include "Eimath.h"


class EiTransform2D
{
public:
    
    static void Translation2D(vec2 &p,vec2 offset)
    {
        p = p + offset;
    }
    
    static void MatrixTranslation2D(matrix3X3 &_mat,vec2 offset)
    {
        _mat.m13 += offset.x;
        _mat.m23 += offset.y;
    }
    
    
    static void Rotation2D(vec2 &p,vec2 point,float angel)
    {
        vec2 temp_P = p - point;
        
        temp_P.x = p.x * cosf(angel) - p.y * sinf(angel);
        
        temp_P.y = p.y * cosf(angel) + p.x * sinf(angel);
        
        p = temp_P + point;
    }
    
    
    static void MatrixRotation2D(matrix3X3 &_mat,vec2 point,float angel)
    {
        
        
        
        matrix3X3 matB;
        matB.m11 = cosf(angel);
        matB.m12 = -sinf(angel);
        matB.m13 = point.x;
        
        matB.m21 = sinf(angel);
        matB.m22 = cosf(angel);
        matB.m23 = point.y;
        
        matrix3X3 matC;
        matC.m13 = -point.x;
        matC.m23 = -point.y;
        
        matB = matrix3X3::mul(matB, matC);
        
        _mat = matrix3X3::mul(matB,_mat);
    }
    
    static void MatrixScale2D(matrix3X3 &_mat,vec2 scaleOffset)
    {
        matrix3X3 matB;
        matB.m11 = scaleOffset.x;
        matB.m22 = scaleOffset.y;
        
        _mat = matrix3X3::mul(matB, _mat);
    }
    
};




#endif /* Transform2D_hpp */
