//
//  Block.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/29.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"

class Block : public Actor{
public:
    Block(class Game* g, bool exploding);
    ~Block();
    class MeshComponent* mc;
    class CollisionComponent* cc;
    
    bool GetExploding(){return isExploding;}
    void Destroy();
    
protected:
    void OnUpdate(float deltaTime) override;
    bool isExploding = false;
};

#endif /* Block_hpp */
