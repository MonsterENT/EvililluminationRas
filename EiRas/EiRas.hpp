//
//  EiRas.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/1/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef EiRas_hpp
#define EiRas_hpp

#include "Eimath.h"
#include "EiLight.hpp"

#define g_width (800)
#define g_height (600)

#define ColorRed vec4(1,0,0,1);
#define ColorGreen vec4(0,1,0,1);
#define ColorBlue vec4(0,0,1,1);
#define ColorGray(x) vec4(x,x,x,1)


inline double clamp(double x){
    return x<0 ? 0 : x>1 ? 1 : x;
}
inline int toInt(double x)
{
    return int(pow(clamp(x),1/2.2)*255+.5);
}



void initEi();

void setPixel(int x,int y,vec4 color);
void setPixel(vec2 p,vec4 color);
void setPixelWithDepthTest(vec2 p,float z,vec4 color);

bool coordinate2frame(int &x, int &y);
bool coordinate2frame(float &x, float &y);

vec4* getFrameBuffer();
float* getDepthBuffer();


void matMatrix44PerspectiveFovLH(matrix4X4 &mat, const float fov, const float Aspect, const float ZNear, const float ZFar );
void setProjMatrix(matrix4X4 mat);
vec4 Ei_Proj(vec4 point);


void setEiLight(EiLight* _EiLight);
EiLight* getEiLight();



void enableAlphaMerge();
void disableAlphaMerge();

#endif /* EiRas_hpp */
