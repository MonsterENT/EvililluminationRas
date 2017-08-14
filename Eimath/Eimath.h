//
//  Eimath.h
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef Eimath_h
#define Eimath_h

#define  _PI 3.1415926
#define  _ESP0X1 1e-1
#define  _ESP0X2 1e-2
#define  _ESP0X5 1e-5
#define  _ESP0X10 1e-10


#include <vector>
#include <math.h>
using std::vector;

class vec3;
class vec2;
class vec4;

namespace EimathFn {
    void swap(float &v1,float &v2);
}

//using EimathFn::swap;






class vec2
{
public:
    
    float x;
    float y;
    
    
    vec2(float _x = 0, float _y = 0)
    {
        x = _x;
        y = _y;
    }
    
    vec2(const vec3& vec);
    
    float getLength(vec2 p)
    {
        return sqrt((p.x - x)*(p.x - x)+(p.y - y)*(p.y - y));
    }
    vec2 operator-(vec2 sub) const
    {
        return vec2(x-sub.x,y-sub.y);
    }
    vec2 operator+(vec2 add) const
    {
        return vec2(x+add.x,y+add.y);
    }
    
    vec2 operator*(float _x) const
    {
        return vec2(x * _x, y * _x);
    }
    
    vec2 operator*(vec2 p) const
    {
        return vec2(x * p.x, y* p.y);
    }
};

class vec3
{
public:
    float x,y,z;
    
    vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    
    vec3(const vec4& _vec4);
    vec3(const vec3& _vec3);
    
    vec3(float _x,float _y,float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    
    
    vec3 operator-(vec3 _vec3) const
    {
        return  vec3(x-_vec3.x,y-_vec3.y,z-_vec3.z);
    }
    

    
    vec3 operator/(float v) const
    {
        return vec3(x/v,y/v,z/v);
    }
    
    bool operator==(const vec3 _vec3) const
    {
        if(fabsf(x -_vec3.x) < _ESP0X10 && fabsf(y - _vec3.y) < _ESP0X10 && fabsf(z - _vec3.z) < _ESP0X10)
            return true;
        else
            return false;
    }
    
    vec3 operator*(float v) const
    {
        return vec3(x * v,y * v,z * v);
    }
    
    float dot(vec3 _vec3) const
    {
        return x*_vec3.x + y*_vec3.y + z*_vec3.z;
    }
    vec3 cross(const vec3 _vec3) const
    {
        return vec3(-y*_vec3.z+z*_vec3.y,-z*_vec3.x+x*_vec3.z,-x*_vec3.y+y*_vec3.x);
    }
    
    vec3 norm() const
    {
        return vec3(*this * (1.0/sqrt(x*x+y*y+z*z)));
    }
    
    float length() const
    {
        return sqrtf(x*x + y*y + z*z);
    }
};

class vec4
{
public:
    float r,g,b,a;
    
    vec4()
    {
        r = 0.0;
        g = 0.0;
        b = 0.0;
        a = 0.0;
    }
    vec4(const vec3& _vec3);
    
    vec4(float _r,float _g,float _b,float _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
    
    vec4 operator*(float e) const
    {
        return vec4(r*e,g*e,b*e,a);
    }
    
    vec4 operator*(vec4 _vec4) const
    {
        return vec4(r*_vec4.r,g*_vec4.g,b*_vec4.b,a);
    }
    
    vec4 operator+(vec4 add) const
    {
        return vec4(r+add.r,g+add.g,b+add.b,1);
    }
    
    vec4 operator/(float v) const
    {
        return vec4(r/v,g/v,b/v,a/v);
    }
    
    void operator+=(vec4 _vec4)
    {
        r += _vec4.r;
        g += _vec4.g;
        b += _vec4.b;
    }
};



class matrix3X3
{
    
public:
    
    float m11,m12,m13;
    float m21,m22,m23;
    float m31,m32,m33;
    
    matrix3X3()
    {
        m11 =1;
        m12 =0;
        m13 =0;
        
        m21 =0;
        m22 =1;
        m23 =0;
        
        m31 =0;
        m32 =0;
        m33 =1;
    }
    
    
    static matrix3X3 mul(const matrix3X3& mat1,const matrix3X3& mat2)
    {
        
        matrix3X3 mat3;
        mat3.m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 *mat2.m31;
        mat3.m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 *mat2.m32;
        mat3.m13 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 *mat2.m33;
        
        mat3.m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 *mat2.m31;
        mat3.m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 *mat2.m32;
        mat3.m23 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 *mat2.m33;
        
        mat3.m31 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 *mat2.m31;
        mat3.m32 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 *mat2.m32;
        mat3.m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 *mat2.m33;
        
        return mat3;
    }
    
