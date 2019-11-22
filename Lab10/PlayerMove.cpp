//
//  PlayerMove.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/29.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "PlayerMove.h"
#include "Player.h"
#include "Game.h"
#include "Renderer.h"
//#include "CollisionComponent.h"
#include "MoveComponent.h"
#include "CameraComponent.h"



PlayerMove::PlayerMove(Player* owner) : MoveComponent(owner){
    mPlayer = owner;
    ChangeState(MoveState::Falling);
}

void PlayerMove::Update(float deltaTime){
    switch (mCurrentState) {
        case PlayerMove::MoveState::OnGround:
        {
            UpdateOnGround(deltaTime);
            break;
        }
            
        case PlayerMove::MoveState::Jump:
        {
            UpdateJump(deltaTime);
            break;
        }
        
        case PlayerMove::MoveState::Falling:
        {
            UpdateFalling(deltaTime);
            break;
        }
            
        case PlayerMove::MoveState::WallClimb:
        {
            UpdateWallClimb(deltaTime);
            break;
        }
    }
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    int x,y;
    SDL_GetRelativeMouseState(&x, &y);
    float xValue = static_cast<float>(x) / MOUSE_CONVERSION_FACTOR;
    float yValue = static_cast<float>(y) / MOUSE_CONVERSION_FACTOR;
    xValue *= Math::Pi * 10.0f;
    yValue *= Math::Pi * 10.0f;
    SetAngularSpeed(xValue);
    mPlayer->camc->SetPitchSpeed(yValue);
    
    if(keyState[SDL_SCANCODE_W] && !keyState[SDL_SCANCODE_S]){
        AddForce(mOwner->GetForward() * MOVE_FORCE);
    }
    else if(!keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_S]){
        AddForce(mOwner->GetForward() * -MOVE_FORCE);
    }
    else{
//        SetForwardSpeed(0.0f);
    }
    
    if(keyState[SDL_SCANCODE_D] && !keyState[SDL_SCANCODE_A]){
        AddForce(mOwner->GetRight() * MOVE_FORCE);
    }
    else if(!keyState[SDL_SCANCODE_D] && keyState[SDL_SCANCODE_A]){
        AddForce(mOwner->GetRight() * -MOVE_FORCE);
    }
    else{
//        SetStrafeSpeed(0.0f);
    }
    
    if(keyState[SDL_SCANCODE_SPACE] && !SpacebarPressed){
        AddForce(mJumpForce);
        
        ChangeState(MoveState::Jump);
    }
    SpacebarPressed = keyState[SDL_SCANCODE_SPACE];
}

bool PlayerMove::CanWallClimb(CollSide cs){
    switch (cs) {
        case CollSide::SideX1:{
            
            break;
        }
            
        case CollSide::SideX2:{
            
            break;
        }
            
        case CollSide::SideY1:{
            
            break;
        }
            
        case CollSide::SideY2:{
            
            break;
        }
            
            
        default:
            return false;
            break;
    }
}

void PlayerMove::UpdateOnGround(float deltaTime){
    //MoveComponent::Update(deltaTime);
    PhysicsUpdate(deltaTime);
    CollSide cs;
    bool isOnTop = false;
    for(auto b : mOwner->GetGame()->GetObjects()){
        cs = FixCollision(mPlayer->cc, b->GetComponent<CollisionComponent>());
        if(cs == CollSide::Top){
            isOnTop = true;
        }
    }
    if(!isOnTop)
        ChangeState(MoveState::Falling);
}

void PlayerMove::UpdateJump(float deltaTime){
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    
    CollSide cs;
    for(auto b : mOwner->GetGame()->GetObjects()){
        cs = FixCollision(mPlayer->cc, b->GetComponent<CollisionComponent>());
        if(cs == CollSide::Bottom){
            mVelocity.z = 0.0f;
        }
    }
    if(mVelocity.z <= 0.0f)
        ChangeState(MoveState::Falling);
}

void PlayerMove::UpdateFalling(float deltaTime){
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    
    CollSide cs;
    for(auto b : mOwner->GetGame()->GetObjects()){
        cs = FixCollision(mPlayer->cc, b->GetComponent<CollisionComponent>());
        if(cs == CollSide::Top){
            mVelocity.z = 0.0f;
            ChangeState(MoveState::OnGround);
        }
    }
}

void PlayerMove::UpdateWallClimb(float deltaTime){
    
}

CollSide PlayerMove::FixCollision(class CollisionComponent* self, class CollisionComponent* block){
    Vector3 offset = Vector3::Zero;
    CollSide cs = self->GetMinOverlap(block, offset);
    if(cs != CollSide::None){
        Vector3 pos = mOwner->GetPosition();
        pos += offset;
        mOwner->SetPosition(pos);
    }
    return cs;
}

void PlayerMove::PhysicsUpdate(float deltaTime){
    mAcceleration = mPendingForces * (1.0f / mMass);
    mVelocity += mAcceleration * deltaTime;
    FixXYVelocity();
    
    Vector3 pos = mOwner->GetPosition();
    pos += mVelocity * deltaTime;
    mOwner->SetPosition(pos);
    
    float rotation = mOwner->GetRotation();
    rotation += GetAngularSpeed() * deltaTime;
    mOwner->SetRotation(rotation);
    mPendingForces = Vector3::Zero;
}

void PlayerMove::FixXYVelocity(){
    Vector2 xyVelocity(mVelocity.x, mVelocity.y);
    if(xyVelocity.Length() > MAX_SPEED){
        xyVelocity.Normalize();
        xyVelocity *= MAX_SPEED;
    }
    if(mCurrentState == MoveState::OnGround){
        if(Math::NearZero(mAcceleration.x) ||
           (mAcceleration.x > 0 && xyVelocity.x < 0) ||
           (mAcceleration.x < 0 && xyVelocity.x > 0)
           ){
            xyVelocity.x *= BRAKE_FACTOR;
        }
        if(Math::NearZero(mAcceleration.y) ||
           (mAcceleration.y > 0 && xyVelocity.y < 0) ||
           (mAcceleration.y < 0 && xyVelocity.y > 0)
           ){
            xyVelocity.y *= BRAKE_FACTOR;
        }
    }
    mVelocity.x = xyVelocity.x;
    mVelocity.y = xyVelocity.y;
}
