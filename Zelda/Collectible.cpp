//
//  Collectible.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Collectible.h"
#include "Actor.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Player.h"

Collectible::Collectible(Actor* owner) : Component(owner){
    
}

void Collectible::Update(float deltaTime){
    if(mOwner->GetGame()->GetPlayer()->cc->Intersect(mOwner->GetComponent<CollisionComponent>())){
        mOwner->SetState(ActorState::Destroy);
        mOnCollect();
    }
}
