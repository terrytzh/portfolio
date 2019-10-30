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

class PlayerMove : public MoveComponent{
public:
    PlayerMove(class Actor* owner);
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    
};

#endif /* PlayerMove_hpp */
