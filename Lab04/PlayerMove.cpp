//
//  PlayerMove.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/23.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "PlayerMove.h"
#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"

PlayerMove::PlayerMove(Actor* owner) : MoveComponent(owner){
    player = dynamic_cast<Player*>(owner);
}

void PlayerMove::Update(float deltaTime){
    if(player->GetIsDead()){
        if(player->GetState()!=ActorState::Paused){
            Mix_HaltChannel(mOwner->GetGame()->GetBGChannel());
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Dead.wav"), 0);
            player->asprite->SetAnimation("dead");
            player->SetState(ActorState::Paused);
        }
        return;
    }
    Vector2 pos = player->GetPosition();
    pos.x += deltaTime * GetForwardSpeed();
    pos.y += deltaTime * mYSpeed;
    
    if(pos.y > 448.0f){
        player->SetIsDead(true);
    }
    
    if(pos.x > 6368.0f){
        Mix_HaltChannel(mOwner->GetGame()->GetBGChannel());
        Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/StageClear.wav"), 0);
        mOwner->SetState(ActorState::Paused);
    }
    
    player->SetPosition(pos);
    
    bool blockCollide = false;
    Vector2 offset;
    CollSide collState;
    for(auto b : player->GetGame()->GetBlocks()){
        offset = Vector2(0,0);
        collState = player->cc->GetMinOverlap(b->cc, offset);

        if(collState != CollSide::None){
            //Fall on ground
            if(collState == CollSide::Top && mYSpeed > 0.0f){
                mYSpeed = 0.0f;
                mInAir = false;
            }
            else if(collState == CollSide::Bottom && mYSpeed < 0.0f){
                mYSpeed = 0.0f;
                Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Bump.wav"), 0);
            }
            
            blockCollide = true;
            pos -= offset;
            player->SetPosition(pos);
        }
    }
    
    //If not colliding with anything, it's in air
    mInAir = !blockCollide;
    
    //Detect collision with goomba
    for(auto g : player->GetGame()->GetEnemies()){
        offset = Vector2(0,0);
        collState = player->cc->GetMinOverlap(g->cc, offset);
        if(collState != CollSide::None && !g->GetStompedState()){
            if(collState == CollSide::Top){
                g->SetStompedState(true);
                mYSpeed = -350.0f;
                mInAir = true;
                Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Stomp.wav"), 0);
            }
            else if((collState == CollSide::Left || collState == CollSide::Right) && mInAir){
                g->SetStompedState(true);
                mYSpeed = -350.0f;
                mInAir = true;
                Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Stomp.wav"), 0);
            }
            else{
                player->SetIsDead(true);
            }
            pos -= offset;
            player->SetPosition(pos);
        }
    }
    
    //Adjust Mario animation
    if(!mInAir){
        if(GetForwardSpeed()>0.0f)
            player->asprite->SetAnimation("runRight");
        else if(GetForwardSpeed()<0.0f)
            player->asprite->SetAnimation("runLeft");
        else
            player->asprite->SetAnimation("idle");
    }
    else{
        if(GetForwardSpeed()>0.0f)
            player->asprite->SetAnimation("jumpRight");
        else if(GetForwardSpeed()<0.0f)
            player->asprite->SetAnimation("jumpLeft");
        else{
            if(player->asprite->GetAnimName() == "runRight" ||
               player->asprite->GetAnimName() == "jumpRight" ||
               player->asprite->GetAnimName() == "idle"
               )
                player->asprite->SetAnimation("jumpRight");
            else
                player->asprite->SetAnimation("jumpLeft");
        }
    }
    
    //Temporary
    if(pos.y == 448.0f){
        mInAir = false;
    }
    
    //Update yspeed: g = 10m/s^2
    mYSpeed += 2000.0f*deltaTime;
    
    //Update camera coordinate
    if(pos.x < mOwner->GetGame()->GetCamPosition().x)
        pos.x = mOwner->GetGame()->GetCamPosition().x;
    
    Vector2 campos = mOwner->GetGame()->GetCamPosition();
    campos.x = pos.x - 300.0f;
    if(campos.x < 0.0f)
        campos.x = 0.0f;
    if(campos.x > mOwner->GetGame()->GetCamPosition().x)
        mOwner->GetGame()->SetCamPosition(campos);
    player->SetPosition(pos);
    
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_LEFT])
        this->SetForwardSpeed(-PLAYER_SPEED);
    else if(keyState[SDL_SCANCODE_RIGHT])
        this->SetForwardSpeed(PLAYER_SPEED);
    else{
        this->SetForwardSpeed(0.0f);
    }
    
    if(keyState[SDL_SCANCODE_SPACE]){
        if(!mSpacePressed){
            if(!mInAir){
                //Start Jumping
                mYSpeed = -700.0f;
                mInAir = true;
                Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav"), 0);
            }
            mSpacePressed = true;
        }
    }
    else
        mSpacePressed = false;
}
