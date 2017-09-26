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
#include "EiCamrea.hpp"

#define g_width (800)
#define g_height (600)

#define ColorRed vec4(1,0,0,1);
#define ColorGreen vec4(0,1,0,1);
#define ColorBlue vec4(0,0,1,1);
#define ColorGray(x) vec4(x,x,x,1)

#define MSAA4X 16

#define reduceY (1.0/(float)g_height)
#define reduceX (1.0/(float)g_width)

#define WidthGapMSAA4X (1.0/(float)(NDC2FrameWidth))
#define HeightGapMSAA4X (1.0/(float)(NDC2FrameHeight))

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

void present();


bool coordinate2frame(int &x, int &y);
bool coordinate2frame(float &x, float &y);

vec4* getFrameBuffer();
float* getDepthBuffer();


void setCamera(EiCamera* Camera);
void setProjMatrix(matrix4X4 mat);
vec4 Ei_Proj(vec4 point);


void setEiLight(EiLight* _EiLight);
EiLight* getEiLight();



void enableAlphaMerge();
void disableAlphaMerge();

#endif /* EiRas_hpp */
