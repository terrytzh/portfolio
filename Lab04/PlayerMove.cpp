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
#include "CollisionComponent.h"

PlayerMove::PlayerMove(Actor* owner) : MoveComponent(owner){
    player = dynamic_cast<Player*>(owner);
}

void PlayerMove::Update(float deltaTime){
    Vector2 pos = player->GetPosition();
    pos.x += deltaTime * GetForwardSpeed();
    pos.y += deltaTime * mYSpeed;
    
    if(pos.y > 448.0f){
        pos.y = 448.0f;
        mInAir = false;
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
            }
            
            blockCollide = true;
            SDL_Log("Offset: %f,%f",offset.x,offset.y);
            pos -= offset;
            SDL_Log("Position: %f,%f",pos.x,pos.y);
            player->SetPosition(pos);
        }
    }
    
    //If not colliding with anything, it's in air
    mInAir = !blockCollide;
    
    //Temporary
    if(pos.y == 448.0f){
        mInAir = false;
    }
    
    //Update yspeed: g = 10m/s^2
    mYSpeed += 2000.0f*deltaTime;
    
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
            }
            mSpacePressed = true;
        }
    }
    else
        mSpacePressed = false;
}
