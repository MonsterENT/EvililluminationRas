//
//  Ei_triangel.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/2/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "Ei_triangel.hpp"

Ei_triangel::Ei_triangel(vec2 _pA,vec2 _pB,vec2 _pC)
{
    pA = _pA;
    pB = _pB;
    pC = _pC;
    pointLine.resize(3);
    
    
    ProcessPoint();
    
}


void Ei_triangel::MatrixTransform(matrix3X3 &mat)
{
    pA = matrix3X3::mul(mat, vec3(pA.x,pA.y,1));
    pB = matrix3X3::mul(mat, vec3(pB.x,pB.y,1));
    pC = matrix3X3::mul(mat, vec3(pC.x,pC.y,1));
    
    ProcessPoint();
}

void Ei_triangel::draw()
{
    if((!flag_0 && !flag_1) || flag_0)
        //上半部分
        for(int y = pointLine[0].y;y>=pM.y;y--)
        {
            float start,end;
            
            if(Max_k_p0_p1 == true)
                start = pointLine[0].x;
            else
                
                start = (y - b_p0_p1)/k_p0_p1;
            if(Max_k_p0_p2 == true)
                end = pointLine[0].x;
            else
                end = (y - b_p0_p2)/k_p0_p2;
            this->chageStartEnd(start, end);
            for(int x = start;x<end;x++)
            {
                setPixel(vec2(x,y), lerpColor(vec2(x,y)));
            }
        }
    
    if((!flag_0 && !flag_1) || flag_1)
        //下半部分
        for(int y = pM.y;y>=pointLine[2].y;y--)
        {
            float start,end;
            if(Max_k_p2_p1 == true)
                start = pointLine[1].x;
            else
                start = (y - b_p2_p1)/k_p2_p1;
            
            if(Max_k_p0_p2 == true)
                end = pointLine[0].x;
            else
                end = (y - b_p0_p2)/k_p0_p2;
            this->chageStartEnd(start, end);
            for(int x = start;x<end;x++)
            {
                setPixel(vec2(x,y), lerpColor(vec2(x,y)));
            }
        }
    
    
}

void Ei_triangel::ProcessPoint()
{
    pointLine[0] = pA;
    pointLine[1] = pB;
    pointLine[2] = pC;
    
    
    Max_k_p0_p2 = false;
    Max_k_p2_p1 = false;
    Max_k_p0_p1 = false;
    
    
    std::sort(pointLine.begin(), pointLine.end(), Ei_triangelSort::comp);
    
    float midY = pointLine[1].y;
    
    //line p0,p2
    if(fabsf(pointLine[0].x - pointLine[2].x) < _ESP0X1)
    {
        k_p0_p2 = MAXFLOAT;
        Max_k_p0_p2 = true;
    }
    else
        k_p0_p2 = (pointLine[0].y - pointLine[2].y)/(pointLine[0].x - pointLine[2].x);
    
    b_p0_p2 = pointLine[0].y - k_p0_p2 * pointLine[0].x;
    
    pM = vec2((midY - b_p0_p2)/k_p0_p2,midY);
    
    //line p0,p1
    if(fabsf(pointLine[0].x - pointLine[1].x) < _ESP0X1)
    {
        k_p0_p1 = MAXFLOAT;
        Max_k_p0_p1 = true;
    }
    else
        k_p0_p1 = (pointLine[0].y - pointLine[1].y)/(pointLine[0].x - pointLine[1].x);
    
    b_p0_p1 = pointLine[0].y - k_p0_p1 * pointLine[0].x;
    
    
    //line p2,p1
    if(fabsf(pointLine[2].x - pointLine[1].x) <_ESP0X1)
    {
        k_p2_p1 = MAXFLOAT;
        Max_k_p2_p1 = true;
    }
    else
        k_p2_p1 = (pointLine[2].y - pointLine[1].y)/(pointLine[2].x - pointLine[1].x);
    
    b_p2_p1 = pointLine[2].y - k_p2_p1 * pointLine[2].x;
    
    flag_0 = false;
    flag_1 = false;
    
    if(fabsf(pointLine[1].y - pointLine[2].y) <_ESP0X5)//下底平
        flag_0 = true;
    else if(fabsf(pointLine[0].y - pointLine[1].y) <_ESP0X5)
        flag_1 = true;
    
}
