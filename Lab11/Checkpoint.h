//
//  Checkpoint.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/7.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Checkpoint_hpp
#define Checkpoint_hpp

#include <stdio.h>
#include "Actor.h"

class Checkpoint : public Actor{
public:
    Checkpoint(class Game* g, Actor* parent);
    class MeshComponent* mc;
    class CollisionComponent* cc;
};

#endif /* Checkpoint_hpp */
