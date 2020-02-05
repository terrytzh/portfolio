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
#include "CameraComponent.h"
#include "PlayerUI.h"

Player::Player(Game* g) : Actor(g){
    SetScale(0.75f);
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Kart.gpmesh"));
    pm = new PlayerMove(this);
    camc = new CameraComponent(this);
    pu = new PlayerUI(this);
}
