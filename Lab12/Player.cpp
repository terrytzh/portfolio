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
#include "Arrow.h"

Player::Player(Game* g, Actor* parent) : Actor(g,parent){
    pm = new PlayerMove(this);
    camc = new CameraComponent(this);
    cc = new CollisionComponent(this);
    cc->SetSize(50.0f, 175.0f, 50.0f);
}