    static vec3 mul(const matrix3X3& mat,const vec3& vec)
    {
        vec3 bVec;
        
        bVec.x = mat.m11* vec.x + mat.m12*vec.y + mat.m13 *vec.z;
        bVec.y = mat.m21* vec.x + mat.m22*vec.y + mat.m23 *vec.z;
        bVec.z = mat.m31* vec.x + mat.m32*vec.y + mat.m33 *vec.z;
        
        return bVec;
    }
    
    
};

class matrix4X4
{
public:
    
    float m11,m12,m13,m14;
    float m21,m22,m23,m24;
    float m31,m32,m33,m34;
    float m41,m42,m43,m44;
    
    matrix4X4()
    {
        m11 =1;
        m12 =0;
        m13 =0;
        m14 =0;
        
        m21 =0;
        m22 =1;
        m23 =0;
        m24 =0;
        
        m31 =0;
        m32 =0;
        m33 =1;
        m34 =0;
        
        m41 =0;
        m42 =0;
        m43 =0;
        m44 =1;
    }
    
    void transpose()
    {
        std::swap(m12, m21);
        std::swap(m13, m31);
        std::swap(m14, m41);
        
        std::swap(m23, m32);
        std::swap(m42, m24);
        std::swap(m43, m34);
    }
    
    static matrix4X4 mul(const matrix4X4& mat1,const matrix4X4& mat2)
    {
        
        matrix4X4 mat3;
        mat3.m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 *mat2.m31 + mat1.m14 * mat2.m41;
        mat3.m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 *mat2.m32 + mat1.m14 * mat2.m42;
        mat3.m13 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 *mat2.m33 + mat1.m14 * mat2.m43;
        mat3.m14 = mat1.m11 * mat2.m14 + mat1.m12 * mat2.m24 + mat1.m13 *mat2.m34 + mat1.m14 * mat2.m44;
        
        mat3.m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 *mat2.m31 + mat1.m24 * mat2.m41;
        mat3.m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 *mat2.m32 + mat1.m24 * mat2.m42;
        mat3.m23 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 *mat2.m33 + mat1.m24 * mat2.m43;
        mat3.m24 = mat1.m21 * mat2.m14 + mat1.m22 * mat2.m24 + mat1.m23 *mat2.m34 + mat1.m24 * mat2.m44;
        
        
        mat3.m31 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 *mat2.m31 + mat1.m34 * mat2.m41;
        mat3.m32 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 *mat2.m32 + mat1.m34 * mat2.m42;
        mat3.m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 *mat2.m33 + mat1.m34 * mat2.m43;
        mat3.m34 = mat1.m31 * mat2.m14 + mat1.m32 * mat2.m24 + mat1.m33 *mat2.m34 + mat1.m34 * mat2.m44;
        
        mat3.m41 = mat1.m41 * mat2.m11 + mat1.m42 * mat2.m21 + mat1.m43 *mat2.m31 + mat1.m44 * mat2.m41;
        mat3.m42 = mat1.m41 * mat2.m12 + mat1.m42 * mat2.m22 + mat1.m43 *mat2.m32 + mat1.m44 * mat2.m42;
        mat3.m43 = mat1.m41 * mat2.m13 + mat1.m42 * mat2.m23 + mat1.m43 *mat2.m33 + mat1.m44 * mat2.m43;
        mat3.m44 = mat1.m41 * mat2.m14 + mat1.m42 * mat2.m24 + mat1.m43 *mat2.m34 + mat1.m44 * mat2.m44;
        
        return mat3;
    }
    
    static vec4 mul(const matrix4X4& mat,const vec4& vec)
    {
        vec4 bVec;
        
        bVec.r = mat.m11* vec.r + mat.m12*vec.g + mat.m13 *vec.b + mat.m14 *vec.a;
        bVec.g = mat.m21* vec.r + mat.m22*vec.g + mat.m23 *vec.b + mat.m24 *vec.a;
        bVec.b = mat.m31* vec.r + mat.m32*vec.g + mat.m33 *vec.b + mat.m34 *vec.a;
        bVec.a = mat.m41* vec.r + mat.m42*vec.g + mat.m43 *vec.b + mat.m44 *vec.a;
        
        return bVec;
    }
    
    
};



#endif /* Eimath_h */
