//
//  Ei_triangel3D.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/7/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef Ei_triangel3D_hpp
#define Ei_triangel3D_hpp


#include "Eiobject.hpp"
#include "Eimath.h"
#include "EiLight.hpp"
#include "EiTexture2D.hpp"


class Ei_triangel3D : public Eiobject
{
public:
    vec3 pA,pB,pC;
    vec4 colorA,colorB,colorC;
    
    vec2 TexA,TexB,TexC;
    EiTexture2D* tex2D;
    
    
    
    vec3 albedo;
    vec3 normal;
    
    Ei_triangel3D(vec3 _pA,vec3 _pB,vec3 _pC);
    
    
    void MatrixTransform(matrix4X4 &mat);
    void setTexture2D(bool enabel=true,EiTexture2D* tex2D=NULL);
    
    void draw();
    
private:
    
    struct PointMap
    {
        vec3 projPoint;
        vec3 sourcePoint;
        vec2 Tex;
        PointMap()
        {
            projPoint = vec3();
            sourcePoint = vec3();
            Tex = vec2();
        }
        
        PointMap(vec3 _projPoint , vec3 _sourcePoint , vec2 _Tex)
        {
            this->projPoint = _projPoint;
            this->sourcePoint = _sourcePoint;
            this->Tex = _Tex;
        }
    };
    
    typedef struct PixelShaderIn
    {
        float x_start,
        x_end,
        y_start,
        y_end,
        z_start,
        z_end
        ;
        
        vec2 tex_start,
        tex_end
        ;
        
    }PixelShaderIn;
    
    
    vector<PointMap>pointLine;
    vec2 pM;
    float k_p0_p2,b_p0_p2; bool Max_k_p0_p2;
    float k_p0_p1,b_p0_p1; bool Max_k_p0_p1;
    float k_p2_p1,b_p2_p1; bool Max_k_p2_p1;
    
    bool flag_0;//下低平
    bool flag_1;//上底平
    
    
    inline vec4 lerpColor(vec2 p,vec3 _projA,vec3 _projB,vec3 _projC)
    {
        
        float v = ((p.y- _projA.y)*(_projB.x - _projA.x) + (_projA.y - _projB.y)*(p.x - _projA.x)) / ((_projC.y -_projA.y) * (_projB.x - _projA.x) - (_projA.y - _projB.y) *(_projA.x - _projC.x));
        
        float u = (p.x + (v-1.0)*_projA.x -v * _projC.x)/(_projB.x - _projA.x);
        
        return colorA*(u) + colorB*(v) + colorC*(1 - v - u);
    }
    
    
    void ProcessPoint(const PointMap& _pA,const PointMap&  _pB,const PointMap&  _pC);
    
    PixelShaderIn VertexLerpTop(float y);
    
    PixelShaderIn VertexLerpBottom(float y);
    
    static bool comp3D(const PointMap& obj1,const PointMap& obj2)
    {
        if(obj1.projPoint.y>obj2.projPoint.y)
            return true;
        else return false;
    }
    
    inline void chageStartEndWithZ(float &start,float &end,float &z_start,float &z_end,float &x_start,float &x_end,float &y_start,float &y_end,vec2 &Tex_start,vec2 &Tex_end)
    {
        float temp;
        if(start>end)
        {
            temp = start;
            start = end;
            end = temp;
        }
        else
        {
            temp = x_start;
            x_start = x_end;
            x_end = temp;
            
            temp = y_start;
            y_start = y_end;
            y_end = temp;
            
            temp = z_end;
            z_end = z_start;
            z_start =temp;
            
            temp = Tex_end.x;
            Tex_end.x = Tex_start.x;
            Tex_start.x = temp;
            
            temp = Tex_end.y;
            Tex_end.y = Tex_start.y;
            Tex_start.y = temp;
            
        }
        
    }
    
};


#endif /* Ei_triangel3D_hpp */
