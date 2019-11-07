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
#include "CollisionComponent.h"
#include "HeightMap.h"


PlayerMove::PlayerMove(Player* owner) : VehicleMove(owner){
    mPlayer = owner;
    mPlayer->SetPosition(mPlayer->GetGame()->GetHeightMap()->CellToWorld(39, 58));
}

void PlayerMove::Update(float deltaTime){
    VehicleMove::Update(deltaTime);
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_W]){
        SetPedal(true);
    }
    else{
        SetPedal(false);
    }
    
    if(keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_D]){
        SetMoveState(MoveState::Left);
    }
    else if(!keyState[SDL_SCANCODE_A] && keyState[SDL_SCANCODE_D]){
        SetMoveState(MoveState::Right);
    }
    else{
        SetMoveState(MoveState::Idle);
    }
}

