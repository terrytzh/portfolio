//
//  Door.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Door_hpp
#define Door_hpp

#include <stdio.h>
#include <string>
#include "Actor.h"


enum class DoorDirection{
    Left,Right,Up,Down
};

enum class DoorState{
    Open,Closed,Locked
};

class Door : public Actor{
public:
    Door(class Game* g, DoorState state = DoorState::Open, DoorDirection direction = DoorDirection::Down, std::string destination = "");
    class CollisionComponent* cc;
    class SpriteComponent* sprite;
    
    void SetState(DoorState state){mState = state;}
    DoorState GetState(){return mState;}
    
    void SetDirection(DoorDirection direction){mDirection = direction;}
    DoorDirection GetDirection(){return mDirection;}
    
    void SetDestination(std::string dest){mDestination = dest;}
    std::string GetDestination(){return mDestination;}
    
    void UpdateComponents();
    
protected:
    
    const float DOOR_WIDTH = 64.0f;
    const float DOOR_HEIGHT = 30.0f;
    
    DoorState mState;
    DoorDirection mDirection;
    std::string mDestination;
};

#endif /* Door_hpp */
