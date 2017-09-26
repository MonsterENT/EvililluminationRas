//
//  Ei_triangel3D.cpp
//  EvililluminationRas
//
//  Created by MonsterENT on 7/7/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#include "Ei_triangel3D.hpp"


Ei_triangel3D::Ei_triangel3D(vec3 _pA,vec3 _pB,vec3 _pC)
{
    disableLight = false;
    tex2D = NULL;
    
    alpha = 1;
    
    pA = _pA;
    pB = _pB;
    pC = _pC;
    
    pointLine.resize(3);
}


void Ei_triangel3D::MatrixTransform(matrix4X4 &mat)
{
    pA = matrix4X4::mul(mat, pA);
    pB = matrix4X4::mul(mat, pB);
    pC = matrix4X4::mul(mat, pC);
}



void Ei_triangel3D::setTexture2D(EiTexture2D* tex2D,EiTexAddressingMode mode,int mipmapLevel)
{
    this->tex2D = tex2D;
    this->addressingMode = mode;
    this->i_mipmapLevel = mipmapLevel;
}

Ei_triangel3D::PixelShaderIn Ei_triangel3D::VertexLerpTop(float y)
{
    PixelShaderIn data;
    
    float s_start = fabsf(pointLine[0].projPoint.y-y) /fabsf(pointLine[0].projPoint.y - pointLine[1].projPoint.y);
    
    data.z_start = 1.0/((1.0/pointLine[1].sourcePoint.z - 1.0/pointLine[0].sourcePoint.z) * s_start + 1.0/pointLine[0].sourcePoint.z);
    
    float s_end = fabsf(pointLine[0].projPoint.y-y) / fabsf(pointLine[0].projPoint.y - pointLine[2].projPoint.y);
    
    data.z_end = 1.0/((1.0/pointLine[2].sourcePoint.z - 1.0/pointLine[0].sourcePoint.z) * s_end + 1.0/pointLine[0].sourcePoint.z);
    
    
    
    data.x_start = (pointLine[0].sourcePoint.x/pointLine[0].sourcePoint.z + s_start*(pointLine[1].sourcePoint.x/pointLine[1].sourcePoint.z - pointLine[0].sourcePoint.x/pointLine[0].sourcePoint.z)) * data.z_start;
    
    data.x_end = ((pointLine[2].sourcePoint.x/pointLine[2].sourcePoint.z - pointLine[0].sourcePoint.x/pointLine[0].sourcePoint.z) * s_end + pointLine[0].sourcePoint.x/pointLine[0].sourcePoint.z) *data.z_end;
    
    
    data.y_start = (pointLine[0].sourcePoint.y/pointLine[0].sourcePoint.z + s_start*(pointLine[1].sourcePoint.y/pointLine[1].sourcePoint.z - pointLine[0].sourcePoint.y/pointLine[0].sourcePoint.z)) * data.z_start;
    
    data.y_end = ((pointLine[2].sourcePoint.y/pointLine[2].sourcePoint.z - pointLine[0].sourcePoint.y/pointLine[0].sourcePoint.z) * s_end + pointLine[0].sourcePoint.y/pointLine[0].sourcePoint.z) *data.z_end;
    
    
    if(this->tex2D)
    {
        data.tex_start.x = (pointLine[0].Tex.x/pointLine[0].sourcePoint.z + s_start*(pointLine[1].Tex.x/pointLine[1].sourcePoint.z - pointLine[0].Tex.x/pointLine[0].sourcePoint.z)) * data.z_start;
        
        data.tex_end.x = ((pointLine[2].Tex.x/pointLine[2].sourcePoint.z - pointLine[0].Tex.x/pointLine[0].sourcePoint.z) * s_end + pointLine[0].Tex.x/pointLine[0].sourcePoint.z) *data.z_end;
        
        
        data.tex_start.y = (pointLine[0].Tex.y/pointLine[0].sourcePoint.z + s_start*(pointLine[1].Tex.y/pointLine[1].sourcePoint.z - pointLine[0].Tex.y/pointLine[0].sourcePoint.z)) * data.z_start;
        
        data.tex_end.y = ((pointLine[2].Tex.y/pointLine[2].sourcePoint.z - pointLine[0].Tex.y/pointLine[0].sourcePoint.z) * s_end + pointLine[0].Tex.y/pointLine[0].sourcePoint.z) *data.z_end;
    }
    return data;
}


