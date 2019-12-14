//
//  HUD.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/10.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "HUD.h"
#include "Game.h"
#include "Actor.h"
#include "Font.h"
#include "Texture.h"
#include "Checkpoint.h"
#include "Renderer.h"
#include "Player.h"
#include "SecurityCamera.h"

HUD::HUD(Actor* owner) : UIComponent(owner){
    mFont = new Font();
    mFont->Load("Assets/Inconsolata-Regular.ttf");
    mTimerText = mFont->RenderText("00:00.00");
    mCoinCountText = mFont->RenderText("0/55");
    mCheckpointText = mFont->RenderText(" ");
    mRadar = owner->GetGame()->GetRenderer()->GetTexture("Assets/Radar.png");
    mRadarArrow = owner->GetGame()->GetRenderer()->GetTexture("Assets/RadarArrow.png");
    mBlip = owner->GetGame()->GetRenderer()->GetTexture("Assets/Blip.png");
}

HUD::~HUD(){
    mFont->Unload();
    delete mFont;
}

void HUD::Draw(class Shader *shader){
    DrawTexture(shader, mTimerText, TIMER_POSITION);
    DrawTexture(shader, mCoinCountText, COINCOUNT_POSITION);
    DrawTexture(shader, mCheckpointText, Vector2::Zero);
    
    DrawTexture(shader, mRadar, RADAR_POSITION);
    DrawTexture(shader, mRadarArrow, RADAR_POSITION);
    for(Blip b : mBlips){
        DrawTexture(shader, mBlip, b.mPos, 1.0f, b.mAngle);
    }
}

void HUD::UpdateBlips(){
    mBlips.clear();
    Vector2 playerForward2D = Vector2(mOwner->GetGame()->GetPlayer()->GetForward().x, mOwner->GetGame()->GetPlayer()->GetForward().y);
    float angle = Math::Atan2(playerForward2D.y, playerForward2D.x);
    Matrix3 rotateMatrix = Matrix3::CreateRotation(angle);
    
    for(SecurityCamera* sc : mOwner->GetGame()->GetSecurityCameras()){
        Vector2 player2D = Vector2(mOwner->GetGame()->GetPlayer()->GetPosition().y, mOwner->GetGame()->GetPlayer()->GetPosition().x);
        Vector2 sc2D = Vector2(sc->GetPosition().y, sc->GetPosition().x);
        Vector2 scDir = sc2D - player2D;
        if(scDir.Length() < RADAR_RANGE){
            scDir *= RADAR_RADIUS / RADAR_RANGE;
            Vector2 scRadarPos = Vector2::Transform(scDir, rotateMatrix);
            scRadarPos += RADAR_POSITION;
            Vector2 scForward2D = Vector2(sc->GetQuaternionForward().y, sc->GetQuaternionForward().x);
            scForward2D.Normalize();
            Vector2 scForward = Vector2::Transform(scForward2D, rotateMatrix);
            float scForwardAngle = Math::Atan2(scForward.y, scForward.x);
            Blip b;
            b.mPos = scRadarPos;
            b.mAngle = scForwardAngle;
            mBlips.push_back(b);
        }
    }
}

void HUD::Update(float deltaTime){
    mOwner->GetGame()->GetTime() += deltaTime;
    if(mOwner->GetGame()->GetCheckpointTimer() < CHECKPOINT_TEXT_TIME)
        mOwner->GetGame()->GetCheckpointTimer() += deltaTime;
    mTimerText->Unload();
    delete mTimerText;
    
    mCoinCountText->Unload();
    delete mCoinCountText;
    
    mCheckpointText->Unload();
    delete mCheckpointText;
    
    int min = (int)(mOwner->GetGame()->GetTime() / 60.0f);
    int sec = (int)(mOwner->GetGame()->GetTime()) % 60;
    int msec = (int)(mOwner->GetGame()->GetTime() * 100.0f) % 100;
    char buffer[9];
    snprintf(buffer, 9, "%02d:%02d:%02d", min, sec, msec);
    std::string output = buffer;
    mTimerText = mFont->RenderText(output);
    
    std::ostringstream ss;
    ss << mOwner->GetGame()->GetCoinCount() << "/55";
    mCoinCountText = mFont->RenderText(ss.str());
    
    if(!mOwner->GetGame()->GetCheckpoints().empty() && mOwner->GetGame()->GetCheckpointTimer() < CHECKPOINT_TEXT_TIME){
        mCheckpointText = mFont->RenderText(mOwner->GetGame()->GetCurrCheckpointText());
    }
    else{
        mCheckpointText = mFont->RenderText(" ");
    }
    
    UpdateBlips();
}
