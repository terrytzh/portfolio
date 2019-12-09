//
//  Arrow.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/7.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Arrow.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Checkpoint.h"
#include "Player.h"

Arrow::Arrow(Game* g, Actor* parent) : Actor(g, parent){
    mc = new MeshComponent(this);
    mc->SetMesh(g->GetRenderer()->GetMesh("Assets/Arrow.gpmesh"));
    SetScale(ARROW_SCALE);
}

void Arrow::OnUpdate(float deltaTime){
    if(mGame->GetCheckpoints().front() == NULL){
        SetQuaternion(Quaternion::Identity);
    }
    else{
        Vector3 checkpointDir = mGame->GetCheckpoints().front()->GetPosition() - mGame->GetPlayer()->GetPosition();
        checkpointDir.Normalize();
        float angle = Math::Acos(Vector3::Dot(Vector3::UnitX, checkpointDir));
        if(Vector3::Dot(Vector3::UnitX, checkpointDir) == 1.0f){
            SetQuaternion(Quaternion::Identity);
        }
        else if(Vector3::Dot(Vector3::UnitX, checkpointDir) == -1.0f){
            SetQuaternion(Quaternion(Vector3::UnitZ, Math::Pi));
        }
        else{
            Vector3 axis = Vector3::Cross(Vector3::UnitX, checkpointDir);
            axis *= 1.0f / axis.Length();
            SetQuaternion(Quaternion(axis, angle));
        }
    }
    
    SetPosition(mGame->GetRenderer()->Unproject(Vector3(0.0f, 250.0f, 0.1f)));
}
