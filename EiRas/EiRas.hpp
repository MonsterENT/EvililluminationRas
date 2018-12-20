//
//  EiRas.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiRas_hpp
#define EiRas_hpp

#include "EiMacro.h"
#include "EiMath/EiMath.hpp"

class EiRas
{
public:
    
    bool enabelMerge;
    
    void initEi();
    
    void setPixel(int x, int y, vec4 color);
    void setPixel(vec2 p, vec4 color);
    void setPixelWithDepthTest(vec2 p, float z, vec4 color);
    
    void presentToFile(const char* fileName);
    
    bool coordinate2frame(int &x, int &y);
    bool coordinate2frame(float &x, float &y);
    
    vec4* getFrameBuffer();
    float* getDepthBuffer();
    
    vec4 alphaMerge(vec4 _background, vec4 _foreground);
    
    bool sampleFrame(int x,int y,vec4 &Color);
    
private:
    vec4* frame =  nullptr;
    
    float* depthBuffer = nullptr;
    
    matrix4X4 mat4X4Proj;
    matrix4X4 *mat4X4Camera;
    
    int NDC2FrameWidth,NDC2FrameHeight;
    int MSAASqrt;
};

#endif /* EiRas_hpp */
