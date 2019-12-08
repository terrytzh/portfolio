  //
//  LaserMine.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/1.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "LaserMine.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "LaserComponent.h"

LaserMine::LaserMine(Game* g, Actor* parent) : Actor(g,parent){
    mc = new MeshComponent(this);
    mc->SetMesh(mGame->GetRenderer()->GetMesh("Assets/LaserMine.gpmesh"));
    lc = new LaserComponent(this);
}
