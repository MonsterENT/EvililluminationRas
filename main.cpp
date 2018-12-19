//
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "EiRas/EiRasHeaders.h"
#define Zfar 100.0

#define Znear 1

#define halfWidth 50.0
#define halfHeight 50.0


//vec4* source;
//vec4 getSrc(int x,int y);

//EiRas* device = nullptr;
int main(int argc, const char * argv[])
{
//    EiTriangel* t = new EiTriangel(vec2(0,0),vec2(0,0),vec2(0,0));
    // 初始化 EiRas
//    initEi();
    
//    enableAlphaMerge();
    
    // 设置透视矩阵
//    matrix4X4 proj;
//    matMatrix44PerspectiveFovLH(proj, _PI/4.0, 1, Znear, Zfar);
//    setProjMatrix(proj);
    
//    EiCamera* Camera = new EiCamera(vec3(0,0,0),vec3(0,0,1),Znear,Zfar);
//    Camera->RotateByUp(_PI/2.0);
//    Camera->RotateByRight(_PI/18.0);
//    Camera->RotateByForward(_PI/4.0);
//    Camera->MoveRight(10);
//    Camera->MoveUp(10);
//    Camera->MoveForward(100);

    

//    setCamera(Camera);
    
    
//    // 2D 辅助线
//    Line line1 = Line(-800,0,800,0);
//    line1.color = vec4(1,1,1,1);
//    line1.width = 2;
//    line1.draw();
//
//    Line line2 = Line(0,600,0,-600);
//    line2.color = vec4(1,1,1,1);
//    line2.width = 2;
//    line2.draw();
//
//
    
    // 设置顶点光照
    //    EiLight* g_light = new EiLight;
    //    g_light->addPointLight(vec4(0.0,0.0,0.0,1), vec4(0.5,0.4,0.8,1), vec4(), vec3(0,0,9.5), 7, vec3(0.06,0.06,0.06));
    //    setEiLight(g_light);
    
    //
//    EiTexture2D* tex1 = new EiTexture2D("RT.bmp");
//    tex1->enableMipmap();
//
//    EiTexture2D* texQP = new EiTexture2D("QP.png");
//    texQP->enableMipmap();
//
//    EiTexture2D* tex2 = new EiTexture2D("02180049.jpg");
//    tex2->enableMipmap();
    // 场景构建
    
    //    Ei_triangel3D bottom1 = Ei_triangel3D(vec3(-halfWidth,-halfHeight,Znear+20),vec3(halfWidth,-halfHeight,Zfar+20),vec3(halfWidth,-halfHeight,Znear+20));
    //    bottom1.colorA = ColorGray(0.4);
    //    bottom1.colorB = ColorGray(0.9);
    //    bottom1.colorC = ColorGray(0.4);
    //    bottom1.albedo = vec3(0.9,0.9,0.9);
    //    bottom1.normal = vec3(0,1,0);
    //
    //    bottom1.TexA = vec2(0,1000);
    //    bottom1.TexB = vec2(1,0);
    //    bottom1.TexC = vec2(1,1000);
    //    bottom1.setTexture2D(tex2,EiTexAddressingMode::AddressingMode_Warp,0);
    //    bottom1.draw();
    //
    //
    //    Ei_triangel3D bottom2 = Ei_triangel3D(vec3(-halfWidth,-halfHeight,Zfar+20),vec3(halfWidth,-halfHeight,Zfar+20),vec3(-halfWidth,-halfHeight,Znear+20));
    //    bottom2.colorA = ColorGray(0.4);
    //    bottom2.colorB = ColorGray(0.9);
    //    bottom2.colorC = ColorGray(0.4);
    //    bottom2.albedo = vec3(0.9,0.9,0.9);
    //    bottom2.normal = vec3(0,1,0);
    //
    //    bottom2.TexA = vec2(0,0);
    //    bottom2.TexB = vec2(1,0);
    //    bottom2.TexC = vec2(0,1000);
    //    bottom2.setTexture2D(tex2,EiTexAddressingMode::AddressingMode_Warp,0);
    //    bottom2.draw();
    //
    
    
    
    
    
    //    Ei_triangel3D left1 =Ei_triangel3D(vec3(-halfWidth,-halfHeight,Znear),vec3(-halfWidth,-halfHeight,Zfar),vec3(-halfWidth,+halfHeight,Zfar));
    //    left1.colorA = ColorGreen;
    //    left1.colorB = ColorRed;
    //    left1.colorC = ColorRed;
    //    left1.albedo = vec3(0.9,0,0);
    //    left1.normal = vec3(1,0,0);
    //    left1.TexA = vec2(0,1);
    //    left1.TexB = vec2(1,1);
    //    left1.TexC = vec2(1,0);
    //    left1.setTexture2D(true,tex2);
    //    left1.draw();
    //
    //
    //    Ei_triangel3D left2 =Ei_triangel3D(vec3(-halfWidth,-halfHeight,Znear),vec3(-halfWidth,+halfHeight,Zfar),vec3(-halfWidth,+halfHeight,Znear));
    //    left2.colorA = ColorRed;
    //    left2.colorB = ColorGray(1);
    //    left2.colorC = ColorRed;
    //
    //    left2.albedo = vec3(0.9,0,0);
    //    left2.normal = vec3(1,0,0);
    //
    //    left2.TexA = vec2(0,1);
    //    left2.TexB = vec2(1,0);
    //    left2.TexC = vec2(0,0);
    //
    //    left2.setTexture2D(true,tex2);
    //    left2.draw();
    //
    //
    //
    //
    //    Ei_triangel3D right1 = Ei_triangel3D(vec3(halfWidth,-halfHeight,Znear),vec3(halfWidth,-halfHeight,Zfar),vec3(halfWidth,+halfHeight,Zfar));
    //    right1.colorA = ColorBlue;
    //    right1.colorB = ColorBlue;
    //    right1.colorC = ColorBlue;
    //    right1.albedo = vec3(0,0.9,0);
    //    right1.normal = vec3(-1,0,0);
    //    right1.TexA = vec2(1,1);
    //    right1.TexB = vec2(0,1);
    //    right1.TexC = vec2(0,0);
    //    right1.setTexture2D(true,tex2);
    //
    //    right1.draw();
    //
    //
    //
    //    Ei_triangel3D right2 = Ei_triangel3D(vec3((halfWidth+0.01),-halfHeight,Znear),vec3(halfWidth,+halfHeight,Znear),vec3(halfWidth,+halfHeight,Zfar));
    //    right2.colorA = ColorBlue;
    //    right2.colorB = ColorBlue;
    //    right2.colorC = ColorBlue;
    //
    //    right2.albedo = vec3(0,0.9,0);
    //    right2.normal = vec3(-1,0,0);
    //
    //    right2.TexA = vec2(1,1);
    //    right2.TexB = vec2(1,0);
    //    right2.TexC = vec2(0,0);
    //    right2.setTexture2D(true,tex2);
    //
    //    right2.draw();
    
//    matrix4X4 mat;
//    EiTransform3D::MatrixRotation3D(mat, vec3(0,0,1), vec3(0,0,200), -_PI/2.0);
//
//
//    Ei_triangel3D far2 = Ei_triangel3D(vec3(halfWidth,-halfHeight,200),vec3((halfWidth),+halfHeight,200),vec3(-halfWidth,+halfHeight,200));//
//    far2.TexA = vec2(1,1);
//    far2.TexB = vec2(1,0);
//    far2.TexC = vec2(0,0);
//    far2.setTexture2D(tex1,EiTexAddressingMode::AddressingMode_Warp,0);
//
//
////    far2.draw();
//
//
//    Ei_triangel3D far1 = Ei_triangel3D(vec3(-halfWidth,-halfHeight,200),vec3(halfWidth,-halfHeight,200),vec3(-halfWidth,+halfHeight,200));//
//    far1.TexA = vec2(0,1);
//    far1.TexB = vec2(1,1);
//    far1.TexC = vec2(0,0);
//    far1.setTexture2D(tex1,EiTexAddressingMode::AddressingMode_Warp,0);
//
////    far1.draw();
//
//
//
////    far2.MatrixTransform(mat);
////    far1.MatrixTransform(mat);
//    far2.draw();
//    far1.draw();
    //    Ei_triangel3D far3 = Ei_triangel3D(vec3(halfWidth,-halfHeight,100),vec3((halfWidth),+halfHeight,100),vec3(-halfWidth,+halfHeight,100));//
    //    far3.TexA = vec2(1,1);
    //    far3.TexB = vec2(1,0);
    //    far3.TexC = vec2(0,0);
    //    far3.setTexture2D(tex2,EiTexAddressingMode::AddressingMode_Warp,0);
    //
    //    far3.alpha = 0.2;
    //    far3.draw();
    //
    //
    //    Ei_triangel3D far4 = Ei_triangel3D(vec3(-halfWidth,-halfHeight,100),vec3(halfWidth,-halfHeight,100),vec3(-halfWidth,+halfHeight,100));//
    //    far4.TexA = vec2(0,1);
    //    far4.TexB = vec2(1,1);
    //    far4.TexC = vec2(0,0);
    //    far4.setTexture2D(tex2,EiTexAddressingMode::AddressingMode_Warp,0);
    //
    //    far4.alpha = 0.2;
    //    far4.draw();
    
    
    //    Ei_triangel3D top1 =Ei_triangel3D(vec3(-halfWidth,+halfHeight,Znear),vec3(halfWidth,+halfHeight,Zfar),vec3(halfWidth,+halfHeight,Znear));
    //    top1.colorA = ColorGray(0.4);
    //    top1.colorB = ColorGray(0.4);
    //    top1.colorC = ColorGray(0.4);
    //    top1.albedo = vec3(0.4,0.4,0.4);
    //    top1.normal = vec3(0,-1,0);
    //    top1.draw();
    //
    //
    //    Ei_triangel3D top2 =Ei_triangel3D(vec3(-halfWidth,+halfHeight,Zfar),vec3(halfWidth,+halfHeight,Zfar),vec3(-halfWidth,+halfHeight,Znear));//
    //    top2.colorA = ColorGray(0.4);
    //    top2.colorB = ColorGray(0.4);
    //    top2.colorC = ColorGray(0.4);
    //
    //    top2.albedo = vec3(0.4,0.4,0.4);
    //    top2.normal = vec3(0,-1,0);
    //    top2.draw();
    //
    
//    disableAlphaMerge();
    
//    EiEffect* effectV = new EiEffect();
//    
//    vec4* frameBlur =  getFrameBuffer();//effectV->EiEffect_FullScreenBlur(10, 5);
    
    
    // DepthView 和 RenderTargetView 写出至ppm文件

//    present();
    
    return 0;
}


