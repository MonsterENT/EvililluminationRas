//
//  EiMath.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiMath.hpp"

vec2::vec2(const vec3& _vec3)
{
    x = _vec3.x;
    y = _vec3.y;
}

vec3::vec3(const vec4& _vec4)
{
    x = _vec4.r;
    y = _vec4.g;
    z = _vec4.b;
}

vec3::vec3(const vec3& _vec3)
{
    x = _vec3.x;
    y = _vec3.y;
    z = _vec3.z;
}

vec3::vec3(const vec2& _vec2, float _z)
{
    x = _vec2.x;
    y = _vec2.y;
    z = _z;
}
