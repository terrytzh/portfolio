//
//  PlayerMove.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/23.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>
#include "Math.h"
#include "MoveComponent.h"

enum class Direction{
    Left,Right,Up,Down,Idle
};

class PlayerMove : public MoveComponent{
public:
    PlayerMove(class Actor* owner);
    
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;

protected:
    class Player* player;
    Direction direction;
    
    void AccessDoor(class Door* d);
    void UnlockDoor(class Door* d);
    
    const float PLAYER_SPEED = 130.0f;
};

#endif /* PlayerMove_hpp */
