//
//  Player.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/23.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Player.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "PlayerMove.h"
#include "Game.h"

Player::Player(Game* g) : Actor(g){
    asprite = new AnimatedSprite(this, 200);
    
    std::vector<SDL_Texture*> walkUpAnime = {
        mGame->GetTexture("Assets/Link/WalkUp0.png"),
        mGame->GetTexture("Assets/Link/WalkUp1.png")
    };
    std::vector<SDL_Texture*> walkDownAnime = {
        mGame->GetTexture("Assets/Link/WalkDown0.png"),
        mGame->GetTexture("Assets/Link/WalkDown1.png")
    };
    std::vector<SDL_Texture*> walkLeftAnime = {
        mGame->GetTexture("Assets/Link/WalkLeft0.png"),
        mGame->GetTexture("Assets/Link/WalkLeft1.png")
    };
    std::vector<SDL_Texture*> walkRightAnime = {
        mGame->GetTexture("Assets/Link/WalkRight0.png"),
        mGame->GetTexture("Assets/Link/WalkRight1.png")
    };
    
    asprite->AddAnimation("walkUp", walkUpAnime);
    asprite->AddAnimation("walkDown", walkDownAnime);
    asprite->AddAnimation("walkLeft", walkLeftAnime);
    asprite->AddAnimation("walkRight", walkRightAnime);
    
    asprite->SetAnimation("walkUp");
    asprite->SetIsPaused(true);
    cc = new CollisionComponent(this);
    cc->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
    pm = new PlayerMove(this);
}

void Player::OnUpdate(float deltaTime){
}
