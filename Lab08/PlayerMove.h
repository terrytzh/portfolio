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
#include "VehicleMove.h"
#include "Math.h"

class PlayerMove : public VehicleMove{
public:
    PlayerMove(class Player* owner);
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    void OnLapChange(int newLap) override;
    
protected:
    class Player* mPlayer;
    
    const float PLAYER_FORWARD_SPEED = 400.0f;
    const float PLAYER_MOVE_SPEED = 300.0f;
    const float PLAYER_Y_LIMIT = 195.0f;
    const float PLAYER_Z_LIMIT = 225.0f;
    const float HDist = 60.0f;
    const float VDist = 70.0f;
    const float TargetDist = 75.0f;
};

#endif /* PlayerMove_hpp */