Ei_triangel3D::PixelShaderIn Ei_triangel3D::VertexLerpBottom(float y)
{
    PixelShaderIn data;
    
    float s_start = fabsf(pointLine[1].projPoint.y-y) /fabsf(pointLine[1].projPoint.y - pointLine[2].projPoint.y);
    
    data.z_start = 1.0/((1.0/pointLine[2].sourcePoint.z - 1.0/pointLine[1].sourcePoint.z) * s_start  + 1.0/pointLine[1].sourcePoint.z);
    
    
    float s_end =  fabsf(pointLine[0].projPoint.y-y)
    /fabsf(pointLine[0].projPoint.y - pointLine[2].projPoint.y);
    data.z_end = 1.0/((1.0/pointLine[2].sourcePoint.z - 1.0/pointLine[0].sourcePoint.z) * s_end  + 1.0/pointLine[0].sourcePoint.z);
    
    
    data.x_start = (pointLine[1].sourcePoint.x/pointLine[1].sourcePoint.z + s_start *(pointLine[2].sourcePoint.x/pointLine[2].sourcePoint.z - pointLine[1].sourcePoint.x/pointLine[1].sourcePoint.z)) * data.z_start;
    
    data.x_end = ((pointLine[2].sourcePoint.x/pointLine[2].sourcePoint.z - pointLine[0].sourcePoint.x/pointLine[0].sourcePoint.z) * s_end + pointLine[0].sourcePoint.x/pointLine[0].sourcePoint.z) * data.z_end;
    //
    data.y_start = (pointLine[1].sourcePoint.y/pointLine[1].sourcePoint.z + s_start *(pointLine[2].sourcePoint.y/pointLine[2].sourcePoint.z - pointLine[1].sourcePoint.y/pointLine[1].sourcePoint.z)) * data.z_start;
    
    data.y_end = ((pointLine[2].sourcePoint.y/pointLine[2].sourcePoint.z - pointLine[0].sourcePoint.y/pointLine[0].sourcePoint.z) * s_end + pointLine[0].sourcePoint.y/pointLine[0].sourcePoint.z) * data.z_end;
    
    if(this->tex2D)
    {
        data.tex_start.x = (pointLine[1].Tex.x/pointLine[1].sourcePoint.z + s_start*(pointLine[2].Tex.x/pointLine[2].sourcePoint.z - pointLine[1].Tex.x/pointLine[1].sourcePoint.z)) * data.z_start;
        
        data.tex_end.x = ((pointLine[2].Tex.x/pointLine[2].sourcePoint.z - pointLine[0].Tex.x/pointLine[0].sourcePoint.z) * s_end + pointLine[0].Tex.x/pointLine[0].sourcePoint.z) *data.z_end;
        
        
        data.tex_start.y = (pointLine[1].Tex.y/pointLine[1].sourcePoint.z + s_start*(pointLine[2].Tex.y/pointLine[2].sourcePoint.z - pointLine[1].Tex.y/pointLine[1].sourcePoint.z)) * data.z_start;
        
        data.tex_end.y = ((pointLine[2].Tex.y/pointLine[2].sourcePoint.z - pointLine[0].Tex.y/pointLine[0].sourcePoint.z) * s_end + pointLine[0].Tex.y/pointLine[0].sourcePoint.z) *data.z_end;
    }
    
    return data;
    
}



