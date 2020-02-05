//
//  CameraComponent.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "CameraComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

CameraComponent::CameraComponent(Actor* owner) : Component(owner){

}



void CameraComponent::Update(float deltaTime){
    mPitchAngle += mPitchSpeed * deltaTime;
    mRight.x = Math::Lerp(mRight.x, idealRight.x, 0.1f);
    mRight.y = Math::Lerp(mRight.y, idealRight.y, 0.1f);
    mRight.z = Math::Lerp(mRight.z, idealRight.z, 0.1f);
    
    if(mPitchAngle < -Math::PiOver2 / 2.0f){
        mPitchAngle = -Math::PiOver2 / 2.0f;
    }
    else if(mPitchAngle > Math::PiOver2 / 2.0f){
        mPitchAngle = Math::PiOver2 / 2.0f;
    }
    
    Matrix4 pitchRotation = Matrix4::CreateRotationY(mPitchAngle);
    Matrix4 yawRotation = Matrix4::CreateRotationZ(mOwner->GetRotation());
    Matrix4 combinedRotation = pitchRotation * yawRotation;
    Vector3 forward = Vector3::Transform(Vector3(1,0,0), combinedRotation);

    Vector3 TargetPos = mOwner->GetPosition() + (forward * TargetDist);
    Matrix4 LookMatrix = Matrix4::CreateLookAt(mOwner->GetPosition(), TargetPos, mRight);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(LookMatrix);
}


