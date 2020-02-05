//
//  Sword.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Sword.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

Sword::Sword(Game* g) : Actor(g){
    sprite = new SpriteComponent(this);
    sprite->SetTexture(g->GetTexture("Assets/Sword/Up.png"));
    cc = new CollisionComponent(this);
    cc->SetSize(25.0f, 25.0f);
    
}
