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
    Block(class Game* g, BlockType btype);
    BlockType GetType(){return type;}
    void SetType(BlockType btype){type = btype;}
    
protected:
    BlockType type;
};
#endif /* Block_hpp */
