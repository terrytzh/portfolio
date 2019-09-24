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
#include "Paddle.h"
#include "Block.h"
#include "CollisionComponent.h"

BallMove::BallMove(Actor* owner) : MoveComponent(owner){
    ball = dynamic_cast<Ball*>(mOwner);
    velocity = ball->GetVelocity();
}

void BallMove::Update(float deltaTime){
    Vector2 temp = mOwner->GetPosition()+velocity*deltaTime;
    if(temp.x<Game::WALL_THICKNESS+ball->GetRadius()){
        temp.x = Game::WALL_THICKNESS+ball->GetRadius();
        velocity.x *= -1.0f;
    }
    else if(temp.x>Game::WINDOW_WIDTH-Game::WALL_THICKNESS-ball->GetRadius()){
        temp.x = Game::WINDOW_WIDTH-Game::WALL_THICKNESS-ball->GetRadius();
        velocity.x *= -1.0f;
    }
    if(temp.y<Game::WALL_THICKNESS+ball->GetRadius()){
        temp.y = Game::WALL_THICKNESS+ball->GetRadius();
        velocity.y *= -1.0f;
    }
    else if(temp.y>Game::WINDOW_HEIGHT+ball->GetRadius()){
        temp = Vector2(Game::WINDOW_WIDTH/2.0f, 600.0f);
        velocity = ball->GetVelocity();
    }
    else if(ball->cc->Intersect(mOwner->GetGame()->GetPaddle()->cc) && velocity.y > 0){
        Paddle* p = mOwner->GetGame()->GetPaddle();
        temp.y = 700.0f - ball->GetRadius() - p->GetPaddleHeight()/2.0f;
        if(temp.x < p->cc->GetMin().x + p->GetPaddleWidth()/3.0f)
            velocity = Vector2::Reflect(velocity, Vector2::Normalize(Vector2(-1,-4)));
        else if(temp.x > p->cc->GetMax().x - p->GetPaddleWidth()/3.0f)
            velocity = Vector2::Reflect(velocity, Vector2::Normalize(Vector2(1,-4)));
        else
            velocity = Vector2::Reflect(velocity, Vector2(0,-1));
    }
    
    Vector2 offset;
    for(auto block : mOwner->GetGame()->GetBlocks()){
        offset = Vector2(0,0);
        CollSide cs = ball->cc->GetMinOverlap(block->cc, offset);
        if(cs == CollSide::Left || cs == CollSide::Right){
            velocity.x *= -1.0f;
            block->SetState(ActorState::Destroy);
            temp -= offset;
            break;
        }
        else if(cs == CollSide::Top || cs == CollSide::Bottom){
            block->SetState(ActorState::Destroy);
            velocity.y *= -1.0f;
            temp -= offset;
            break;
        }
    }
    
    mOwner->SetPosition(temp);
}
