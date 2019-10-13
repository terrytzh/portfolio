//
//  TriForce.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "TriForce.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "Collectible.h"
#include "Player.h"
#include <vector>

TriForce::TriForce(Game* g) : Actor(g){
    std::vector<SDL_Texture*> triforce_texture = {
        g->GetTexture("Assets/Triforce0.png"),
        g->GetTexture("Assets/Triforce1.png")
    };
    
    as = new AnimatedSprite(this);
    as->AddAnimation("triforce", triforce_texture);
    as->SetAnimation("triforce");
    
    cc = new CollisionComponent(this);
    cc->SetSize(20.0f, 20.0f);
    collectible = new Collectible(this);
    collectible->SetOnCollect([this]{
        Mix_HaltChannel(mGame->GetBGChannel());
        Mix_PlayChannel(-1, mGame->GetSound("Assets/Sounds/TriForce.ogg"), 0);
        mGame->GetPlayer()->SetState(ActorState::Paused);
    });
}
