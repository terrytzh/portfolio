//
//  Block.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/7.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"

class Block : public Actor{
public:
    Block(class Game* g);
    ~Block();
    class MeshComponent* meshc;
    class CollisionComponent* cc;
    
};

#endif /* Block_hpp */
