//
//  EiCamera.cpp
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "EiCamera.hpp"
#include "../EiMath/EiTransform3D.hpp"

void matMatrix44PerspectiveFovLH(matrix4X4 &mat, const float fov, const float aspect, const float ZNear, const float ZFar);

EiCamera::EiCamera(vec3 pos,vec3 in_dir, float Z_near, float Z_far, float FocalLen, vec3 in_up)
{
    this->look = in_dir.norm();
    this->up = in_up;
    this->right = look.cross(up);
    
    CameraPos = pos;
    //    v=2tan^{-1}(\frac{s}{2f} )，
    float Fov = 2.0 * atanf(43.27 / (2.0 * FocalLen));
    matMatrix44PerspectiveFovLH(this->ProjMat,Fov, 1, Z_near, Z_far);
    
}

matrix4X4* EiCamera::getCameraMatrix()
{
    vec3 look_normalize = this->look.norm();
    this->look = look_normalize;
    this->up = this->look.cross(this->right);
    this->up = this->up.norm();
    this->right = up.cross(this->look);
    this->right = this->right.norm();
    
    
    CameraMat.m11 = right.x;
    CameraMat.m12 = right.y;
    CameraMat.m13 = right.z;
    CameraMat.m14 = - right.dot(CameraPos);
    
    CameraMat.m21 = - up.x;
    CameraMat.m22 = - up.y;
    CameraMat.m23 = - up.z;
    CameraMat.m24 = - up.dot(CameraPos);
    
    CameraMat.m31 = look.x;
    CameraMat.m32 = look.y;
    CameraMat.m33 = look.z;
    CameraMat.m34 = - look.dot(CameraPos);
    
    CameraMat.m41 = 0;
    CameraMat.m42 = 0;
    CameraMat.m43 = 0;
    CameraMat.m44 = 1;
    
    return &CameraMat;
}

matrix4X4* EiCamera::getProjMatrix()
{
    return &(this->ProjMat);
}



void EiCamera::MoveForward(float dis)
{
    vec3 movedVec3 = this->look.norm() * dis;
    this->CameraPos += movedVec3;
}

void EiCamera::MoveRight(float dis)
{
    vec3 movedVec3 = this->right.norm() * dis;
    this->CameraPos += movedVec3;
}

void EiCamera::MoveUp(float dis)
{
    vec3 movedVec3 = this->up.norm() * dis;
    this->CameraPos += movedVec3;
}



void EiCamera::RotateByForward(float angle)
{
    matrix4X4 R;
    EiTransform3D::MatrixRotation3D(R, this->look, vec3(0,0,0), angle);
    
    this->right = R.mul(R, this->right);
    this->up = R.mul(R, this->up);
    
}

void EiCamera::RotateByRight(float angle)
{
    matrix4X4 R;
    EiTransform3D::MatrixRotation3D(R, this->right, vec3(0,0,0), angle);
    
    this->look = R.mul(R, this->look);
    this->up = R.mul(R, this->up);
}

void EiCamera::RotateByUp(float angle)
{
    matrix4X4 R;
    EiTransform3D::MatrixRotation3D(R, this->up, vec3(0,0,0), angle);
    
    this->right = matrix4X4::mul(R, this->right);
    this->look = matrix4X4::mul(R, this->look);
}


////////////

void matMatrix44PerspectiveFovLH(matrix4X4 &mat, const float fov, const float aspect, const float ZNear, const float ZFar )
{
    const float fViewSpaceHeight = 1.0f / tanf( fov * 0.5f );
    const float fViewSpaceWidth = fViewSpaceHeight / aspect ;
    
    mat.m11 = fViewSpaceWidth; mat.m12 = 0.0f; mat.m13 = 0.0f; mat.m14 = 0.0f;
    mat.m21 = 0.0f; mat.m22 = fViewSpaceHeight; mat.m23 = 0.0f; mat.m24 = 0.0f;
    mat.m31 = 0.0f; mat.m32 = 0.0f; mat.m33 = ZFar / ( ZFar - ZNear ); mat.m34 = -ZNear * ZFar / ( ZFar - ZNear );
    mat.m41 = 0.0f; mat.m42 = 0.0f; mat.m43 = 1.0f; mat.m44 = 0.0f;
}
