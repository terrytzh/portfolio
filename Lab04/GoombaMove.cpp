//
//  GoombaMove.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "GoombaMove.h"
#include "CollisionComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Block.h"
#include "Goomba.h"


GoombaMove::GoombaMove(Actor* owner) : MoveComponent(owner){
    SetForwardSpeed(-GOOMBA_VELOCITY);
    goomba = dynamic_cast<Goomba*>(owner);
    mYSpeed = 0.0f;
}

void GoombaMove::Update(float deltaTime){
    if(goomba->GetStompedState())
        return;
    
    Vector2 pos = goomba->GetPosition();
    pos.x += deltaTime * GetForwardSpeed();
    pos.y += deltaTime * mYSpeed;
    
    goomba->SetPosition(pos);
    
    //Block Collision
    Vector2 offset;
    for(auto b : mOwner->GetGame()->GetBlocks()){
        offset = Vector2(0,0);
        CollSide side = goomba->cc->GetMinOverlap(b->cc, offset);
        if(side != CollSide::None){
            //Fall on ground
            if(side == CollSide::Top && mYSpeed > 0.0f){
                mYSpeed = 0.0f;
            }
            //Prevent floating
            else if(side == CollSide::Bottom && mYSpeed < 0.0f){
                mYSpeed = 0.0f;
            }
            pos -= offset;
            goomba->SetPosition(pos);
            
        }
    }
    
    for(auto b : mOwner->GetGame()->GetBlocks()){
        offset = Vector2(0,0);
        CollSide side = goomba->cc->GetMinOverlap(b->cc, offset);
        if(side != CollSide::None){
            if(side == CollSide::Left && Math::Abs(b->GetPosition().y-goomba->GetPosition().y) < 10.0f){
                SetForwardSpeed(-GOOMBA_VELOCITY);
            }
            else if(side == CollSide::Right && Math::Abs(b->GetPosition().y-goomba->GetPosition().y) < 10.0f){
                SetForwardSpeed(GOOMBA_VELOCITY);
            }
            pos -= offset;
            goomba->SetPosition(pos);
            
        }
    }
    
    
    
    //Enemy collision
    for(auto g : mOwner->GetGame()->GetEnemies()){
        if(g == goomba)
            continue;
        offset = Vector2(0,0);
        CollSide side = goomba->cc->GetMinOverlap(g->cc, offset);
        if(side != CollSide::None){
            //Fall on ground
            if(side == CollSide::Top && mYSpeed > 0.0f){
                mYSpeed = 0.0f;
            }
            //Prevent floating
            else if(side == CollSide::Bottom && mYSpeed < 0.0f){
                mYSpeed = 0.0f;
            }
            else if(side == CollSide::Left){
                this->SetForwardSpeed(-GOOMBA_VELOCITY);
                g->gm->SetForwardSpeed(GOOMBA_VELOCITY);
            }
            else if(side == CollSide::Right){
                this->SetForwardSpeed(GOOMBA_VELOCITY);
                g->gm->SetForwardSpeed(-GOOMBA_VELOCITY);
            }
            
            pos -= offset;
            goomba->SetPosition(pos);
        }
    }
    
    
    if(goomba->GetPosition().y > 520.0f)
        goomba->SetState(ActorState::Destroy);
    
    mYSpeed += deltaTime * 2000.0f;
    
}
