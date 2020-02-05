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
    SnapToIdeal();
    camVelocity = Vector3::Zero;
}



void CameraComponent::Update(float deltaTime){
    
    dampConstant = 2.0f * Math::Sqrt(SPRING_CONSTANT);
    Vector3 idealCamPos = CalculateIdealPosition();
    Vector3 displacement = camPosition - idealCamPos;
    Vector3 springAcceleration = (-SPRING_CONSTANT * displacement) - (dampConstant * camVelocity);
    camVelocity += springAcceleration * deltaTime;
    camPosition += camVelocity * deltaTime;
    
    Vector3 TargetPos = mOwner->GetPosition() + (mOwner->GetForward() * TargetDist);
    Matrix4 LookMatrix = Matrix4::CreateLookAt(camPosition, TargetPos, Vector3::UnitZ);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(LookMatrix);
}


Vector3 CameraComponent::CalculateIdealPosition(){
    Vector3 CamPos = mOwner->GetPosition() - (mOwner->GetForward() * HDist);
    CamPos.z = 70.0f;
    return CamPos;
}

void CameraComponent::SnapToIdeal(){
    camPosition = CalculateIdealPosition();
    Vector3 TargetPos = mOwner->GetPosition() + (mOwner->GetForward() * TargetDist);
    Matrix4 LookMatrix = Matrix4::CreateLookAt(camPosition, TargetPos, Vector3::UnitZ);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(LookMatrix);
}
