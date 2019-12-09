//
//  Arrow.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/7.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Arrow_hpp
#define Arrow_hpp

#include <stdio.h>
#include "Actor.h"

class Arrow : public Actor{
public:
    Arrow(class Game* g, Actor* parent);
    class MeshComponent* mc;

protected:
    void OnUpdate(float deltaTime) override;
    
    const float ARROW_SCALE = 0.15f;
};

#endif /* Arrow_hpp */
