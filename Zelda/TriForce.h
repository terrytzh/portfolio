//
//  TriForce.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef TriForce_hpp
#define TriForce_hpp

#include <stdio.h>
#include "Actor.h"

class TriForce : public Actor{
public:
    TriForce(class Game* g);
    class AnimatedSprite* as;
    class CollisionComponent* cc;
    class Collectible* collectible;
    
    
};

#endif /* TriForce_hpp */
