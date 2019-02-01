//
//  EiTriangel.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/19.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiTriangel2D.hpp"

bool triangel2DSortCompare(const void* obj1, const void* obj2)
{
    vec2* o1 = (vec2*)obj1;
    vec2* o2 = (vec2*)obj2;
    
    if(o1->y > o2->y)
    {
        return true;
    }
    return false;
}

EiTriangel2D::EiTriangel2D(vec2 _pA,vec2 _pB,vec2 _pC)
{
    pA = _pA;
    pB = _pB;
    pC = _pC;
    
    ProcessPoint();
}

void EiTriangel2D::MatrixTransform(const matrix3X3& mat)
{
    pA = matrix3X3::mul(mat, vec3(pA,1));
    pB = matrix3X3::mul(mat, vec3(pB,1));
    pC = matrix3X3::mul(mat, vec3(pC,1));

    ProcessPoint();
}

void EiTriangel2D::draw(EiRas* device)
{
    if((!flag_0 && !flag_1) || flag_0)
    {
        //上半部分
        for(float y = pointLine[0].y; y >= pM.y; y -= EiRas::getFrameDxy().y)
        {
            float start, end;
            
            if(Max_k_p0_p1 == true)
            {
                start = pointLine[0].x;
            }
            else
            {
                start = (y - b_p0_p1) / k_p0_p1;
            }
            if(Max_k_p0_p2 == true)
            {
                end = pointLine[0].x;
            }
            else
            {
                end = (y - b_p0_p2) / k_p0_p2;
            }
            this->chageStartEnd(start, end);
            for(float x = start; x < end; x += EiRas::getFrameDxy().x)
            {
                device->setPixelWithDepthTest(vec2(x,y), 0, lerpColor(vec2(x,y)));
            }
        }
    }
    if((!flag_0 && !flag_1) || flag_1)
    {
        //下半部分
        for(float y = pM.y; y >= pointLine[2].y; y -= EiRas::getFrameDxy().y)
        {
            float start, end;
            if(Max_k_p2_p1 == true)
            {
                start = pointLine[1].x;
            }
            else
            {
                start = (y - b_p2_p1) / k_p2_p1;
            }
            
            if(Max_k_p0_p2 == true)
            {
                end = pointLine[0].x;
            }
            else
            {
                end = (y - b_p0_p2) / k_p0_p2;
            }
            this->chageStartEnd(start, end);
            for(float x = start; x < end; x += EiRas::getFrameDxy().x)
            {
                device->setPixelWithDepthTest(vec2(x, y), 0, lerpColor(vec2(x, y)));
            }
        }
    }
}

void EiTriangel2D::ProcessPoint()
{
    pointLine[0] = pA;
    pointLine[1] = pB;
    pointLine[2] = pC;
    
    Max_k_p0_p2 = false;
    Max_k_p2_p1 = false;
    Max_k_p0_p1 = false;
    
    EiMath_Q::qSort(pointLine, 3, triangel2DSortCompare);
    
    float midY = pointLine[1].y;
    
    //line p0,p2
    if(fabsf(pointLine[0].x - pointLine[2].x) < _ESP0X1)
    {
        k_p0_p2 = MAXFLOAT;
        Max_k_p0_p2 = true;
    }
    else
    {
        k_p0_p2 = (pointLine[0].y - pointLine[2].y)/(pointLine[0].x - pointLine[2].x);
    }
    
    b_p0_p2 = pointLine[0].y - k_p0_p2 * pointLine[0].x;
    
    pM = vec2((midY - b_p0_p2)/k_p0_p2,midY);
    
    //line p0,p1
    if(fabsf(pointLine[0].x - pointLine[1].x) < _ESP0X1)
    {
        k_p0_p1 = MAXFLOAT;
        Max_k_p0_p1 = true;
    }
    else
    {
        k_p0_p1 = (pointLine[0].y - pointLine[1].y) / (pointLine[0].x - pointLine[1].x);
    }
    
    b_p0_p1 = pointLine[0].y - k_p0_p1 * pointLine[0].x;
    
    //line p2,p1
    if(fabsf(pointLine[2].x - pointLine[1].x) <_ESP0X1)
    {
        k_p2_p1 = MAXFLOAT;
        Max_k_p2_p1 = true;
    }
    else
    {
        k_p2_p1 = (pointLine[2].y - pointLine[1].y) / (pointLine[2].x - pointLine[1].x);
    }
    
    b_p2_p1 = pointLine[2].y - k_p2_p1 * pointLine[2].x;
    
    flag_0 = false;
    flag_1 = false;
    
    if(fabsf(pointLine[1].y - pointLine[2].y) < _ESP0X5)//下底平
    {
        flag_0 = true;
    }
    else if(fabsf(pointLine[0].y - pointLine[1].y) < _ESP0X5)
    {
        flag_1 = true;
    }
}
