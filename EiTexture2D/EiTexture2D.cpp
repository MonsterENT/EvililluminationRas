//
//  EiTexture2D.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 8/9/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "EiTexture2D.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>




EiTexture2D::EiTexture2D(string fileName)
{
    CvMat* img = cvLoadImageM(fileName.c_str());
    if(!img) return;
    
    height = img->height;
    width = img->width;
    
    tex2Dframe.resize(img->height);
    for(int i =0;i<img->height;i++)
        tex2Dframe[i] = new vec4[img->width];
    
    CvScalar cs;                               //声明像素变量
    for(int i = 0; i < img->height; i++)
        for (int j = 0; j < img->width; j++)
        {
            cs = cvGet2D(img, i, j);
            tex2Dframe[i][j] = vec4(cs.val[2]/255.0,cs.val[1]/255.0,cs.val[0]/255.0,1);
        }
    
    
}


EiTexture2D::~EiTexture2D()
{
    for(int i =0;i<tex2Dframe.size();i++)
        delete tex2Dframe[i];
    
}

vec4 EiTexture2D::getColorByUV(vec2 UV)
{
    UV.x *= (float)width;
    UV.y *= (float)height;
    
    if(UV.x >0 && UV.x < width && UV.y > 0 && UV.y< height)
        return tex2Dframe[(int)UV.y][(int)UV.x];
    
    else return vec4();
}




