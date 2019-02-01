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
#include "EiRasObject.hpp"
#include "EiPrimitive/EiPrimitive.hpp"
#include "EiCommandBuffer/EiCommandBuffer.hpp"

extern vec2_Int frameSize;
extern vec2 dxy;

class EiPrimitive;
class EiCommandBuffer;
class EiCommand;

class EiRas : public EiRasObject
{
    friend EiCommandBuffer;
public:
    bool enableMerge;
    
    void initEi(vec2_Int frameSize);

    void setPixelWithDepthTest(vec2 p, float z, vec4 color);
    
    void presentToFile(const char* fileName);
    
    vec4* getFrameBuffer();
    float* getDepthBuffer();
    
    vec4 alphaMerge(vec4 _background, vec4 _foreground);
    
    bool sampleFrame(int x,int y,vec4 &Color);
    
    int hashCode()
    {
        return enableMerge;
    }
    
    static vec2_Int getFrameSize()
    {
        return frameSize;
    }
    
    static vec2 getFrameDxy()
    {
        return dxy;
    }
    
    void clearFrameAndDepth(vec4 clearColor);
    void drawPrimitives(EiPrimitive** primitives, int count);
    void drawPrimitive(EiPrimitive* primitive);
    void present();
    
private:
    EiCommandBuffer* commandBuffer;
    
    vec4* frame =  nullptr;
    float* depthBuffer = nullptr;
    
    matrix4X4 mat4X4Proj;
    matrix4X4 *mat4X4Camera;
    
    int NDC2FrameWidth,NDC2FrameHeight;
    
    void _clearFrameAndDepth(vec4& clearColor);
    void _drawPrimitives(EiPrimitive** primitives, int count);
    void _present(EiCommand** commands, int count);
    
    void setPixel(int x, int y, vec4 color);
    void setPixel(vec2 p, vec4 color);
    bool coordinate2frame(int &x, int &y);
    bool coordinate2frame(float &x, float &y);
};

#endif /* EiRas_hpp */
