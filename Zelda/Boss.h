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
    const float BOSS_WIDTH = 50.0f;
    const float BOSS_HEIGHT = 64.0f;
    
    const float NORMAL_ATTACK_TIME = 2.0f;
    const float ENRAGED_ATTACK_TIME = 1.0f;
    const int ENRAGED_HP = 2;
    const int INITIAL_HP = 5;
    
    float attackTimer = 0.0f;
    
    void OnUpdate(float deltaTime) override;
};

#endif /* Boss_hpp */
