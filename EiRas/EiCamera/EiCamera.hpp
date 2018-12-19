//
//  EiCamera.hpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiCamera_hpp
#define EiCamera_hpp

#include "../EiMacro.h"
#include "../EiMath/EiMath.hpp"

class EiCamera
{
    
public:
    
    EiCamera()
    {
    }
    EiCamera(vec3 pos,vec3 in_dir,float Z_near,float Z_far,float FocalLen = 50.0/*mm*/,vec3 in_up = vec3(0,1,0));
    
    matrix4X4* getProjMatrix();
    
    matrix4X4* getCameraMatrix();
    
    // Control
    void MoveForward(float dis);
    void MoveRight(float dis);
    void MoveUp(float dis);
    
    void RotateByForward(float angle);
    void RotateByRight(float angle);
    void RotateByUp(float angle);
    
private:
    
    matrix4X4 mat;
    vec3 right;
    vec3 up;
    vec3 look;
    
    vec3 CameraPos;
    
    matrix4X4 CameraMat;
    matrix4X4 ProjMat;
};


#endif /* EiCamera_hpp */
