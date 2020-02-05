//
//  Checkpoint.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/7.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Checkpoint.h"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Player.h"
#include "Renderer.h"

Checkpoint::Checkpoint(Game* g, Actor* parent) : Actor(g,parent){
    mc = new MeshComponent(this);
    mc->SetMesh(g->GetRenderer()->GetMesh("Assets/Checkpoint.gpmesh"));
    mc->SetTextureIndex(1);
    cc = new CollisionComponent(this);
    cc->SetSize(25.0f, 25.0f, 25.0f);
}

void Checkpoint::OnUpdate(float deltaTime){
    if(mGame->GetCheckpoints().front() == this){
        mc->SetTextureIndex(0);
        isActivated = true;
    }
    if(isActivated){
        if(cc->Intersect(mGame->GetPlayer()->cc)){
            if(!mLevelString.empty()){
                mGame->SetNextLevel(mLevelString);
            }
            else{
                mGame->GetPlayer()->SetRespawnPos(GetPosition());
                SetState(ActorState::Destroy);
                mGame->GetCheckpoints().pop();
            }
            mGame->SetCurrCheckpointText(mText);
            mGame->GetCheckpointTimer() = 0.0f;
            Mix_PlayChannel(-1, mGame->GetSound("Assets/Sounds/Checkpoint.wav"), 0);
        }
    }
}
