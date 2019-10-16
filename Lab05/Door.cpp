//
//  Door.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Door.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"

Door::Door(Game* g, DoorState state, DoorDirection direction, std::string destination) : Actor(g){
    mDestination = destination;
    mState = state;
    mDirection = direction;
    
    cc = new CollisionComponent(this);
    sprite = new SpriteComponent(this);
    
    UpdateComponents();
}

void Door::UpdateComponents(){
    
    if(mDirection == DoorDirection::Up || mDirection == DoorDirection::Down){
        cc->SetSize(DOOR_HEIGHT, DOOR_WIDTH);
    }
    else{
        cc->SetSize(DOOR_WIDTH, DOOR_HEIGHT);
    }
    
    switch (mState) {
        case DoorState::Open:
            switch (mDirection) {
                case DoorDirection::Up:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/UpOpen.png"));
                    break;
                    
                case DoorDirection::Down:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/DownOpen.png"));
                    break;
                
                case DoorDirection::Left:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/LeftOpen.png"));
                    break;
                
                case DoorDirection::Right:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/RightOpen.png"));
                    break;
            }
            break;
            
        case DoorState::Closed:
            switch (mDirection) {
                case DoorDirection::Up:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/UpClosed.png"));
                    break;
                    
                case DoorDirection::Down:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/DownClosed.png"));
                    break;
                    
                case DoorDirection::Left:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/LeftClosed.png"));
                    break;
                    
                case DoorDirection::Right:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/RightClosed.png"));
                    break;
            }
            break;
            
        case DoorState::Locked:
            switch (mDirection) {
                case DoorDirection::Up:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/UpLocked.png"));
                    break;
                    
                case DoorDirection::Down:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/DownLocked.png"));
                    break;
                    
                case DoorDirection::Left:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/LeftLocked.png"));
                    break;
                    
                case DoorDirection::Right:
                    sprite->SetTexture(mGame->GetTexture("Assets/Door/RightLocked.png"));
                    break;
            }
            break;
    }
}
