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

void EnemyComponent::TakeDamage(int amount){
    if(invinsibilityTimer <= 0.0f)
        invinsibilityTimer = 1.0f;
    else
        return;
    
    hitPoint -= amount;
    if(hitPoint <= 0){
        mOnDeath();
        mOwner->SetState(ActorState::Destroy);
    }
    else{
        mOnTakeDamage();
    }
}

void EnemyComponent::Update(float deltaTime){
    if(invinsibilityTimer > 0.0f)
        invinsibilityTimer -= deltaTime;
}
