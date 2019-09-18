//
//  BallMove.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/17.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef BallMove_hpp
#define BallMove_hpp

#include <stdio.h>
#include "Math.h"
#include "MoveComponent.h"

class BallMove : public MoveComponent{
public:
    BallMove(class Actor* owner);
    
    void Update(float deltaTime) override;
    
    Vector2 GetVelocity(){return velocity;}
    void SetVelocity(Vector2 v){velocity = v;}
    
    const Vector2 BALL_INITIAL_VELOCITY = Vector2(250, -250);
    const float BALL_RADIUS = 11.0f;
    
protected:
    Vector2 velocity;
    
};

#endif /* BallMove_hpp */
