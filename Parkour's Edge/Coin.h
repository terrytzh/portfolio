//
//  Coin.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/8.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Coin_hpp
#define Coin_hpp

#include <stdio.h>
#include "Actor.h"

class Coin : public Actor{
public:
    Coin(class Game* g, Actor* parent);
    class MeshComponent* mc;
    class CollisionComponent* cc;

protected:
    void OnUpdate(float deltaTime) override;
    
    const float COIN_LENGTH = 100.0f;
    const float COIN_ROTATE_SPEED = Math::Pi;
};


#endif /* Coin_hpp */
