//
//  Fireball.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Fireball.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "Player.h"

Fireball::Fireball(Game* g, bool isGreen) : Actor(g){
    sprite = new SpriteComponent(this);
    if(isGreen)
        sprite->SetTexture(mGame->GetTexture("Assets/FireballGreen.png"));
    else
    sprite->SetTexture(mGame->GetTexture("Assets/FireballRed.png"));
    
    mc = new MoveComponent(this);
    mc->SetForwardSpeed(200.0f);
    
    cc = new CollisionComponent(this);
    cc->SetSize(16.0f, 16.0f);
}

void Fireball::OnUpdate(float deltaTime){
    if(lifeTime > 2.0f){
        SetState(ActorState::Destroy);
        return;
    }
    
    if(cc->Intersect(mGame->GetPlayer()->cc)){
        mGame->GetPlayer()->TakeDamage(1);
        SetState(ActorState::Destroy);
    }
    
    lifeTime += deltaTime;
}
