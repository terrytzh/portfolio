//
//  Asteroid.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Asteroid.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Random.h"

Asteroid::Asteroid(Game* g) : Actor(g) {
    mGame->AddAsteroid(this);
    
    sprite = new SpriteComponent(this);
    sprite->SetTexture(mGame->GetTexture("Assets/Asteroid.png"));
    move = new MoveComponent(this);
    move->SetForwardSpeed(150.0f);
    mRotation = Random::GetFloatRange(0.0f, Math::TwoPi);
    mPosition = Random::GetVector(Vector2(0, 0), Vector2(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT));
}

Asteroid::~Asteroid(){
    mGame->RemoveAsteroid(this);
}

void Asteroid::OnUpdate(float deltaTime) {
    if(mPosition.x < 0)
        mPosition.x = Game::WINDOW_WIDTH;
    else if(mPosition.x > Game::WINDOW_WIDTH)
        mPosition.x = 0;
    if(mPosition.y < 0)
        mPosition.y = Game::WINDOW_HEIGHT;
    else if(mPosition.y > Game::WINDOW_HEIGHT)
        mPosition.y = 0;
}
