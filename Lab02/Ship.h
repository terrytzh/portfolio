//
//  Ship.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/13.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

#include <stdio.h>
#include "Actor.h"

class Ship : public Actor {
    
public:
    Ship(class Game* g);
    class SpriteComponent* sprite;
    class MoveComponent* move;
    
protected:
    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;
    
    const float SHIP_FORWARD_SPEED = 200.0;
    const float SHIP_ANGULAR_SPEED = 3.0;
    const float SHOOT_SPEED = 1.0f;
    float shotElapsedTime = 1.01f;
    
};

#endif /* Ship_hpp */
