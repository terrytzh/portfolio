//
//  Bat.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include <vector>
#include "Random.h"
#include "Bat.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "Collider.h"

Bat::Bat(Game* g) : Actor(g){
    as = new AnimatedSprite(this);
    std::vector<SDL_Texture*> text = {
        g->GetTexture("Assets/Bat0.png"),
        g->GetTexture("Assets/Bat1.png")
    };
    as->AddAnimation("bat", text);
    as->SetAnimation("bat");
    
    cc = new CollisionComponent(this);
    cc->SetSize(BAT_WIDTH, BAT_WIDTH);
    
    ec = new EnemyComponent(this);
    ec->SetOnDeath([this]{
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/EnemyDie.wav"), 0);
    });
    ec->SetOnTakeDamage([this]{
        
    });
    
    direction = Vector2::Normalize(Vector2(Random::GetFloatRange(-1.0f, 1.0f),Random::GetFloatRange(-1.0f, 1.0f)));
}

void Bat::OnUpdate(float deltaTime){
    if(moveTime > DIRECTION_CHANGE_TIME){
        direction = Vector2::Normalize(Vector2(Random::GetFloatRange(-1.0f, 1.0f),Random::GetFloatRange(-1.0f, 1.0f)));
        moveTime = 0.0f;
    }
    Vector2 pos = GetPosition();
    pos += direction * BAT_SPEED * deltaTime;
    SetPosition(pos);
    
    Vector2 offset;
    CollSide side;
    for(auto collider : mGame->GetColliders()){
        offset = Vector2(0,0);
        side = cc->GetMinOverlap(collider->cc, offset);
        if(side != CollSide::None){
            //Something
        }
        pos += offset;
        SetPosition(pos);
    }
    
    moveTime += deltaTime;
}
