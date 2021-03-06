//
//  SecretBlock.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef SecretBlock_hpp
#define SecretBlock_hpp

#include <stdio.h>
#include "Actor.h"

enum class SecretBlockDirection{
    Left,Right,Up,Down
};

class SecretBlock : public Actor{
public:
    SecretBlock(class Game* g);
    class SpriteComponent* sprite;
    class CollisionComponent* cc;
    
    SecretBlockDirection GetDirection(){return direction;}
    void SetDirection(SecretBlockDirection dir){direction = dir;}
    
    void Move(float distance);
protected:
    SecretBlockDirection direction;
    float moveDistance;
    
    const float BLOCK_WIDTH = 32.0f;
    
    bool isUnlocked = false;
    
    void OpenClosedDoors();
};

#endif /* SecretBlock_hpp */
