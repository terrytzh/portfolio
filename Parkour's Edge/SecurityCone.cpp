//
//  SecurityCone.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/8.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "SecurityCone.h"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Player.h"
#include "PlayerMove.h"
#include "Renderer.h"

SecurityCone::SecurityCone(Game* g, Actor* parent) : Actor(g, parent){
    mc = new MeshComponent(this, true);
    mc->SetMesh(g->GetRenderer()->GetMesh("Assets/Cone.gpmesh"));
    SetPosition(RELATIVE_POS);
    SetScale(CONE_SCALE);
}

void SecurityCone::OnUpdate(float deltaTime){
    Vector3 playerDir = mGame->GetPlayer()->GetPosition() - GetWorldPosition();
    float playerDistance = playerDir.Length();
    playerDir.Normalize();
    float playerAngle = Math::Acos(Vector3::Dot(playerDir, GetWorldForward()));
    if(playerAngle < Math::PiOver2 / 3.0f && playerDistance <  CONE_HEIGHT / Math::Cos(playerAngle)){
        if(mState == Idle){
            mState = Aware;
            securityTimer = AWARE_TIME;
            mc->SetTextureIndex(1);
            mDetectedSFX =  Mix_PlayChannel(Mix_GroupAvailable(1),GetGame()->GetSound("Assets/Sounds/SecurityDetected.wav"),0);
        }
        else if(mState == Aware && securityTimer < 0.0f){
            mState = Alert;
            securityTimer = ALERT_TIME;
            mc->SetTextureIndex(2);
        }
        else if(mState == Alert && securityTimer < 0.0f){
            mGame->GetPlayer()->pm->Respawn();
        }
    }
    else{
        mState = Idle;
        mc->SetTextureIndex(0);
        if(mDetectedSFX != -1){
            Mix_HaltChannel(mDetectedSFX);
            mDetectedSFX = -1;
        }
    }
    
    if(mState == Aware || mState == Alert){
        securityTimer -= deltaTime;
    }
}
