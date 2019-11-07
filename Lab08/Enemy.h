//
//  Enemy.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "Actor.h"

class Enemy : public Actor{
public:
    Enemy(class Game* g);
    class MeshComponent* meshc;
    class EnemyMove* em;
};

#endif /* Enemy_hpp */
