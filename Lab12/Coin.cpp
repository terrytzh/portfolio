//
//  Coin.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/8.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Coin.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Checkpoint.h"
#include "Player.h"

Coin::Coin(Game* g, Actor* parent) : Actor(g, parent){
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Coin.gpmesh"));
    cc = new CollisionComponent(this);
    cc->SetSize(COIN_LENGTH, COIN_LENGTH, COIN_LENGTH);
}

void Coin::OnUpdate(float deltaTime){
    if(cc->Intersect(mGame->GetPlayer()->cc)){
        GetGame()->GetCoinCount()++;
        Mix_PlayChannel(-1, mGame->GetSound("Assets/Sounds/Coin.wav"), 0);
        SetState(ActorState::Destroy);
    }
    SetRotation(GetRotation() + COIN_ROTATE_SPEED * deltaTime);
}
