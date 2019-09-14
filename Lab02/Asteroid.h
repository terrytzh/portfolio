//
//  Asteroid.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Asteroid_hpp
#define Asteroid_hpp

#include <stdio.h>
#include "Actor.h"

class Asteroid : public Actor {
public:
    Asteroid(class Game* g);
    ~Asteroid();
    class SpriteComponent* sprite;
    class MoveComponent* move;
    
protected:
    void OnUpdate(float deltaTime) override;
};

#endif /* Asteroid_hpp */
