//
//  Ship.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Ship.h"
#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Ship::Ship(class Game* g) : Actor(g){
    sprite = new SpriteComponent(this);
    sprite->SetTexture(mGame->GetTexture("Assets/Ship.png"));
    move = new MoveComponent(this);
}

void Ship::OnProcessInput(const Uint8* keyState){
    //Adjust Forward Speed
    if(keyState[SDL_SCANCODE_UP]){
        move->SetForwardSpeed(SHIP_FORWARD_SPEED);
        sprite->SetTexture(mGame->GetTexture("Assets/ShipThrust.png"));
    }
    else if (keyState[SDL_SCANCODE_DOWN]){
        move->SetForwardSpeed(-SHIP_FORWARD_SPEED);
        sprite->SetTexture(mGame->GetTexture("Assets/ShipThrust.png"));
    }
    else{
        move->SetForwardSpeed(0.0);
        sprite->SetTexture(mGame->GetTexture("Assets/Ship.png"));
    }
    
    //Adjust Angular Speed
    if (keyState[SDL_SCANCODE_LEFT]){
        move->SetAngularSpeed(SHIP_ANGULAR_SPEED);
    }
    else if (keyState[SDL_SCANCODE_RIGHT]){
        move->SetAngularSpeed(-SHIP_ANGULAR_SPEED);
    }
    else{
        move->SetAngularSpeed(0.0);
    }
    
    if (keyState[SDL_SCANCODE_SPACE]){
    if(shotElapsedTime > SHOOT_SPEED){
        Laser* l = new Laser(mGame);
        l->SetPosition(this->GetPosition());
        l->SetRotation(this->GetRotation());
        shotElapsedTime = 0.0f;
    }
    }
}

void Ship::OnUpdate(float deltaTime) {
    shotElapsedTime += deltaTime;
    if(mPosition.x < 0)
        mPosition.x = mGame->WINDOW_WIDTH;
    else if(mPosition.x > mGame->WINDOW_WIDTH)
        mPosition.x = 0;
    if(mPosition.y < 0)
        mPosition.y = mGame->WINDOW_HEIGHT;
    else if(mPosition.y > mGame->WINDOW_HEIGHT)
        mPosition.y = 0;
}
