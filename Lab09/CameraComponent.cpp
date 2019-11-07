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
    Vector3 TargetPos = mOwner->GetPosition() + (mOwner->GetForward() * TargetDist);
    Matrix4 LookMatrix = Matrix4::CreateLookAt(mOwner->GetPosition(), TargetPos, Vector3::UnitZ);
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(LookMatrix);
}
