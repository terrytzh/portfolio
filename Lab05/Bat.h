//
//  Bat.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Bat_hpp
#define Bat_hpp

#include <stdio.h>
#include "Actor.h"

class Bat : public Actor{
public:
    Bat(class Game* g);
    class AnimatedSprite* as;
    class CollisionComponent* cc;
    class EnemyComponent* ec;

protected:
    void OnUpdate(float deltaTime) override;
    
    Vector2 direction;
    float moveTime = 0.0f;
    
    const float BAT_SPEED = 50.0f;
    
};


#endif /* Bat_hpp */
