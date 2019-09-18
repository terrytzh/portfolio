//
//  BallMove.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/17.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "BallMove.h"
#include "Ball.h"
#include "Game.h"

BallMove::BallMove(Actor* owner) : MoveComponent(owner){
    velocity = BALL_INITIAL_VELOCITY;
}

void BallMove::Update(float deltaTime){
    Vector2 temp = mOwner->GetPosition()+velocity*deltaTime;
    if(temp.x<Game::WALL_THICKNESS+BALL_RADIUS){
        temp.x = Game::WALL_THICKNESS+BALL_RADIUS;
        velocity.x *= -1.0f;
    }
    else if(temp.x>Game::WINDOW_WIDTH-Game::WALL_THICKNESS-BALL_RADIUS){
        temp.x = Game::WINDOW_WIDTH-Game::WALL_THICKNESS-BALL_RADIUS;
        velocity.x *= -1.0f;
    }
    if(temp.y<Game::WALL_THICKNESS+BALL_RADIUS){
        temp.y = Game::WALL_THICKNESS+BALL_RADIUS;
        velocity.y *= -1.0f;
    }
    else if(temp.y>Game::WINDOW_HEIGHT+BALL_RADIUS){
        temp = Vector2(Game::WINDOW_WIDTH/2.0f, 600.0f);
        velocity = BALL_INITIAL_VELOCITY;
    }
    mOwner->SetPosition(temp);
}
