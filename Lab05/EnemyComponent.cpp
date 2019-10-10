//
//  EnemyComponent.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "EnemyComponent.h"
#include "Game.h"
#include "Actor.h"

EnemyComponent::EnemyComponent(Actor* owner) : Component(owner){
    currentRoom = owner->GetGame()->GetCurrentRoom();
    owner->GetGame()->AddToEnemies(currentRoom, owner);
}

EnemyComponent::~EnemyComponent(){
    mOwner->GetGame()->RemoveFromEnemies(currentRoom, mOwner);
}
