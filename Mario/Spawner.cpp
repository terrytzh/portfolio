//
//  Spawner.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Spawner.h"
#include "Game.h"
#include "Goomba.h"
#include "Player.h"

Spawner::Spawner(Game* g) : Actor(g){
    
}

void Spawner::OnUpdate(float deltaTime){
    if(GetPosition().x - mGame->GetPlayer()->GetPosition().x < 600.0f){
        Goomba* g = new Goomba(mGame);
        g->SetPosition(GetPosition());
        SetState(ActorState::Destroy);
    }
}
