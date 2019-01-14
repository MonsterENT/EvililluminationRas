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
#include "EiRas/EiDependence/RingBuffer.hpp"
#include "EiRas/EiDependence/EiThread/EiThreadHelper.hpp"

EiRas* device = nullptr;

int main(int argc, const char * argv[])
{
    device = new EiRas;
    
    device->initEi(vec2_Int(1600, 1200));
    
    device->clearFrameAndDepth(ColorGray(0));
    EiTriangel2D* triangel = new EiTriangel2D(vec2(0, 0), vec2(1, 1), vec2(-1, 1));
    triangel->colorA = ColorRed;
    triangel->colorB = ColorBlue;
    triangel->colorC = ColorGreen;
    
    device->drawPrimitive(triangel);
    
    matrix3X3 mat;
    mat.m23 = 0.5;
    triangel->MatrixTransform(mat);
    triangel->colorB = ColorGray(1);
    
    device->drawPrimitive(triangel);
    
    
    EiLine* lineH = new EiLine(vec2(-1, 0), vec2(1, 0));
    lineH->width = 0.01f;
    
    EiLine* lineV = new EiLine(vec2(0, 1), vec2(0, -1));
    lineV->width = 0.01f;
    
    EiLine* lineF2 = new EiLine(vec2(-0.5, 0.5), vec2(0.5, -0.5));
    lineF2->width = 0.001f;
    lineF2->color = ColorBlue;
    
    
//    device->drawPrimitive(lineH);
//    device->drawPrimitive(lineV);
//    device->drawPrimitive(lineF2);
    
    device->present();
    
    //avoid main thread quit
    while (1) {
    }
//    const char* fileName = "OutPutFile.ppm";
    
//    device->presentToFile(fileName);

    return 0;
}


