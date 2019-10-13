//
//  Boss.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Boss_hpp
#define Boss_hpp

#include <stdio.h>
#include "Actor.h"

class Boss : public Actor{
public:
    Boss(class Game* g);
    class AnimatedSprite* as;
    class CollisionComponent* cc;
    class EnemyComponent* ec;
    
protected:
    const int BOSS_DAMAGE = 2;
    
    float attackTimer = 0.0f;
    
    void OnUpdate(float deltaTime) override;
};

#endif /* Boss_hpp */
