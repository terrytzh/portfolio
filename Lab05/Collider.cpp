//
//  Collider.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/1.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Collider.h"
#include "Game.h"
#include "CollisionComponent.h"

Collider::Collider(Game* g) : Actor(g){
    cc = new CollisionComponent(this);
}

void Collider::setCollisionComponent(float width, float height){
    cc->SetSize(width, height);
}
