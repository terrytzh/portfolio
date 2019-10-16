//
//  Fireball.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Fireball_hpp
#define Fireball_hpp

#include <stdio.h>
#include "Actor.h"

class Fireball : public Actor{
public:
    Fireball(class Game* g, bool isGreen = false);
    class SpriteComponent* sprite;
    class MoveComponent* mc;
    class CollisionComponent* cc;
    
protected:
    float lifeTime = 0.0f;
    
    const float FORWARD_SPEED = 200.0f;
    const float FIREBALL_WIDTH = 16.0f;
    const float MAXIMUM_LIFETIME = 2.0f;
    
    void OnUpdate(float deltaTime) override;
};

#endif /* Fireball_hpp */
