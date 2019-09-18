//
//  Ball.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/17.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Ball.h"
#include "Game.h"
#include "BallMove.h"
#include "SpriteComponent.h"



Ball::Ball(Game* g) : Actor(g){
    sprite = new SpriteComponent(this);
    sprite->SetTexture(mGame->GetTexture("Assets/Ball.png"));
    bm = new BallMove(this);
}
