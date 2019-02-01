//
//  EiMath.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiMath_hpp
#define EiMath_hpp

#include "../EiMacro.h"
#include <math.h>
#include "../EiRasObject.hpp"

class vec2;
class vec3;
class vec4;

namespace EiMath_Q {
    
    template<typename T>void swap(T& a, T& b)
    {
        T tmp = b;
        b = a;
        a = tmp;
    }
    
    typedef bool(EiQsortCompare)(const void* obj1, const void* obj2);
    
    inline bool EiQsortIntCompare(const void* obj1, const void* obj2)
    {
        if(*((int*)obj1) < *((int*)obj2))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    template<typename T> void _qSort(T* array, int left, int right, EiQsortCompare compareFunc)
    {
        if(left > right)
        {
            return;
        }
        
        int mid = (right - left) / 2 + left;
        
        swap<T>(array[mid], array[right]);
        
        int count = left;
        for(int i = left; i < right; i++)
        {
            if(compareFunc(&array[i],&array[right]))
            {
                if(i != count)
                {
                    swap<T>(array[i], array[count]);
                }
                count++;
            }
        }
        swap<T>(array[right], array[count]);
        mid = count;
        _qSort(array, left, mid - 1, compareFunc);
        _qSort(array, mid + 1, right, compareFunc);
    }
    
    template<typename T> void qSort(T* array, int len, EiQsortCompare compareFunc)
    {
        if(array && len > 0)
        {
            _qSort(array, 0, len - 1, compareFunc);
        }
    }
    
    inline double clamp(double x){
        return x < 0 ? 0 : x > 1 ? 1 : x;
    }
    
    inline int toInt(double x)
    {
        return int(pow(clamp(x), 1 / 2.2) * 255 + .5);
    }
}

class vec2_Int : public EiRasObject
{
public:
    int x;
    int y;
    vec2_Int(int _x = 0, int _y = 0)
    {
        x = _x;
        y = _y;
    }
};

class vec2 : public EiRasObject
{
public:
    
    float x;
    float y;
    
    vec2(float _x = 0, float _y = 0)
    {
        x = _x;
        y = _y;
    }
    
    vec2(const vec3& _vec3);
    
    float getLength(const vec2 &p)
    {
        return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
    }
    vec2 operator-(vec2 sub) const
    {
        return vec2(x - sub.x, y - sub.y);
    }
    vec2 operator+(vec2 add) const
    {
        return vec2(x + add.x, y + add.y);
    }
    
    vec2 operator*(float _x) const
    {
        return vec2(x * _x, y * _x);
    }
    
    vec2 operator*(vec2 p) const
    {
        return vec2(x * p.x, y * p.y);
    }
};

class vec3 : public EiRasObject
{
public:
    float x, y, z;
    
    vec3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    
    vec3(const vec4& _vec4);
    
    vec3(const vec3& _vec3);
    
    vec3(const vec2& _vec2, float _z);
    
    vec3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    
    vec3 operator-(vec3 _vec3) const
    {
        return  vec3(x - _vec3.x, y - _vec3.y, z - _vec3.z);
    }
    
    vec3 operator/(float v) const
    {
        return vec3(x / v, y / v, z / v);
    }
    
