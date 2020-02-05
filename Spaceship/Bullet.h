//
//  Bullet.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/3.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "Actor.h"

class Bullet : public Actor{
public:
    Bullet(class Game* g);
    class MeshComponent* meshc;
    class CollisionComponent* cc;
    class MoveComponent* mc;
    
protected:
    void OnUpdate(float deltaTime) override;
    float lifeTimeer = 0.0f;
};

#endif /* Bullet_hpp */
