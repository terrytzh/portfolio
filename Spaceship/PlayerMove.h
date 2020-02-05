//
//  PlayerMove.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/29.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>
#include "MoveComponent.h"
#include "Math.h"

class PlayerMove : public MoveComponent{
public:
    PlayerMove(class Player* owner);
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    float GetSpeed(){return speedMultiplier * PLAYER_FORWARD_SPEED;}
    
protected:
    Vector3 velocity;
    class Player* mPlayer;
    bool spacebarPressed = false;
    float speedMultiplier = 1.0f;
    float speedIncreaseTimer = 0.0f;
    
    const float PLAYER_FORWARD_SPEED = 400.0f;
    const float PLAYER_MOVE_SPEED = 300.0f;
    const float PLAYER_Y_LIMIT = 195.0f;
    const float PLAYER_Z_LIMIT = 225.0f;
    const float HDist = 300.0f;
    const float VDist = 100.0f;
    const float TargetDist = 20.0f;
};

#endif /* PlayerMove_hpp */
