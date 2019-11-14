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
    }
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    int x,y;
    SDL_GetRelativeMouseState(&x, &y);
    float xValue = static_cast<float>(x) / 500.0f;
    float yValue = static_cast<float>(y) / 500.0f;
    xValue *= Math::Pi * 10.0f;
    yValue *= Math::Pi * 10.0f;
    SetAngularSpeed(xValue);
    mPlayer->camc->SetPitchSpeed(yValue);
    
    if(keyState[SDL_SCANCODE_W] && !keyState[SDL_SCANCODE_S]){
        SetForwardSpeed(350.0f);
    }
    else if(!keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_S]){
        SetForwardSpeed(-350.0f);
    }
    else{
        SetForwardSpeed(0.0f);
    }
    
    if(keyState[SDL_SCANCODE_D] && !keyState[SDL_SCANCODE_A]){
        SetStrafeSpeed(350.0f);
    }
    else if(!keyState[SDL_SCANCODE_D] && keyState[SDL_SCANCODE_A]){
        SetStrafeSpeed(-350.0f);
    }
    else{
        SetStrafeSpeed(0.0f);
    }
    
    if(keyState[SDL_SCANCODE_SPACE] && !SpacebarPressed){
        mZSpeed = JUMP_SPEED;
        ChangeState(MoveState::Jump);
    }
    SpacebarPressed = keyState[SDL_SCANCODE_SPACE];
}

void PlayerMove::UpdateOnGround(float deltaTime){
    MoveComponent::Update(deltaTime);
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
    MoveComponent::Update(deltaTime);
    mZSpeed += GRAVITY_ACCELERATION * deltaTime;
    Vector3 pos = mOwner->GetPosition();
    pos.z += mZSpeed * deltaTime;
    mOwner->SetPosition(pos);
    
    CollSide cs;
    for(auto b : mOwner->GetGame()->GetObjects()){
        cs = FixCollision(mPlayer->cc, b->GetComponent<CollisionComponent>());
        if(cs == CollSide::Bottom){
            mZSpeed = 0.0f;
        }
    }
    if(mZSpeed <= 0.0f)
        ChangeState(MoveState::Falling);
}

void PlayerMove::UpdateFalling(float deltaTime){
    MoveComponent::Update(deltaTime);
    mZSpeed += GRAVITY_ACCELERATION * deltaTime;
    Vector3 pos = mOwner->GetPosition();
    pos.z += mZSpeed * deltaTime;
    mOwner->SetPosition(pos);
    
    CollSide cs;
    for(auto b : mOwner->GetGame()->GetObjects()){
        cs = FixCollision(mPlayer->cc, b->GetComponent<CollisionComponent>());
        if(cs == CollSide::Top){
            mZSpeed = 0.0f;
            ChangeState(MoveState::OnGround);
        }
    }
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
    
}
