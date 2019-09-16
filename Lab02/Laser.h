//
//  Laser.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Laser_hpp
#define Laser_hpp

#include <stdio.h>
#include "Actor.h"

class Laser : public Actor{
public:
    Laser(class Game* g);
    class SpriteComponent* sprite;
    class MoveComponent* move;
    
protected:
    void OnUpdate(float deltaTime) override;
    float spawn_time;
    
    const float MAXIMUM_LIFETIME = 1.0f;
    const float LASER_SPEED = 400.0f;
    const float COLLIDE_RANGE = 70.0f;
};

#endif /* Laser_hpp */
