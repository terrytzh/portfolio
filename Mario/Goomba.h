//
//  Goomba.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Goomba_hpp
#define Goomba_hpp

#include <stdio.h>
#include "Actor.h"

class Goomba : public Actor{
public:
    Goomba(class Game* g);
    ~Goomba();
    class AnimatedSprite* asprite;
    class GoombaMove* gm;
    class CollisionComponent* cc;
    
    void SetStompedState(bool state){isStomped = state;}
    bool GetStompedState(){return isStomped;}
    
protected:
    void OnUpdate(float deltaTime) override;
    
    const float GOOMBA_SIZE = 32.0f;
    
    bool isStomped = false;
    float deadTime = 0.0f;
};

#endif /* Goomba_hpp */
