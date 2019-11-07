//
//  VehicleMove.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "VehicleMove.h"
#include "Game.h"
#include "Actor.h"
#include "HeightMap.h"

VehicleMove::VehicleMove(Actor* owner, bool isEnemy) : Component(owner, 50){
    velocity = Vector3::Zero;
    if(isEnemy){
        MAX_LINEAR_ACCELERATION = 3000.0f;
        ANGULER_DRAG_COEFFICIENT = 0.8f;
        ACCELERATION_RAMP_TIME = 1.5f;
        ANGULER_ACCELERATION = 8.0f * Math::Pi;
    }
}

void VehicleMove::Update(float deltaTime){
    Vector3 pos = mOwner->GetPosition();
    if(pedalPressed){
        accelerateTimer += deltaTime;
        float lerpCoefficient = accelerateTimer / ACCELERATION_RAMP_TIME;
        if(lerpCoefficient > 1.0f)
            lerpCoefficient = 1.0f;
        float acceleration = Math::Lerp(MIN_LINEAR_ACCELERATION, MAX_LINEAR_ACCELERATION, lerpCoefficient);
        velocity += mOwner->GetForward() * acceleration * deltaTime;
        pos += velocity * deltaTime;
        velocity *= PEDAL_DRAG_COEFFICIENT;
    }
    else{
        accelerateTimer = 0.0f;
        pos += velocity * deltaTime;
        velocity *= NORMAL_DRAG_COEFFICIENT;
    }
    
    if(mOwner->GetGame()->GetHeightMap()->IsOnTrack(pos.x, pos.y)){
        float height = mOwner->GetGame()->GetHeightMap()->GetHeight(pos.x, pos.y);
        pos.z = Math::Lerp(pos.z, height, 0.1f);
    }
    mOwner->SetPosition(pos);
    
    switch (moveState) {
        case Left:{
            angularVelocity += ANGULER_ACCELERATION * -1.0f * deltaTime;
            break;
            }
            
        case Right:{
            angularVelocity += ANGULER_ACCELERATION * 1.0f * deltaTime;
            break;
        }
            
        default:
            break;
    }
    
    float angle = mOwner->GetRotation();
    angle += angularVelocity * deltaTime;
    mOwner->SetRotation(angle);
    angularVelocity *= ANGULER_DRAG_COEFFICIENT;
}
