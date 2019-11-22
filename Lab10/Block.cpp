//
//  Block.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/7.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Block.h"
#include "Game.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"

Block::Block(Game* g) : Actor(g){
    SetScale(64.0f);
    meshc = new MeshComponent(this);
    meshc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    cc = new CollisionComponent(this);
    cc->SetSize(1.0f, 1.0f, 1.0f);
    mGame->GetObjects().push_back(this);
}

Block::~Block(){
    for(std::vector<Actor*>::iterator i = mGame->GetObjects().begin(); i != mGame->GetObjects().end(); i++){
        if(*i == this){
            mGame->GetObjects().erase(i);
            break;
        }
    }
}
