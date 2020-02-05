//
//  EnemyComponent.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef EnemyComponent_hpp
#define EnemyComponent_hpp

#include <stdio.h>
#include <string>
#include <functional>
#include "Component.h"

class EnemyComponent : public Component{
public:
    EnemyComponent(class Actor* owner);
    ~EnemyComponent();
    
    void SetOnDeath(std::function<void()> func){mOnDeath = func;}
    void SetOnTakeDamage(std::function<void()> func){mOnTakeDamage = func;}
    
    void SetHP(int amount){hitPoint = amount;}
    int GetHP(){return hitPoint;}
    void SetCollisionDamage(int amount){collisionDamage = amount;}
    int GetCollisionDamage(){return collisionDamage;}
    
    void TakeDamage(int amount);
    void Update(float deltaTime) override;
    
protected:
    
    int hitPoint = 1;
    int collisionDamage = 1;
    float invinsibilityTimer = 0.0f;
    
    std::function<void()> mOnDeath;
    std::function<void()> mOnTakeDamage;
    std::string currentRoom;
};

#endif /* EnemyComponent_hpp */
