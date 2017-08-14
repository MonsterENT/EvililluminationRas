//
//  Transform3D.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/9/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef Transform3D_hpp
#define Transform3D_hpp

#include "Eimath.h"


class EiTransform3D
{
public:
    static void MatrixTranslation3D(matrix4X4& _mat,vec3 offset)
    {
        matrix4X4 Tmat;
        Tmat.m14 = offset.x;
        Tmat.m24 = offset.y;
        Tmat.m34 = offset.z;
        
        _mat = matrix4X4::mul(Tmat, _mat);
    }
    
    static void MatrixRotation3D(matrix4X4& _mat,const vec3 axis,const vec3 axisPoint,float angel)
    {
        matrix4X4 rotationAxis;
        
        
        vec3 axisOnZ_Y;
        vec3 axisXvec;
        vec3 axisYvec;
        
        if(axis == vec3(1,0,0))
        {
            axisYvec = vec3(0,1,0);
            axisXvec = axisYvec.cross(axis);
        }
        else if(axis.x < _ESP0X2)
        {
            axisOnZ_Y = axis;
            axisXvec = vec3(1,0,0);
            axisYvec = axisXvec.cross(axisOnZ_Y);
        }
        else
        {
            axisOnZ_Y.x = 0;
            axisOnZ_Y.y = axis.y;
            axisOnZ_Y.z = axis.z;
            
            axisXvec = axis.cross(axisOnZ_Y);
            axisYvec = axisXvec.cross(axis);
        }
        
        
        
        rotationAxis.m11 = axisXvec.x;
        rotationAxis.m12 = axisXvec.y;
        rotationAxis.m13 = axisXvec.z;
        
        rotationAxis.m21 = axisYvec.x;
        rotationAxis.m22 = axisYvec.y;
        rotationAxis.m23 = axisYvec.z;
        
        rotationAxis.m31 = axis.x;
        rotationAxis.m32 = axis.y;
        rotationAxis.m33 = axis.z;
        
        
        matrix4X4 _matTranslation;
        _matTranslation.m14 = -axisPoint.x;
        _matTranslation.m24 = -axisPoint.y;
        _matTranslation.m34 = -axisPoint.z;
        
        //旋转到标准坐标
        
        
        
        
        matrix4X4 _matRoationZ;
        
        _matRoationZ.m11 = cosf(angel);
        _matRoationZ.m12 = -sinf(angel);
        
        _matRoationZ.m21 = sinf(angel);
        _matRoationZ.m22 = cosf(angel);
        
        matrix4X4 _matTemp = matrix4X4::mul(rotationAxis,_matTranslation);
        
        matrix4X4 _matFinal = matrix4X4::mul(_matRoationZ, _matTemp);
        
        
        rotationAxis.transpose();
        
        _matFinal = matrix4X4::mul(rotationAxis, _matFinal);
        
        _matTranslation.m14 = axisPoint.x;
        _matTranslation.m24 = axisPoint.y;
        _matTranslation.m34 = axisPoint.z;
        
        _matFinal = matrix4X4::mul(_matTranslation, _matFinal);
        
        _mat = matrix4X4::mul(_matFinal, _mat);
        
    }
};


#endif /* Transform3D_hpp */
