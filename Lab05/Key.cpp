//
//  Key.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Key.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "Collectible.h"
#include "Player.h"

Key::Key(Game* g) : Actor(g){
    cc = new CollisionComponent(this);
    cc->SetSize(16.0f, 32.0f);
    sprite = new SpriteComponent(this);
    sprite->SetTexture(mGame->GetTexture("Assets/Key.png"));
    
    Collectible* collect = new Collectible(this);
    collect->SetOnCollect([this]{
        GetGame()->GetPlayer()->SetKeyCount(GetGame()->GetPlayer()->GetKeyCount()+1);
    });
}
