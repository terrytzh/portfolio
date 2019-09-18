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

protected:
    
};

#endif /* Ball_hpp */
