//
//  SideBlock.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/29.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "SideBlock.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Player.h"

SideBlock::SideBlock(Game* g) : Actor(g){
    SetScale(500.0f);
    mc = new MeshComponent(this);
    mc->SetMesh(g->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    mc->SetTextureIndex(1);
}

void SideBlock::OnUpdate(float deltaTime){
    if(mGame->GetPlayer()->GetPosition().x - GetPosition().x > 2000.0f){
        SetState(ActorState::Destroy);
    }
}
