//
//  Player.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Player.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "CollisionComponent.h"
#include "Renderer.h"
#include "Game.h"
#include "PlayerMove.h"

Player::Player(Game* g) : Actor(g){
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Ship.gpmesh"));
    cc = new CollisionComponent(this);
    cc->SetSize(100.0f, 40.0f, 60.0f);
    pm = new PlayerMove(this);
}
