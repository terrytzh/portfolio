//
//  Block.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/15.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Block.h"
#include "Actor.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Block::Block(Game* g, char btype) : Actor(g) {
    sprite = new SpriteComponent(this);
    switch (btype) {
        case 'A':
            type = BlockType::A;
            sprite->SetTexture(mGame->GetTexture("Assets/BlockA.png"));
            break;
        
        case 'B':
            type = BlockType::B;
            sprite->SetTexture(mGame->GetTexture("Assets/BlockB.png"));
            break;
            
        case 'C':
            type = BlockType::C;
            sprite->SetTexture(mGame->GetTexture("Assets/BlockC.png"));
            break;
        
        case 'D':
            type = BlockType::D;
            sprite->SetTexture(mGame->GetTexture("Assets/BlockD.png"));
            break;
        
        case 'E':
            type = BlockType::E;
            sprite->SetTexture(mGame->GetTexture("Assets/BlockE.png"));
            break;
        
        case 'F':
            type = BlockType::F;
            sprite->SetTexture(mGame->GetTexture("Assets/BlockF.png"));
            break;
        
        default:
            break;
    }
    mc = new MoveComponent(this);
}
