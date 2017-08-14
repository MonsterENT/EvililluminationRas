//
//  Eimath.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "Eimath.h"

void EimathFn::swap(float &v1,float &v2)
{
    float temp = v2;
    v2 = v1;
    v1 = temp;
}


vec2::vec2(const vec3& _vec3)
{
    this->x = _vec3.x;
    this->y = _vec3.y;
}


vec3::vec3(const vec4& _vec4)
{
    this->x = _vec4.r;
    this->y = _vec4.g;
    this->z = _vec4.b;
}
vec3::vec3(const vec3& _vec3)
{
    this->x = _vec3.x;
    this->y = _vec3.y;
    this->z = _vec3.z;
}

vec4::vec4(const vec3& _vec3)
{
    this->r = _vec3.x;
    this->g = _vec3.y;
    this->b = _vec3.z;
    this->a = 1;
}
