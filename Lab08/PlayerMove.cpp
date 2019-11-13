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
#include "PlayerUI.h"
#include "Enemy.h"
#include "EnemyMove.h"


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

void PlayerMove::OnLapChange(int newLap) {
    if(newLap == 5){
        Mix_FadeOutChannel(mOwner->GetGame()->GetBGMChannel(), 250);
        if(newLap > mOwner->GetGame()->GetEnemy()->em->GetCurrentLap()){
            mPlayer->pu->SetRaceState(PlayerUI::Won);
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Won.wav"), 0);
        }
        else{
            mPlayer->pu->SetRaceState(PlayerUI::Lost);
            Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Lost.wav"), 0);
        }
        mPlayer->SetState(ActorState::Paused);
        mPlayer->GetGame()->GetEnemy()->SetState(ActorState::Paused);
        
            
    }
    else if(newLap == 4){
        Mix_FadeOutChannel(mOwner->GetGame()->GetBGMChannel(), 250);
        Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/FinalLap.wav"), 0);
        mOwner->GetGame()->SetBGMChannel(Mix_FadeInChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/MusicFast.ogg"), -1, 4000));
        mPlayer->pu->OnLapChange(newLap);
    }
    else{
        mPlayer->pu->OnLapChange(newLap);
    }
}
