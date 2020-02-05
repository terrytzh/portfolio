//
//  Ball.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/17.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "Actor.h"

class Ball : public Actor{
public:
    Ball(class Game* g);
    class SpriteComponent* sprite;
    class BallMove* bm;
    class CollisionComponent* cc;
    
    class Vector2 GetVelocity(){return BALL_INITIAL_VELOCITY;}
    float GetRadius(){return BALL_RADIUS;}
    
    protected:
    const Vector2 BALL_INITIAL_VELOCITY = Vector2(250, -250);
    const float BALL_RADIUS = 10.0f;
    
};

#endif /* Ball_hpp */
