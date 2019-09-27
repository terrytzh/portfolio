//
//  Goomba.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Goomba.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "GoombaMove.h"

Goomba::Goomba(Game* g) : Actor(g){
    mGame->AddEnemy(this);
    asprite = new AnimatedSprite(this);
    std::vector<SDL_Texture*> walkAnime = {
        mGame->GetTexture("Assets/Goomba/Walk0.png"),
        mGame->GetTexture("Assets/Goomba/Walk1.png")
    };
    asprite->AddAnimation("walk", walkAnime);
    asprite->SetAnimation("walk");
    cc = new CollisionComponent(this);
    cc->SetSize(GOOMBA_SIZE, GOOMBA_SIZE);
    gm = new GoombaMove(this);
}

Goomba::~Goomba(){
    mGame->RemoveEnemy(this);
}

void Goomba::OnUpdate(float deltaTime){
    if(isStomped){
        std::vector<SDL_Texture*> deadAnime = {mGame->GetTexture("Assets/Goomba/Dead.png")};
        asprite->AddAnimation("dead", deadAnime);
        asprite->SetAnimation("dead");
        deadTime += deltaTime;
        if(deadTime > 0.25f)
            SetState(ActorState::Destroy);
    }
}
