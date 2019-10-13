//
//  Player.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/23.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"


class Player : public Actor {
public:
    Player(class Game* g);
    class AnimatedSprite* asprite;
    class CollisionComponent* cc;
    class PlayerMove* pm;
    
    void SetIsDead(bool dead){isDead = dead;}
    bool GetIsDead(){return isDead;}
    
    void SetKeyCount(int count){keyCount = count;}
    int GetKeyCount(){return keyCount;}
    
    void TakeDamage(int amount);
    
    
protected:
    void OnUpdate(float deltaTime) override;
    
    const float PLAYER_WIDTH = 20.0f;
    const float PLAYER_HEIGHT = 20.0f;
    
    bool isDead = false;
    int keyCount = 0;
    int PLAYER_HP = 10;
    float invincibilityTimer = 0.0f;
    
};

#endif /* Player_hpp */
