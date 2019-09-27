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
#include "AnimatedSprite.h"

PlayerMove::PlayerMove(Actor* owner) : MoveComponent(owner){
    player = dynamic_cast<Player*>(owner);
}

void PlayerMove::Update(float deltaTime){
    
    Vector2 half(player->GetGame()->WINDOW_WIDTH/2.0f, player->GetGame()->WINDOW_HEIGHT/2.0f);
    player->GetGame()->SetCamPosition(player->GetPosition()-half);
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
