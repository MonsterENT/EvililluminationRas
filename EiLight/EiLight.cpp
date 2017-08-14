//
//  EiLight.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/14/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "EiLight.hpp"


EiLight::EiLight()
{
    
    
}


EiLight::~EiLight()
{
    
    
}


size_t EiLight::dirLightNum()
{
    return dirLights.size();
}

void EiLight::addDirLight(vec4 ambient,vec4 diffuse,vec4 specular,vec3 dir)
{
    DirLight light;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    light.dir = dir;
    
    dirLights.push_back(light);
}

void EiLight::addDirLight(DirLight &light)
{
    dirLights.push_back(light);
}

void EiLight::addPointLight(vec4 ambient,vec4 diffuse,vec4 specular,vec3 pos,float range,vec3 att)
{
    PointLight light;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    light.pos = pos;
    light.range = range;
    light.att = att;
    
    pointLights.push_back(light);
}


vec4 EiLight::computLight(vec3 pos,vec3 normal,vec3 albedo)
{
    vec4 ambient,diffuse;
    
    for(int i =0;i<dirLights.size();i++)
    {
        computeDirLights(pos,normal, albedo, dirLights[i],ambient,diffuse);
    }
    
    for(int i =0;i<pointLights.size();i++)
        computePointLights(pos, normal, albedo, pointLights[i], ambient, diffuse);
    
    return ambient + diffuse;
}

void EiLight::computeDirLights(vec3 pos,vec3 normal,vec4 albedo,const DirLight &dirLight,vec4 &out_ambient,vec4 &out_diffuse)
{
    
    //环境光直接计算
    out_ambient += albedo * dirLight.ambient;
    
    //计算漫反射系数
    //注意：计算前保证法线、光线方向归一化
    
    float diffFactor = -normal.dot(dirLight.dir);
    
    //如果系数小于0（即顶点背着光源），则不再进行计算
    
    if (diffFactor > 0)
    {
        //计算漫反射光
        out_diffuse += albedo * dirLight.diffuse * diffFactor;
    }
}


void EiLight::computePointLights(vec3 pos,vec3 normal,vec4 albedo,const PointLight &pointLight,vec4 &out_ambient,vec4 &out_diffuse)
{

    //计算光照方向：顶点->光源
    vec3 dir = pointLight.pos - pos;
    
    //计算顶点到光源距离
    float dist = dir.length();
    
    //超过照射范围，则不再进行计算
    if(dist > pointLight.range)
        return;
    
    //归一化光线方向
    dir = dir.norm();
    
    //计算光强的衰减
    float att = 1/(pointLight.att.x + pointLight.att.y*dist + pointLight.att.z*dist*dist);
    
    //计算环境光
    out_ambient += albedo * pointLight.ambient * att;
    
    //计算漫反射系数
    float diffFactor = dir.dot(normal);
    
    //如果小于0，直接退出
    
    if(diffFactor > 0)
    {
        //计算漫反射光
        out_diffuse += albedo * pointLight.diffuse *att;
    }
    
    
}




