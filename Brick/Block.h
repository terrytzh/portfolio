//
//  Block.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/15.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Actor.h"


enum class BlockType{
    A,B,C,D,E,F
};

class Block : public Actor {
public:
    Block(class Game* g, char btype);
    ~Block();
    BlockType GetType(){return type;}
    void SetType(BlockType btype){type = btype;}
    
    class SpriteComponent* sprite;
    class MoveComponent* mc;
    class CollisionComponent* cc;
    
    float GetBlockWidth(){return BLOCK_WIDTH;}
    float GetBlockHeight(){return BLOCK_HEIGHT;}
    
protected:
    BlockType type;
    
    const float BLOCK_WIDTH = 64.0f;
    const float BLOCK_HEIGHT = 32.0f;
};
#endif /* Block_hpp */
