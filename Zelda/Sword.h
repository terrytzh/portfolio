//
//  Sword.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Sword_hpp
#define Sword_hpp

#include <stdio.h>
#include "Actor.h"

class Sword : public Actor{
public:
    Sword(class Game* g);
    class SpriteComponent* sprite;
    class CollisionComponent* cc;
    
};

#endif /* Sword_hpp */
