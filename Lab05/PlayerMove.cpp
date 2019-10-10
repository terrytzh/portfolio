//
//  PlayerMove.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/23.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "PlayerMove.h"
#include "Game.h"
#include "Player.h"
#include "Block.h"
#include "Collider.h"
#include "Door.h"
#include "SecretBlock.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"

PlayerMove::PlayerMove(Actor* owner) : MoveComponent(owner){
    player = dynamic_cast<Player*>(owner);
}

void PlayerMove::Update(float deltaTime){
    Vector2 dir;
    switch (direction) {
        case Direction::Left:
            dir = Vector2(-1,0);
            player->asprite->SetAnimation("walkLeft");
            break;
            
        case Direction::Right:
            dir = Vector2(1,0);
            player->asprite->SetAnimation("walkRight");
            break;
        
        case Direction::Up:
            dir = Vector2(0,-1);
            player->asprite->SetAnimation("walkUp");
            break;
        
        case Direction::Down:
            dir = Vector2(0,1);
            player->asprite->SetAnimation("walkDown");
            break;
            
        case Direction::Idle:
            dir = Vector2(0,0);
            break;
    }
    
    Vector2 pos = mOwner->GetPosition();
    pos += dir * PLAYER_SPEED * deltaTime;
    mOwner->SetPosition(pos);
    
    Vector2 offset;
    CollSide side;
    
    for(auto d: player->GetGame()->GetDoors()){
        offset = Vector2(0,0);
        side = player->cc->GetMinOverlap(d->cc, offset);
        if(side != CollSide::None &&
           ((direction == Direction::Right && d->GetDirection() == DoorDirection::Right) ||
               (direction == Direction::Left && d->GetDirection() == DoorDirection::Left) ||
               (direction == Direction::Up && d->GetDirection() == DoorDirection::Up) ||
               (direction == Direction::Down && d->GetDirection() == DoorDirection::Down)))
               {
                   if(d->GetState() == DoorState::Open){
                       AccessDoor(d);
                       pos = player->GetPosition();
                       break;
                   }
                   else if(d->GetState() == DoorState::Locked && player->GetKeyCount()>0){
                       UnlockDoor(d);
                       AccessDoor(d);
                       pos = player->GetPosition();
                       break;
                   }
               }
        
        
    }
    
    for(auto s: player->GetGame()->GetSecretBlocks()){
        offset = Vector2(0,0);
        side = player->cc->GetMinOverlap(s->cc, offset);
        switch (s->GetDirection()) {
            case SecretBlockDirection::Left:
                if(side == CollSide::Left){
                    s->Move(PLAYER_SPEED * deltaTime / 3.0f);
                    offset *= 0.667f;
                }
                break;
                
            case SecretBlockDirection::Right:
                if(side == CollSide::Right){
                    s->Move(PLAYER_SPEED * deltaTime / 3.0f);
                    offset *= 0.667f;
                }
                break;
            
            case SecretBlockDirection::Up:
                if(side == CollSide::Top){
                    s->Move(PLAYER_SPEED * deltaTime / 3.0f);
                    offset *= 0.667f;
                }
                break;
            
            case SecretBlockDirection::Down:
                if(side == CollSide::Bottom){
                    s->Move(PLAYER_SPEED * deltaTime / 3.0f);
                    offset *= 0.667f;
                }
                break;
        }
        pos += offset;
        player->SetPosition(pos);
    }
    
    for(auto c : player->GetGame()->GetColliders()){
        offset = Vector2(0,0);
        side = player->cc->GetMinOverlap(c->cc, offset);
        pos += offset;
        player->SetPosition(pos);
    }
    
    Vector2 half(player->GetGame()->WINDOW_WIDTH/2.0f, player->GetGame()->WINDOW_HEIGHT/2.0f);
    player->GetGame()->SetCamPosition(player->GetPosition()-half);
}

void PlayerMove::ProcessInput(const Uint8 *keyState){
    if(keyState[SDL_SCANCODE_LEFT])
        direction = Direction::Left;
    else if(keyState[SDL_SCANCODE_RIGHT])
        direction = Direction::Right;
    else if(keyState[SDL_SCANCODE_UP])
        direction = Direction::Up;
    else if(keyState[SDL_SCANCODE_DOWN])
        direction = Direction::Down;
    else
        direction = Direction::Idle;
}

void PlayerMove::UnlockDoor(class Door *d){
    player->SetKeyCount(player->GetKeyCount()-1);
    d->SetState(DoorState::Open);
    d->UpdateComponents();
}

void PlayerMove::AccessDoor(class Door *d){
    player->GetGame()->SetCurrentRoom(d->GetDestination());
    DoorDirection dir;
    switch (d->GetDirection()) {
        case DoorDirection::Up:
            dir = DoorDirection::Down;
            break;
            
        case DoorDirection::Down:
            dir = DoorDirection::Up;
            break;
        
        case DoorDirection::Left:
            dir = DoorDirection::Right;
            break;
            
        case DoorDirection::Right:
            dir = DoorDirection::Left;
            break;
    }
    
    for(auto otherDoor : player->GetGame()->GetDoors()){
        if(otherDoor->GetDirection() == dir){
            Vector2 doorPos = otherDoor->GetPosition();
            switch (dir) {
                case DoorDirection::Up:
                    doorPos.y += otherDoor->cc->GetHeight();
                    player->SetPosition(doorPos);
                    break;
                    
                case DoorDirection::Down:
                    doorPos.y -= otherDoor->cc->GetHeight();
                    player->SetPosition(doorPos);
                    break;
                    
                case DoorDirection::Left:
                    doorPos.x += otherDoor->cc->GetWidth();
                    player->SetPosition(doorPos);
                    break;
                    
                case DoorDirection::Right:
                    doorPos.x -= otherDoor->cc->GetWidth();
                    player->SetPosition(doorPos);
                    break;
            }
        }
    }
}
