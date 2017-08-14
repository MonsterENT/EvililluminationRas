//
//  EiLight.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/14/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef EiLight_hpp
#define EiLight_hpp

#include "Eimath.h"
#include <vector>
using std::vector;

//平行光
struct DirLight
{
    vec4	ambient;	//环境光
    vec4	diffuse;	//漫反射光
    vec4	specular;	//高光
    
    vec3	dir;		//方向
};

//点光源
struct PointLight
{
    vec4	ambient;	//环境光
    vec4	diffuse;	//漫反射光
    vec4	specular;	//高光
    
    vec3	pos;		//光源位置
    float	range;		//光源照射范围
    
    vec3	att;		//光强衰减系数
};


class EiLight
{
public:
    
    EiLight();
    ~EiLight();

    
    size_t dirLightNum();
    
    void addDirLight(vec4 ambient,vec4 diffuse,vec4 specular,vec3 dir);
    void addDirLight(DirLight &light);
    
    void addPointLight(vec4 ambient,vec4 diffuse,vec4 specular,vec3 pos,float range,vec3 att);
    
    vec4 computLight(vec3 pos/*保留*/,vec3 normal,vec3 albedo);
    
private:
    vector<DirLight> dirLights;
    vector<PointLight> pointLights;
    
    void computeDirLights(vec3 pos,vec3 normal,vec4 albedo,const DirLight &dirLight,vec4 &out_ambient,vec4 &out_diffuse);
    
    void computePointLights(vec3 pos,vec3 normal,vec4 albedo,const PointLight &pointLight,vec4 &out_ambient,vec4 &out_diffuse);
};


#endif /* EiLight_hpp */

