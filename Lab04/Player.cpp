//
//  Player.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/23.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Player.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "PlayerMove.h"
#include "Game.h"

Player::Player(Game* g) : Actor(g){
    sprite = new SpriteComponent(this, 200);
    sprite->SetTexture(mGame->GetTexture("Assets/Mario/Idle.png"));
    cc = new CollisionComponent(this);
    cc->SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
    pm = new PlayerMove(this);
}
