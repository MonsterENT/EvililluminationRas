//
//  EiEffect.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 9/15/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "EiEffect.hpp"


vec4* EiEffect::EiEffect_FullScreenBlur(int Radius,int blurtime)
{
    vec4* frameBlur = new vec4[g_width*g_height];
    
    vec4* frameFinal = new vec4[g_width*g_height];
    
    
    vec4* source = getFrameBuffer();
    
    for(int times=0;times <blurtime;times++)
    {
        
        for(int i=0;i<g_width;i++)
            for(int j=0;j<g_height;j++)
            {
                vec4 all = vec4();
                for(int r = 0;r<Radius;r++)
                {
                    all += getSrc(source, i-r, j);
                }
                
                for(int r = 1;r<Radius;r++)
                {
                    all += getSrc(source,i+r, j);
                }
                
                all =vec4(all.r/(float)(2.0*Radius-1.0),all.g/(float)(2.0*Radius-1.0),all.b/(float)(2.0*Radius-1.0),1);
                
                frameBlur[j * g_width + i] = all;
            }
        
        source = frameBlur;
        
        for(int i=0;i<g_width;i++)
            for(int j=0;j<g_height;j++)
            {
                vec4 all = vec4();
                for(int r = 0;r<Radius;r++)
                {
                    all += getSrc(source,i, j-r);
                }
                
                for(int r = 1;r<Radius;r++)
                {
                    all += getSrc(source,i, j+r);
                }
                
                all =vec4(all.r/(float)(2.0*Radius-1.0),all.g/(float)(2.0*Radius-1.0),all.b/(float)(2.0*Radius-1.0),1);
                
                frameFinal[j * g_width + i] = all;
            }
        source = frameFinal;
    }
    
    frameBlur = frameFinal;
    
    return frameBlur;
}



vec4 EiEffect::getSrc(vec4* source,int x,int y)
{
    if(x >= g_width || x < 0 || y < 0 || y>=g_height)
        return vec4(0,0,0,1);
    else
        return source[y * g_width + x];
}
