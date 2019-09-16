//
//  Laser.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Asteroid.h"
#include "Game.h"

Laser::Laser(Game* g) : Actor(g) {
    sprite = new SpriteComponent(this,90);
    sprite->SetTexture(mGame->GetTexture("Assets/Laser.png"));
    move = new MoveComponent(this);
    move->SetForwardSpeed(LASER_SPEED);
    spawn_time = 0.0f;
}

void Laser::OnUpdate(float deltaTime) {
    spawn_time += deltaTime;
    if(spawn_time > MAXIMUM_LIFETIME)
        this->SetState(ActorState::Destroy);
    
    for(std::vector<class Asteroid*>::iterator i = mGame->asteroids.begin(); i != mGame->asteroids.end(); i++){
        if((this->mPosition-(*i)->GetPosition()).Length() < COLLIDE_RANGE){
            this->SetState(ActorState::Destroy);
            (*i)->SetState(ActorState::Destroy);
        }
    }
}
