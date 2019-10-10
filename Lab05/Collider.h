//
//  Collider.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/1.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Collider_hpp
#define Collider_hpp

#include <stdio.h>
#include "Actor.h"

class Collider : public Actor{
public:
    Collider(class Game* g);
    class CollisionComponent* cc;
    
    void setCollisionComponent(float width, float height);
};

#endif /* Collider_hpp */
