//
//  Skeleton.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//


#include "Skeleton.h"
#include "Game.h"
#include "Random.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "Fireball.h"
#include "Player.h"

Skeleton::Skeleton(Game* g) : Actor(g){
    std::vector<SDL_Texture*> text = {
        g->GetTexture("Assets/Skeleton0.png"),
        g->GetTexture("Assets/Skeleton1.png")
    };
    as = new AnimatedSprite(this);
    as->AddAnimation("skeleton", text);
    as->SetAnimation("skeleton");
    
    cc = new CollisionComponent(this);
    cc->SetSize(25.0f, 25.0f);
    
    ec = new EnemyComponent(this);
    ec->SetOnDeath([this]{
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/EnemyDie.wav"), 0);
    });
    ec->SetOnTakeDamage([this]{
        
    });
    COOLDOWN_TIMER = Random::GetFloatRange(1.0f, 3.0f);
}

void Skeleton::OnUpdate(float deltaTime){
    if(timeCount > COOLDOWN_TIMER){
        Fireball* fb = new Fireball(mGame);
        fb->SetPosition(GetPosition());
        fb->SetRotation(Math::Atan2(-(mGame->GetPlayer()->GetPosition().y - fb->GetPosition().y), mGame->GetPlayer()->GetPosition().x - fb->GetPosition().x));
        timeCount = 0.0f;
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/Fireball.wav"), 0);
    }
    timeCount += deltaTime;
}
