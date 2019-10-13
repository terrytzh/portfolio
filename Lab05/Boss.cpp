//
//  Boss.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Boss.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "Fireball.h"
#include "Door.h"
#include <vector>

Boss::Boss(Game* g) : Actor(g){
    std::vector<SDL_Texture*> idle_texture = {
        g->GetTexture("Assets/Dragon/Idle0.png"),
        g->GetTexture("Assets/Dragon/Idle1.png")
    };
    
    std::vector<SDL_Texture*> attack_texture = {
        g->GetTexture("Assets/Dragon/Attack0.png"),
        g->GetTexture("Assets/Dragon/Attack1.png")
    };
    
    std::vector<SDL_Texture*> enraged_texture = {
        g->GetTexture("Assets/Dragon/Enraged0.png"),
        g->GetTexture("Assets/Dragon/Enraged1.png"),
        g->GetTexture("Assets/Dragon/Enraged2.png"),
        g->GetTexture("Assets/Dragon/Enraged3.png")
    };
    as = new AnimatedSprite(this);
    as->AddAnimation("idle", idle_texture);
    as->AddAnimation("attack", attack_texture);
    as->AddAnimation("enraged", enraged_texture);
    as->SetAnimation("idle");
    
    cc = new CollisionComponent(this);
    cc->SetSize(50.0f, 64.0f);
    
    ec = new EnemyComponent(this);
    ec->SetOnDeath([this]{
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/BossDie.wav"), 0);
        for(auto d : mGame->GetDoors()){
            if(d->GetState() == DoorState::Closed){
                d->SetState(DoorState::Open);
                d->UpdateComponents();
            }
        }
    });
    ec->SetOnTakeDamage([this]{
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/BossHit.wav"), 0);
    });
    ec->SetHP(5);
    ec->SetCollisionDamage(2);
}


void Boss::OnUpdate(float deltaTime){
    if(ec->GetHP()>2){
        if(attackTimer <= 0.0f){
            attackTimer = 2.0f;
            //Attack
            Fireball* up = new Fireball(mGame,true);
            up->SetRotation(Math::Pi*5.0f/6.0f);
            up->SetPosition(GetPosition());
            Fireball* left = new Fireball(mGame,true);
            left->SetRotation(Math::Pi);
            left->SetPosition(GetPosition());
            Fireball* down = new Fireball(mGame,true);
            down->SetRotation(Math::Pi*7.0f/6.0f);
            down->SetPosition(GetPosition());
            as->SetAnimation("idle");
            Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/Fireball.wav"), 0);
        }
        else if(attackTimer <= 0.25f){
            as->SetAnimation("attack");
        }
    }
    else{
        as->SetAnimation("enraged");
        if(attackTimer <= 0.0f){
            attackTimer = 1.0f;
            //Attack
            for(int i = 0;i<9;i++){
                Fireball* fb = new Fireball(mGame,true);
                fb->SetRotation(Math::PiOver2 + Math::Pi*static_cast<float>(i)/8.0f);
                fb->SetPosition(GetPosition());
            }
            Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/Fireball.wav"), 0);
        }
    }
    
    attackTimer -= deltaTime;
}
