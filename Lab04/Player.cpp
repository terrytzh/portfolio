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
    
    std::vector<SDL_Texture*> idleAnime = {mGame->GetTexture("Assets/Mario/Idle.png")};
    std::vector<SDL_Texture*> deadAnime = {mGame->GetTexture("Assets/Mario/Dead.png")};
    std::vector<SDL_Texture*> jumpLeftAnime = {mGame->GetTexture("Assets/Mario/JumpLeft.png")};
    std::vector<SDL_Texture*> jumpRightAnime = {mGame->GetTexture("Assets/Mario/JumpRight.png")};
    std::vector<SDL_Texture*> runLeftAnime = {
        mGame->GetTexture("Assets/Mario/RunLeft0.png"),
        mGame->GetTexture("Assets/Mario/RunLeft1.png"),
        mGame->GetTexture("Assets/Mario/RunLeft2.png")
    };
    std::vector<SDL_Texture*> runRightAnime = {
        mGame->GetTexture("Assets/Mario/RunRight0.png"),
        mGame->GetTexture("Assets/Mario/RunRight1.png"),
        mGame->GetTexture("Assets/Mario/RunRight2.png")
    };
    
    asprite->AddAnimation("idle", idleAnime);
    asprite->AddAnimation("dead", deadAnime);
    asprite->AddAnimation("jumpLeft", jumpLeftAnime);
    asprite->AddAnimation("jumpRight", jumpRightAnime);
    asprite->AddAnimation("runLeft", runLeftAnime);
    asprite->AddAnimation("runRight", runRightAnime);
    
    asprite->SetAnimation("idle");
    cc = new CollisionComponent(this);
    cc->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
    pm = new PlayerMove(this);
}

void Player::OnUpdate(float deltaTime){
}
