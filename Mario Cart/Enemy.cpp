//
//  Enemy.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Enemy.h"
#include "Game.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "EnemyMove.h"

Enemy::Enemy(Game* g) : Actor(g){
    SetScale(0.75f);
    meshc = new MeshComponent(this);
    meshc->SetMesh(g->GetRenderer()->GetMesh("Assets/Kart.gpmesh"));
    meshc->SetTextureIndex(6);
    em = new EnemyMove(this);
}



