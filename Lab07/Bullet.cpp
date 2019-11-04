//
//  Bullet.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/3.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Bullet.h"
#include "Player.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Block.h"
#include "CollisionComponent.h"
#include "PlayerMove.h"
#include "MoveComponent.h"
#include "Renderer.h"
#include "Game.h"

Bullet::Bullet(Game* g) : Actor(g){
    SetScale(0.5f);
    //SetPosition(g->GetPlayer()->GetPosition());
    meshc = new MeshComponent(this);
    meshc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
    mc = new MoveComponent(this);
    mc->SetForwardSpeed(500.0f + g->GetPlayer()->pm->GetSpeed());
    cc = new CollisionComponent(this);
    cc->SetSize(10.0f, 10.0f, 10.0f);
}

void Bullet::OnUpdate(float deltaTime){
    if(lifeTimeer > 1.0f){
        SetState(ActorState::Destroy);
        return;
    }
    
    for(auto b : mGame->GetBlocks()){
        if(cc->Intersect(b->cc)){
            b->Destroy();
            SetState(ActorState::Destroy);
        }
    }
    
    
    lifeTimeer += deltaTime;
}
