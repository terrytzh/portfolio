//
//  Paddle.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/17.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Paddle.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"

Paddle::Paddle(Game* g) : Actor(g){
    sprite = new SpriteComponent(this);
    sprite->SetTexture(mGame->GetTexture("Assets/Paddle.png"));
    mc = new MoveComponent(this);
}

void Paddle::OnProcessInput(const Uint8* keyState){
    if(keyState[SDL_SCANCODE_LEFT]){
        mc->SetForwardSpeed(-PADDLE_SPEED);
    }
    else if(keyState[SDL_SCANCODE_RIGHT]){
        mc->SetForwardSpeed(PADDLE_SPEED);
    }
    else{
        mc->SetForwardSpeed(0.0f);
    }
}

void Paddle::OnUpdate(float deltaTime){
    
    SDL_Log("Position x: %f", mPosition.x);
    
    if(mPosition.x < PADDLE_WIDTH/2.0f + mGame->WALL_THICKNESS){
        mPosition.x = PADDLE_WIDTH/2.0f + mGame->WALL_THICKNESS;
    }
    else if(mPosition.x > mGame->WINDOW_WIDTH - mGame->WALL_THICKNESS - PADDLE_WIDTH/2.0f){
        mPosition.x = mGame->WINDOW_WIDTH - mGame->WALL_THICKNESS - PADDLE_WIDTH/2.0f;
    }
}
