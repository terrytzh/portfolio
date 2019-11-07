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



PlayerMove::PlayerMove(Player* owner) : MoveComponent(owner){
    
}

void PlayerMove::Update(float deltaTime){
    MoveComponent::Update(deltaTime);
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    
}

