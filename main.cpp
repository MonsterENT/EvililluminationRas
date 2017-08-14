//
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "Eimath.h"
#include "EiRas.hpp"
#include "Ei_line.hpp"
#include "Ei_triangel.hpp"
#include "Ei_triangel3D.hpp"
#include "Transform3D.hpp"
#include "EiLight.hpp"

#define Zfar 15.0

#define Znear 1

#define halfWidth 5.0/2.0
#define halfHeight 5.0/2.0

int main(int argc, const char * argv[])
{
    // 初始化 EiRas
    initEi();
    
    // 设置透视矩阵
    matrix4X4 proj;
    matMatrix44PerspectiveFovLH(proj, _PI/4.0, 1, Znear, Zfar);
    setProjMatrix(proj);
    
    
    // 2D 辅助线
    Line line1 = Line(-800,0,800,0);
    line1.color = vec4(1,1,1,1);
    line1.width = 2;
    line1.draw();
    
    Line line2 = Line(0,600,0,-600);
    line2.color = vec4(1,1,1,1);
    line2.width = 2;
    line2.draw();
    
    

    // 设置顶点光照
    EiLight* g_light = new EiLight;
    g_light->addPointLight(vec4(0.0,0.0,0.0,1), vec4(0.5,0.4,0.8,1), vec4(), vec3(0,0,9.5), 7, vec3(0.06,0.06,0.06));
    setEiLight(g_light);
    
    
    

    // 场景构建
    
    Ei_triangel3D bottom1 = Ei_triangel3D(vec3(-halfWidth,-halfHeight,Znear),vec3(halfWidth,-halfHeight,Zfar),vec3(halfWidth,-halfHeight,Znear));
    bottom1.colorA = ColorGray(0.4);
    bottom1.colorB = ColorGray(0.9);
    bottom1.colorC = ColorGray(0.4);
    bottom1.albedo = vec3(0.9,0.9,0.9);
    bottom1.normal = vec3(0,1,0);
    bottom1.draw();
    
    
    Ei_triangel3D bottom2 = Ei_triangel3D(vec3(-halfWidth,-halfHeight,Zfar),vec3(halfWidth,-halfHeight,Zfar),vec3(-halfWidth,-halfHeight,Znear));
    bottom2.colorA = ColorGray(0.4);
    bottom2.colorB = ColorGray(0.9);
    bottom2.colorC = ColorGray(0.4);
    bottom2.albedo = vec3(0.9,0.9,0.9);
    bottom2.normal = vec3(0,1,0);
    bottom2.draw();
    

    
    //两张纹理贴图   （为什么写在这？）瞎写呗
    EiTexture2D* tex1 = new EiTexture2D("RT.bmp");
    EiTexture2D* tex2 = new EiTexture2D("02180049.jpg");
    
    
    Ei_triangel3D left1 =Ei_triangel3D(vec3(-halfWidth,-halfHeight,Znear),vec3(-halfWidth,-halfHeight,Zfar),vec3(-halfWidth,+halfHeight,Zfar));
    left1.colorA = ColorGreen;
    left1.colorB = ColorRed;
    left1.colorC = ColorRed;
    left1.albedo = vec3(0.9,0,0);
    left1.normal = vec3(1,0,0);
    left1.TexA = vec2(0,1);
    left1.TexB = vec2(1,1);
    left1.TexC = vec2(1,0);
    left1.setTexture2D(true,tex2);
    left1.draw();
    
    
    Ei_triangel3D left2 =Ei_triangel3D(vec3(-halfWidth,-halfHeight,Znear),vec3(-halfWidth,+halfHeight,Zfar),vec3(-halfWidth,+halfHeight,Znear));
    left2.colorA = ColorRed;
    left2.colorB = ColorGray(1);
    left2.colorC = ColorRed;
    
    left2.albedo = vec3(0.9,0,0);
    left2.normal = vec3(1,0,0);
   
    left2.TexA = vec2(0,1);
    left2.TexB = vec2(1,0);
    left2.TexC = vec2(0,0);
    
    left2.setTexture2D(true,tex2);
    left2.draw();
    
    
    
    
    Ei_triangel3D right1 = Ei_triangel3D(vec3(halfWidth,-halfHeight,Znear),vec3(halfWidth,-halfHeight,Zfar),vec3(halfWidth,+halfHeight,Zfar));
    right1.colorA = ColorBlue;
    right1.colorB = ColorBlue;
    right1.colorC = ColorBlue;
    right1.albedo = vec3(0,0.9,0);
    right1.normal = vec3(-1,0,0);
    right1.TexA = vec2(1,1);
    right1.TexB = vec2(0,1);
    right1.TexC = vec2(0,0);
    right1.setTexture2D(true,tex2);
    
    right1.draw();
    
    
    
    Ei_triangel3D right2 = Ei_triangel3D(vec3((halfWidth+0.01),-halfHeight,Znear),vec3(halfWidth,+halfHeight,Znear),vec3(halfWidth,+halfHeight,Zfar));
    right2.colorA = ColorBlue;
    right2.colorB = ColorBlue;
    right2.colorC = ColorBlue;
    
    right2.albedo = vec3(0,0.9,0);
    right2.normal = vec3(-1,0,0);
    
    right2.TexA = vec2(1,1);
    right2.TexB = vec2(1,0);
    right2.TexC = vec2(0,0);
    right2.setTexture2D(true,tex2);
    
    right2.draw();
    

    
    
    
    Ei_triangel3D far2 = Ei_triangel3D(vec3(halfWidth,-halfHeight,Zfar),vec3((halfWidth),+halfHeight,Zfar),vec3(-halfWidth,+halfHeight,Zfar));//
    far2.colorA = ColorGray(0.6);
    far2.colorB = ColorGray(0.6);
    far2.colorC = ColorGreen;
    far2.albedo = vec3(0.6,0.6,0.6);
    far2.normal = vec3(0,0,-1);
    far2.TexA = vec2(1,1);
    far2.TexB = vec2(1,0);
    far2.TexC = vec2(0,0);
    far2.setTexture2D(true,tex1);

    
    // 3D 旋转 平移
    matrix4X4 _mat3Drotation;
    EiTransform3D::MatrixRotation3D(_mat3Drotation, vec3(0,1,0), vec3(halfWidth,-halfHeight,Zfar), _PI/4.0);
//    EiTransform3D::MatrixTranslation3D(_mat3Drotation, vec3(-500,0,-500));
//    far2.MatrixTransform(_mat3Drotation);
    
    far2.draw();
    

    Ei_triangel3D far1 = Ei_triangel3D(vec3(-halfWidth,-halfHeight,Zfar),vec3(halfWidth,-halfHeight,Zfar),vec3(-halfWidth,+halfHeight,Zfar));//
    far1.colorA = ColorGreen;
    far1.colorB = ColorGray(0.1);
    far1.colorC = ColorGray(0.1);
    far1.albedo = vec3(0.6,0.6,0.6);
    far1.normal = vec3(0,0,-1);
    far1.TexA = vec2(0,1);
    far1.TexB = vec2(1,1);
    far1.TexC = vec2(0,0);
    far1.setTexture2D(true,tex1);
    
    far1.draw();
    
    
    
    
    Ei_triangel3D top1 =Ei_triangel3D(vec3(-halfWidth,+halfHeight,Znear),vec3(halfWidth,+halfHeight,Zfar),vec3(halfWidth,+halfHeight,Znear));
    top1.colorA = ColorGray(0.4);
    top1.colorB = ColorGray(0.4);
    top1.colorC = ColorGray(0.4);
    top1.albedo = vec3(0.4,0.4,0.4);
    top1.normal = vec3(0,-1,0);
    top1.draw();
    
    
    Ei_triangel3D top2 =Ei_triangel3D(vec3(-halfWidth,+halfHeight,Zfar),vec3(halfWidth,+halfHeight,Zfar),vec3(-halfWidth,+halfHeight,Znear));//
    top2.colorA = ColorGray(0.4);
    top2.colorB = ColorGray(0.4);
    top2.colorC = ColorGray(0.4);
    
    top2.albedo = vec3(0.4,0.4,0.4);
    top2.normal = vec3(0,-1,0);
    top2.draw();
    

    
    
    // DepthView 和 RenderTargetView 写出至ppm文件
    
    char filename[50];
    sprintf(filename,"EiRasDepth.ppm");
    FILE *f = fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", g_width, g_height, 255);
    for (int i=0; i< g_width * g_height; i++)
        fprintf(f,"%d %d %d ", toInt(double(getDepthBuffer()[i])),toInt(double(getDepthBuffer()[i])), toInt(double(getDepthBuffer()[i])));
    fclose(f);
    
    
    sprintf(filename,"EiRas.ppm");
    f = fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", g_width, g_height, 255);
    
    for (int i=0; i< g_width * g_height; i++)
        fprintf(f,"%d %d %d ", toInt(getFrameBuffer()[i].r),toInt(getFrameBuffer()[i].g), toInt(getFrameBuffer()[i].b));
    
    fclose(f);

    return 0;
}



