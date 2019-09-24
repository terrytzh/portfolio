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
#include "MoveComponent.h"


class PlayerMove : public MoveComponent{
public:
    PlayerMove(class Actor* owner);
    
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;

protected:
    class Player* player;
    float mYSpeed = 0.0f;
    
    bool mSpacePressed = false;
    bool mInAir = false;
    
    const float PLAYER_SPEED = 300.0f;
};

#endif /* PlayerMove_hpp */
