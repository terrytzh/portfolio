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
    Block(class Game* g, Actor* parent);
    ~Block();
    class MeshComponent* meshc;
    class CollisionComponent* cc;
    void SetIsMirror(bool b){isMirror = b;}
    bool GetIsMirror(){return isMirror;}
    void SetIsRotating(bool b){isRotating = b;}
    bool GetIsRotating(){return isRotating;}
    
protected:
    bool isMirror = false;
    bool isRotating = false;
    void OnUpdate(float deltaTime) override;
    
    const float ROTATE_SPEED = Math::PiOver2 / 2.0f;
};

#endif /* Block_hpp */
