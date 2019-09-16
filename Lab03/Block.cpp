//
//  Block.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/15.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Block.h"
#include "Actor.h"

Block::Block(Game* g, BlockType btype) : Actor(g) {
    type = btype;
}
