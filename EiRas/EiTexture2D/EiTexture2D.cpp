//
//  EiTexture2D.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 8/9/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "EiTexture2D.hpp"

bool getFromTex(int x, int y, vector<vec4*> &tex, int height, int width, vec4 &color);

void EiTexture2D::enableMipmap()
{
    isEnableMipmap = true;
    
    mipmapLine.resize(MAX_mipmapCount);
    
    mipmapLine[0].tex2D = tex2Dframe;
    mipmapLine[0].height = height;
    mipmapLine[0].width = width;
    createMipmap();
    
}

void EiTexture2D::createMipmap()
{
    for(int mipmapLevel = 1; mipmapLevel < MAX_mipmapCount; mipmapLevel++)
    {
        int height = mipmapLine[mipmapLevel - 1].height / 2;
        int width = mipmapLine[mipmapLevel - 1].width / 2;
        
        if(height > 0 && width > 0)
        {
            MipmapCount ++;
            mipmapLine[mipmapLevel].height = height;
            mipmapLine[mipmapLevel].width = width;
            
            mipmapLine[mipmapLevel].tex2D.resize(height);
            for(int i = 0; i < height; i++)
            {
                mipmapLine[mipmapLevel].tex2D[i] = new vec4[width];
            }
            
            for(int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    vec4 color = vec4();
                    color = isSampleTex(j * 2, i * 2 ,mipmapLevel - 1);
                    mipmapLine[mipmapLevel].tex2D[i][j] = color;
                }
            }
        }
    }
}

int EiTexture2D::getMipmapCount()
{
    return MipmapCount;
}

EiTexture2D::EiTexture2D(string fileName)
{
//    mipmapLine.resize(1);
//
//    CvMat* img = cvLoadImageM(fileName.c_str());
//    if(!img) return;
//
//    height = img->height;
//    width = img->width;
//
//    height = height /2 * 2;
//    width = width / 2 * 2;
//
//    tex2Dframe.resize(img->height);
//    for(int i =0;i<img->height;i++)
//        tex2Dframe[i] = new vec4[img->width];
//
//    CvScalar cs;                               //声明像素变量
//    for(int i = 0; i < img->height; i++)
//        for (int j = 0; j < img->width; j++)
//        {
//            cs = cvGet2D(img, i, j);
//            tex2Dframe[i][j] = vec4(cs.val[2]/255.0,cs.val[1]/255.0,cs.val[0]/255.0,1);
//        }
//
//    isEnableMipmap = false;
//    MipmapCount = 1;
    
}


EiTexture2D::~EiTexture2D()
{
    for(int i =0;i<tex2Dframe.size();i++)
        delete[] tex2Dframe[i];
    
}

vec4 EiTexture2D::getColorByUV(vec2 UV,EiTexAddressingMode mode,int mipmapLevel,vec2 OffsetXY)
{
    if(mode == EiTexAddressingMode::AddressingMode_Warp)
    {
        if(UV.x > 1)
        {
            UV.x -= floorf(UV.x);
        }
        if(UV.y > 1)
        {
            UV.y -= floorf(UV.y);
        }
    }
    else if(mode == EiTexAddressingMode::AddressingMode_Mirror)
    {
        if(UV.x >1)
        {
            if((int)UV.x % 2 == 1)
            {
                UV.x = floorf(UV.x) + 1 - UV.x;
            }
            else
            {
                UV.x -= floorf(UV.x);
            }
        }
        if(UV.y > 1)
        {
            if((int)UV.y % 2 == 1)
            {
                UV.y = floorf(UV.y) + 1 - UV.y;
            }
            else
            {
                UV.y -= floorf(UV.y);
            }

        }
    }
    
    float curMipmapLevel = mipmapLevel;
    
    if(mipmapLevel == -1) // 计算Level
    {
        
        float TexPreSSPixel;
        
        if(OffsetXY.x > OffsetXY.y)
        {
            TexPreSSPixel = OffsetXY.x * width;
        }
        else
        {
            TexPreSSPixel = OffsetXY.y * height;
        }
        
        if(TexPreSSPixel < 1.0)
        {
            curMipmapLevel = 0;
        }
        else
        {
            static const float fInvLog2 = 1.0f / logf(2.0f);
            curMipmapLevel = logf(TexPreSSPixel) * fInvLog2;
        }
    }
    
    curMipmapLevel -= 0.5; //bias
    
    if(curMipmapLevel < 0)
    {
        curMipmapLevel = 0;
    }
    if(curMipmapLevel >= MipmapCount)
    {
        curMipmapLevel = MipmapCount - 1;
        UV.x *= (float)width / powf(2.0, MipmapCount - 1);
        UV.y *= (float)height / powf(2.0, MipmapCount - 1);
        vec4 color = isSampleTex(UV.x, UV.y, MipmapCount - 1);
        color.a = 1;
        return color;
    }
    
    
    if(mipmapLevel != -1)
    {
        UV.x *= (float)width / powf(2.0, curMipmapLevel);
        UV.y *= (float)height / powf(2.0, curMipmapLevel);
        vec4 color = isSampleTex(UV.x, UV.y, curMipmapLevel);
        color.a = 1;
        return color;
    }
    
    
    float levelOffset = curMipmapLevel - (int)curMipmapLevel;
    int mipmapLevelA = (int)curMipmapLevel;
    int mipmapLevelB = (int)curMipmapLevel + 1;
    
    vec4 colorA = isSampleTex(UV.x * (float)width / powf(2.0, mipmapLevelA), UV.y*(float)width / powf(2.0, mipmapLevelA), mipmapLevelA);
    colorA.a = 1;
    
    vec4 colorB = isSampleTex(UV.x * (float)width / powf(2.0, mipmapLevelB), UV.y*(float)width / powf(2.0, mipmapLevelB), mipmapLevelB);
    colorB.a = 1;
    
    return colorB*levelOffset + colorA * (1.0 - levelOffset);
}

vec4 EiTexture2D::isSampleTex(float x, float y, int mipmapLevel)
{
    
    vector<vec4*> &tex = mipmapLine[mipmapLevel].tex2D;
    int height = mipmapLine[mipmapLevel].height;
    int width = mipmapLine[mipmapLevel].width;
    vec4 color = vec4();
    
    int SampleCount = 0;
    
    if(getFromTex(x - 1.0, y, tex, height, width, color))
    {
        SampleCount++;
    }
    
    if(getFromTex(x + 1.0, y, tex, height, width, color))
    {
        SampleCount++;
    }
    
    if(getFromTex(x, y + 1.0, tex, height, width, color))
    {
        SampleCount++;
    }
    
    if(getFromTex(x, y - 1.0, tex, height, width, color))
    {
        SampleCount++;
    }
    
    if(getFromTex(x, y, tex, height, width, color))
    {
        SampleCount++;
    }
    
    if(SampleCount != 0)
    {
        color = color / ((float)SampleCount);
    }
    else
    {
        return vec4(1,1,1,1);
    }
    
    return color;
}

bool getFromTex(int x,int y,vector<vec4*> &tex, int height,int width, vec4 &color)
{
    
    if(x > 0 && x < width && y > 0 && y < height)
    {
        color += tex[y][x];
        return true;
    }
    return false;
}
