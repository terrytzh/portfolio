//
//  Block.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/29.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Block.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Player.h"

Block::Block(Game* g, bool exploding) : Actor(g){
    isExploding = exploding;
    SetScale(25.0f);
    mc = new MeshComponent(this);
    mc->SetMesh(g->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    if(isExploding)
        mc->SetTextureIndex(4);
    else
        mc->SetTextureIndex(2);
    cc = new CollisionComponent(this);
    cc->SetSize(1.0f, 1.0f, 1.0f);
    
    g->AddBlock(this);
}

Block::~Block(){
    mGame->RemoveBlock(this);
}

void Block::OnUpdate(float deltaTime){
    if(mGame->GetPlayer()->GetPosition().x - GetPosition().x > 2000.0f){
        SetState(ActorState::Destroy);
    }
}

void Block::Destroy(){
    SetState(ActorState::Destroy);
    if(isExploding){
        Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/BlockExplode.wav"), 0);
        for(auto b : mGame->GetBlocks()){
            if((b->GetPosition() - GetPosition()).Length() <= 50.0f && b->GetState() != ActorState::Destroy){
                b->Destroy();
            }
        }
    }
}
