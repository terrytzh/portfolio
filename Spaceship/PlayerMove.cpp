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
#include "Bullet.h"
#include "CollisionComponent.h"
#include "Block.h"


PlayerMove::PlayerMove(Player* owner) : MoveComponent(owner){
    velocity = Vector3::UnitX * PLAYER_FORWARD_SPEED * speedMultiplier;
    mPlayer = owner;
}

void PlayerMove::Update(float deltaTime){
    for(auto b : mPlayer->GetGame()->GetBlocks()){
        if(mPlayer->cc->Intersect(b->cc)){
            mPlayer->SetState(ActorState::Paused);
            Mix_PlayChannel(-1, mPlayer->GetGame()->GetSound("Assets/Sounds/ShipDie.wav"), 0);
            Mix_HaltChannel(mPlayer->GetGame()->GetBGMChannel());
        }
    }
    
    if(speedIncreaseTimer > 10.0f){
        speedIncreaseTimer = 0.0f;
        speedMultiplier += 0.15f;
    }
    else
        speedIncreaseTimer += deltaTime;
    
    Vector3 pos = mPlayer->GetPosition();
    pos += deltaTime * velocity * speedMultiplier;
    
    if(pos.y > PLAYER_Y_LIMIT)
        pos.y = PLAYER_Y_LIMIT;
    else if(pos.y < -PLAYER_Y_LIMIT)
        pos.y = -PLAYER_Y_LIMIT;
    
    if(pos.z > PLAYER_Z_LIMIT)
        pos.z = PLAYER_Z_LIMIT;
    else if(pos.z < -PLAYER_Z_LIMIT)
        pos.z = -PLAYER_Z_LIMIT;
    
    mPlayer->SetPosition(pos);
    Vector3 CamPos = pos - (Vector3::UnitX * HDist) + (Vector3::UnitZ * VDist);
    Vector3 TargetPos = pos + (Vector3::UnitX * TargetDist);
    Matrix4 LookMatrix = Matrix4::CreateLookAt(CamPos, TargetPos, Vector3::UnitZ);
    mPlayer->GetGame()->GetRenderer()->SetViewMatrix(LookMatrix);
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    velocity = Vector3::UnitX * PLAYER_FORWARD_SPEED;
    if(keyState[SDL_SCANCODE_W]){
        velocity += Vector3::UnitZ * PLAYER_MOVE_SPEED;
    }
    if(keyState[SDL_SCANCODE_S]){
        velocity -= Vector3::UnitZ * PLAYER_MOVE_SPEED;
    }
    if(keyState[SDL_SCANCODE_D]){
        velocity += Vector3::UnitY * PLAYER_MOVE_SPEED;
    }
    if(keyState[SDL_SCANCODE_A]){
        velocity -= Vector3::UnitY * PLAYER_MOVE_SPEED;
    }
    
    //Bullet shooting
    if(keyState[SDL_SCANCODE_SPACE]){
        if(!spacebarPressed){
            Bullet* b = new Bullet(mPlayer->GetGame());
            Mix_PlayChannel(-1, mPlayer->GetGame()->GetSound("Assets/Sounds/Shoot.wav"), 0);
            b->SetPosition(mPlayer->GetPosition());
            spacebarPressed = true;
        }
    }
    else
        spacebarPressed = false;
}