void Ei_triangel3D::draw()
{
    vec4 tempA = Ei_Proj(this->pA);
    vec3 pA = vec3(tempA.r/tempA.a,tempA.g/tempA.a,tempA.b/tempA.a);
    
    
    vec4 tempB = Ei_Proj(this->pB);
    vec3 pB = vec3(tempB.r/tempB.a,tempB.g/tempB.a,tempB.b/tempB.a);
    
    
    vec4 tempC = Ei_Proj(this->pC);
    vec3 pC = vec3(tempC.r/tempC.a,tempC.g/tempC.a,tempC.b/tempC.a);
    
    
    PointMap MapA(pA,this->pA,TexA);
    PointMap MapB(pB,this->pB,TexB);
    PointMap MapC(pC,this->pC,TexC);
    
    
    ProcessPoint(MapA,MapB,MapC);
    
    
    EiLight* light = getEiLight();
    if(disableLight)
        light = NULL;
    
    
    if((!flag_0 && !flag_1) || flag_0)
        //上半部分
        
        for(float y = pointLine[0].projPoint.y;y>=pM.y;y-=reduceY)
        {
            
            //clip
            if(y <-1 || y>1)
                continue;
            
            float start,end;
            
            if(Max_k_p0_p1 == true)
                start = pointLine[0].projPoint.x;
            
            else
                start = (y - b_p0_p1)/k_p0_p1;
            
            if(Max_k_p0_p2 == true)
                end = pointLine[0].projPoint.x;
            
            else
                end = (y - b_p0_p2)/k_p0_p2;
            
            
            
            //lerp
            PixelShaderIn pixelIn = VertexLerpTop(y);
            
            
            //
            this->chageStartEndWithZ(start,end,pixelIn.z_start,pixelIn.z_end,pixelIn.x_start,pixelIn.x_end,pixelIn.y_start,pixelIn.y_end,pixelIn.tex_start,pixelIn.tex_end);
            
            
            
            for(float x = start;x<end;x+=reduceX)
            {
                if(x <-1 || x>1)
                    continue;
                
                float z = 1.0/( (x-start) / (end - start) * (1.0/pixelIn.z_start - 1.0/pixelIn.z_end) + 1.0/pixelIn.z_end);
                
                float worldX = ( (x-start) / (end - start) * (pixelIn.x_start/pixelIn.z_start - pixelIn.x_end/pixelIn.z_end) + pixelIn.x_end/pixelIn.z_end) * z;
                
                float worldY = ( (x-start) / (end - start) * (pixelIn.y_start/pixelIn.z_start - pixelIn.y_end/pixelIn.z_end) + pixelIn.y_end/pixelIn.z_end) * z;
                
                
                if(tex2D)
                {
                    vec2 TexCoord;
                    TexCoord.x = ( (x-start) / (end - start) * (pixelIn.tex_start.x/pixelIn.z_start - pixelIn.tex_end.x/pixelIn.z_end) + pixelIn.tex_end.x/pixelIn.z_end) * z;
                    TexCoord.y = ( (x-start) / (end - start) * (pixelIn.tex_start.y/pixelIn.z_start - pixelIn.tex_end.y/pixelIn.z_end) + pixelIn.tex_end.y/pixelIn.z_end) * z;
                    
                    float ddx = (pixelIn.tex_start.x/pixelIn.z_start - pixelIn.tex_end.x/pixelIn.z_end)/ (end - start)*z/(float)g_width*2.0;
                    float ddy = (pixelIn.tex_start.y/pixelIn.z_start - pixelIn.tex_end.y/pixelIn.z_end)/ (end - start)*z/(float)g_width*2.0;
                    
                    vec4 i_Color = tex2D->getColorByUV(vec2(TexCoord.x,TexCoord.y),addressingMode,this->i_mipmapLevel,vec2(ddx,ddy));
                    i_Color.a = alpha;
                    setPixelWithDepthTest(vec2(x,y), z, i_Color);
                }
                else
                {
                    if(light)
                    {
                        vec4 i_Color = light->computLight(vec3(worldX,worldY,z), normal, albedo);
                        i_Color.a = alpha;
                        setPixelWithDepthTest(vec2(x,y), z, i_Color);
                    }
                    else
                        setPixelWithDepthTest(vec2(x,y), z, colorA);
                    
                }
            }
        }
    
    if((!flag_0 && !flag_1) || flag_1)
        //下半部分
        for(float y = pM.y;y>=pointLine[2].projPoint.y;y-=reduceY)
        {
            
            //clip
            if(y <-1 || y>1)
                continue;
            
            
            float start,end;
            
            if(Max_k_p2_p1 == true)
                start = pointLine[1].projPoint.x;
            else
                start = (y - b_p2_p1)/k_p2_p1;
            
            
            if(Max_k_p0_p2 == true)
                end = pointLine[0].projPoint.x;
            else
                end = (y - b_p0_p2)/k_p0_p2;
            
            
            //lerp
            
            PixelShaderIn pixelIn = VertexLerpBottom(y);
            
            //
            
            this->chageStartEndWithZ(start, end,pixelIn.z_start,pixelIn.z_end,pixelIn.x_start,pixelIn.x_end,pixelIn.y_start,pixelIn.y_end,pixelIn.tex_start,pixelIn.tex_end);
            
            
            for(float x = start;x<end;x+=reduceX)
            {
                if(x <-1 || x>1)
                    continue;
                
                float z = 1.0/( (x-start) / (end - start) * (1.0/pixelIn.z_start - 1.0/pixelIn.z_end) + 1.0/pixelIn.z_end);
                
                float worldX = ( (x-start) / (end - start) * (pixelIn.x_start/pixelIn.z_start - pixelIn.x_end/pixelIn.z_end) + pixelIn.x_end/pixelIn.z_end) * z;
                float worldY = ( (x-start) / (end - start) * (pixelIn.y_start/pixelIn.z_start - pixelIn.y_end/pixelIn.z_end) + pixelIn.y_end/pixelIn.z_end) * z;
                
                
                if(tex2D)
                {
                    vec2 TexCoord;
                    TexCoord.x = ( (x-start) / (end - start) * (pixelIn.tex_start.x/pixelIn.z_start - pixelIn.tex_end.x/pixelIn.z_end) + pixelIn.tex_end.x/pixelIn.z_end) * z;
                    TexCoord.y = ( (x-start) / (end - start) * (pixelIn.tex_start.y/pixelIn.z_start - pixelIn.tex_end.y/pixelIn.z_end) + pixelIn.tex_end.y/pixelIn.z_end) * z;
                    
                    float ddx = (pixelIn.tex_start.x/pixelIn.z_start - pixelIn.tex_end.x/pixelIn.z_end)/ (end - start)*z/(float)g_width*2.0;
                    float ddy = (pixelIn.tex_start.y/pixelIn.z_start - pixelIn.tex_end.y/pixelIn.z_end)/ (end - start)*z/(float)g_width*2.0;
                    
                    vec4 i_Color = tex2D->getColorByUV(vec2(TexCoord.x,TexCoord.y),addressingMode,this->i_mipmapLevel,vec2(ddx,ddy));
                    i_Color.a = alpha;
                    setPixelWithDepthTest(vec2(x,y), z, i_Color);
                }
                
                else
                {
                    if(light)
                    {
                        vec4 i_Color = light->computLight(vec3(worldX,worldY,z), normal, albedo);
                        i_Color.a = alpha;
                        setPixelWithDepthTest(vec2(x,y), z, i_Color);
                    }
                    else
                        setPixelWithDepthTest(vec2(x,y), z, colorA);
                    
                }
            }
        }
}




