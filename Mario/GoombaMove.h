//
//  GoombaMove.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef GoombaMove_hpp
#define GoombaMove_hpp

#include <stdio.h>
#include "MoveComponent.h"

class GoombaMove : public MoveComponent{
public:
    GoombaMove(class Actor* owner);
    void Update(float deltaTime) override;
    
protected:
    class Goomba* goomba;
    float mYSpeed;
    const float GOOMBA_VELOCITY = 100.0f;
};

#endif /* GoombaMove_hpp */
