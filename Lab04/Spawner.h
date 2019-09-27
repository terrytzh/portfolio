//
//  Spawner.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Spawner_hpp
#define Spawner_hpp

#include <stdio.h>
#include "Actor.h"

//Just for spawning!
class Spawner : public Actor{
public:
    Spawner(class Game* g);
    void OnUpdate(float deltaTime) override;
};

#endif /* Spawner_hpp */
