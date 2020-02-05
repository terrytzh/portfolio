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
    PLAYER_HP = INITIAL_PLAYER_HP;
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
    
    std::vector<SDL_Texture*> AttackUpAnime = {
        mGame->GetTexture("Assets/Link/AttackUp.png"),
    };
    
    std::vector<SDL_Texture*> AttackDownAnime = {
        mGame->GetTexture("Assets/Link/AttackDown.png"),
    };
    
    std::vector<SDL_Texture*> AttackLeftAnime = {
        mGame->GetTexture("Assets/Link/AttackLeft.png"),
    };
    
    std::vector<SDL_Texture*> AttackRightAnime = {
        mGame->GetTexture("Assets/Link/AttackRight.png"),
    };
    
    asprite->AddAnimation("walkUp", walkUpAnime);
    asprite->AddAnimation("walkDown", walkDownAnime);
    asprite->AddAnimation("walkLeft", walkLeftAnime);
    asprite->AddAnimation("walkRight", walkRightAnime);
    asprite->AddAnimation("AttackUp", AttackUpAnime);
    asprite->AddAnimation("AttackDown", AttackDownAnime);
    asprite->AddAnimation("AttackLeft", AttackLeftAnime);
    asprite->AddAnimation("AttackRight", AttackRightAnime);
    
    asprite->SetAnimation("walkUp");
    cc = new CollisionComponent(this);
    cc->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
    pm = new PlayerMove(this);
}

void Player::OnUpdate(float deltaTime){
    if(invincibilityTimer > 0.0f)
        invincibilityTimer -= deltaTime;
}

void Player::TakeDamage(int amount){
    if(invincibilityTimer > 0.0f)
        return;
    else
        invincibilityTimer = INVINCIBILITY_TIME;
    
    PLAYER_HP -= amount;
    if(PLAYER_HP <= 0){
        Mix_HaltChannel(GetGame()->GetBGChannel());
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/LinkDie.wav"), 0);
        SetState(ActorState::Paused);
    }
    else{
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/LinkHit.wav"), 0);
    }
}
