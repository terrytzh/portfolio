//
//  Paddle.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/17.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include <stdio.h>
#include "Actor.h"


class Paddle : public Actor{
public:
    Paddle(class Game* g);
    class SpriteComponent* sprite;
    class MoveComponent* mc;
    class CollisionComponent* cc;
    
    float GetPaddleWidth(){return PADDLE_WIDTH;}
    float GetPaddleHeight(){return PADDLE_HEIGHT;}
    float GetPaddleSpeed(){return PADDLE_SPEED;}
    
protected:
    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;
    
    const float PADDLE_SPEED = 400.0f;
    const float PADDLE_WIDTH = 104.0f;
    const float PADDLE_HEIGHT = 24.0f;
};


#endif /* Paddle_hpp */