    bool operator==(const vec3 _vec3) const
    {
        if(fabsf(x -_vec3.x) < _ESP0X10 && fabsf(y - _vec3.y) < _ESP0X10 && fabsf(z - _vec3.z) < _ESP0X10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    void operator+=(const vec3 _vec3)
    {
        this->x += _vec3.x;
        this->y += _vec3.y;
        this->z += _vec3.z;
    }
    
    vec3 operator*(float v) const
    {
        return vec3(x * v,y * v,z * v);
    }
    
    float dot(const vec3& _vec3) const
    {
        return x *_vec3.x + y * _vec3.y + z * _vec3.z;
    }
    vec3 cross(const vec3& _vec3) const
    {
        return vec3(-y * _vec3.z + z * _vec3.y, -z * _vec3.x + x * _vec3.z, -x * _vec3.y + y * _vec3.x);
    }
    
    vec3 norm() const
    {
        return vec3( * this * (1.0 / sqrt(x * x + y * y + z * z)));
    }
    
    float length() const
    {
        return sqrtf(x * x + y * y + z * z);
    }
};

class vec4 : public EiRasObject
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
    vec4(const vec3& _vec3)
    {
        r = _vec3.x;
        g = _vec3.y;
        b = _vec3.z;
        a = 1;
    }
    
    vec4(float _r,float _g,float _b,float _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
    
    vec4 operator*(float e) const
    {
        return vec4(r * e, g * e, b * e, a);
    }
    
    vec4 operator*(vec4 _vec4) const
    {
        return vec4(r * _vec4.r, g * _vec4.g, b * _vec4.b, a);
    }
    
    vec4 operator+(vec4 add) const
    {
        return vec4(r + add.r, g + add.g, b + add.b, 1);
    }
    
    vec4 operator/(float v) const
    {
        return vec4(r / v, g / v, b / v, a / v);
    }
    
    void operator+=(vec4 _vec4)
    {
        r += _vec4.r;
        g += _vec4.g;
        b += _vec4.b;
    }
    
    void operator/=(float v)
    {
        r /= v;
        g /= v;
        b /= v;
    }
};

class matrix2X2 : public EiRasObject
{
public:
    float m11,m12;
    float m21,m22;
    
    matrix2X2()
    {
        m11 = 1;
        m12 = 0;
        
        m21 = 0;
        m22 = 1;
    }
    
    static matrix2X2 mul(const matrix2X2& mat1,const matrix2X2& mat2)
    {
        matrix2X2 mat3;
        mat3.m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21;
        mat3.m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22;
        
        mat3.m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21;
        mat3.m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22;
        
        return mat3;
    }
    
    static vec2 mul(const matrix2X2& mat,const vec2& vec)
    {
        vec2 bVec;
        
        bVec.x = mat.m11 * vec.x + mat.m12 * vec.y;
        bVec.y = mat.m21 * vec.x + mat.m22 * vec.y;
        
        return bVec;
    }
};

class matrix3X3 : public EiRasObject
{
    
public:
    
    float m11,m12,m13;
    float m21,m22,m23;
    float m31,m32,m33;
    
    matrix3X3()
    {
        m11 = 1;
        m12 = 0;
        m13 = 0;
        
        m21 = 0;
        m22 = 1;
        m23 = 0;
        
        m31 = 0;
        m32 = 0;
        m33 = 1;
    }
    
    
    static matrix3X3 mul(const matrix3X3& mat1,const matrix3X3& mat2)
    {
        matrix3X3 mat3;
        mat3.m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 * mat2.m31;
        mat3.m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 * mat2.m32;
        mat3.m13 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 * mat2.m33;
        
        mat3.m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 * mat2.m31;
        mat3.m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 * mat2.m32;
        mat3.m23 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 * mat2.m33;
        
        mat3.m31 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 * mat2.m31;
        mat3.m32 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 * mat2.m32;
        mat3.m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 * mat2.m33;
        
        return mat3;
    }
    
    static vec3 mul(const matrix3X3& mat,const vec3& vec)
    {
        vec3 bVec;
        
        bVec.x = mat.m11 * vec.x + mat.m12 * vec.y + mat.m13 * vec.z;
        bVec.y = mat.m21 * vec.x + mat.m22 * vec.y + mat.m23 * vec.z;
        bVec.z = mat.m31 * vec.x + mat.m32 * vec.y + mat.m33 * vec.z;
        
        return bVec;
    }
};

class matrix4X4 : public EiRasObject
{
public:
    
    float m11,m12,m13,m14;
    float m21,m22,m23,m24;
    float m31,m32,m33,m34;
    float m41,m42,m43,m44;
    
    matrix4X4()
    {
        m11 = 1;
        m12 = 0;
        m13 = 0;
        m14 = 0;
        
        m21 = 0;
        m22 = 1;
        m23 = 0;
        m24 = 0;
        
        m31 = 0;
        m32 = 0;
        m33 = 1;
        m34 = 0;
        
        m41 = 0;
        m42 = 0;
        m43 = 0;
        m44 = 1;
    }
    
    void transpose()
    {
        EiMath_Q::swap(m12, m21);
        EiMath_Q::swap(m13, m31);
        EiMath_Q::swap(m14, m41);
        
        EiMath_Q::swap(m23, m32);
        EiMath_Q::swap(m42, m24);
        EiMath_Q::swap(m43, m34);
    }
    
    static matrix4X4 mul(const matrix4X4& mat1,const matrix4X4& mat2)
    {
        matrix4X4 mat3;
        
        mat3.m11 = mat1.m11 * mat2.m11 + mat1.m12 * mat2.m21 + mat1.m13 * mat2.m31 + mat1.m14 * mat2.m41;
        mat3.m12 = mat1.m11 * mat2.m12 + mat1.m12 * mat2.m22 + mat1.m13 * mat2.m32 + mat1.m14 * mat2.m42;
        mat3.m13 = mat1.m11 * mat2.m13 + mat1.m12 * mat2.m23 + mat1.m13 * mat2.m33 + mat1.m14 * mat2.m43;
        mat3.m14 = mat1.m11 * mat2.m14 + mat1.m12 * mat2.m24 + mat1.m13 * mat2.m34 + mat1.m14 * mat2.m44;
        
        mat3.m21 = mat1.m21 * mat2.m11 + mat1.m22 * mat2.m21 + mat1.m23 * mat2.m31 + mat1.m24 * mat2.m41;
        mat3.m22 = mat1.m21 * mat2.m12 + mat1.m22 * mat2.m22 + mat1.m23 * mat2.m32 + mat1.m24 * mat2.m42;
        mat3.m23 = mat1.m21 * mat2.m13 + mat1.m22 * mat2.m23 + mat1.m23 * mat2.m33 + mat1.m24 * mat2.m43;
        mat3.m24 = mat1.m21 * mat2.m14 + mat1.m22 * mat2.m24 + mat1.m23 * mat2.m34 + mat1.m24 * mat2.m44;
        
        
        mat3.m31 = mat1.m31 * mat2.m11 + mat1.m32 * mat2.m21 + mat1.m33 * mat2.m31 + mat1.m34 * mat2.m41;
        mat3.m32 = mat1.m31 * mat2.m12 + mat1.m32 * mat2.m22 + mat1.m33 * mat2.m32 + mat1.m34 * mat2.m42;
        mat3.m33 = mat1.m31 * mat2.m13 + mat1.m32 * mat2.m23 + mat1.m33 * mat2.m33 + mat1.m34 * mat2.m43;
        mat3.m34 = mat1.m31 * mat2.m14 + mat1.m32 * mat2.m24 + mat1.m33 * mat2.m34 + mat1.m34 * mat2.m44;
        
        mat3.m41 = mat1.m41 * mat2.m11 + mat1.m42 * mat2.m21 + mat1.m43 * mat2.m31 + mat1.m44 * mat2.m41;
        mat3.m42 = mat1.m41 * mat2.m12 + mat1.m42 * mat2.m22 + mat1.m43 * mat2.m32 + mat1.m44 * mat2.m42;
        mat3.m43 = mat1.m41 * mat2.m13 + mat1.m42 * mat2.m23 + mat1.m43 * mat2.m33 + mat1.m44 * mat2.m43;
        mat3.m44 = mat1.m41 * mat2.m14 + mat1.m42 * mat2.m24 + mat1.m43 * mat2.m34 + mat1.m44 * mat2.m44;
        
        return mat3;
    }
    
    static vec4 mul(const matrix4X4& mat,const vec4& vec)
    {
        vec4 bVec;
        
        bVec.r = mat.m11 * vec.r + mat.m12 * vec.g + mat.m13 * vec.b + mat.m14 * vec.a;
        bVec.g = mat.m21 * vec.r + mat.m22 * vec.g + mat.m23 * vec.b + mat.m24 * vec.a;
        bVec.b = mat.m31 * vec.r + mat.m32 * vec.g + mat.m33 * vec.b + mat.m34 * vec.a;
        bVec.a = mat.m41 * vec.r + mat.m42 * vec.g + mat.m43 * vec.b + mat.m44 * vec.a;
        
        return bVec;
    }
};

#endif /* EiMath_hpp */
