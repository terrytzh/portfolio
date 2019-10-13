//
//  Skeleton.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Skeleton_hpp
#define Skeleton_hpp

#include <stdio.h>
#include "Actor.h"

class Skeleton : public Actor{
public:
    Skeleton(class Game* g);
    class AnimatedSprite* as;
    class CollisionComponent* cc;
    class EnemyComponent* ec;
    
protected:
    void OnUpdate(float deltaTime) override;
    
    float COOLDOWN_TIMER;
    float timeCount = 0.0f;
};

#endif /* Skeleton_hpp */