void  Ei_triangel3D::ProcessPoint(const PointMap& _pA,const PointMap&  _pB,const PointMap&  _pC)
{
    pointLine[0] = _pA;
    pointLine[1] = _pB;
    pointLine[2] = _pC;
    
    
    Max_k_p0_p2 = false;
    Max_k_p2_p1 = false;
    Max_k_p0_p1 = false;
    
    
    std::sort(pointLine.begin(), pointLine.end(), comp3D);
    
    float midY = pointLine[1].projPoint.y;
    
    //line p0,p2
    if(fabsf(pointLine[0].projPoint.x - pointLine[2].projPoint.x) < _ESP0X1)
    {
        k_p0_p2 = MAXFLOAT;
        Max_k_p0_p2 = true;
    }
    else
        k_p0_p2 = (pointLine[0].projPoint.y - pointLine[2].projPoint.y)/(pointLine[0].projPoint.x - pointLine[2].projPoint.x);
    
    b_p0_p2 = pointLine[0].projPoint.y - k_p0_p2 * pointLine[0].projPoint.x;
    
    pM = vec2((midY - b_p0_p2)/k_p0_p2,midY);
    
    //line p0,p1
    if(fabsf(pointLine[0].projPoint.x - pointLine[1].projPoint.x) < _ESP0X1)
    {
        k_p0_p1 = MAXFLOAT;
        Max_k_p0_p1 = true;
    }
    else
        k_p0_p1 = (pointLine[0].projPoint.y - pointLine[1].projPoint.y)/(pointLine[0].projPoint.x - pointLine[1].projPoint.x);
    
    b_p0_p1 = pointLine[0].projPoint.y - k_p0_p1 * pointLine[0].projPoint.x;
    
    
    //line p2,p1
    if(fabsf(pointLine[2].projPoint.x - pointLine[1].projPoint.x) <_ESP0X1)
    {
        k_p2_p1 = MAXFLOAT;
        Max_k_p2_p1 = true;
    }
    else
        k_p2_p1 = (pointLine[2].projPoint.y - pointLine[1].projPoint.y)/(pointLine[2].projPoint.x - pointLine[1].projPoint.x);
    
    b_p2_p1 = pointLine[2].projPoint.y - k_p2_p1 * pointLine[2].projPoint.x;
    
    flag_0 = false;
    flag_1 = false;
    
    if(fabsf(pointLine[1].projPoint.y - pointLine[2].projPoint.y) <_ESP0X5)//下底平
        flag_0 = true;
    else if(fabsf(pointLine[0].projPoint.y - pointLine[1].projPoint.y) <_ESP0X5)
        flag_1 = true;
    
}
