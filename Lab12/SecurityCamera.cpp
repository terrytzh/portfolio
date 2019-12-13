//
//  SecurityCamera.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/8.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "SecurityCamera.h"
#include "SecurityCone.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Checkpoint.h"
#include "Player.h"

SecurityCamera::SecurityCamera(Game* g, Actor* parent) : Actor(g, parent){
    mc = new MeshComponent(this);
    mc->SetMesh(g->GetRenderer()->GetMesh("Assets/Camera.gpmesh"));
    mCone = new SecurityCone(g, this);
    g->GetSecurityCameras().push_back(this);
}

SecurityCamera::~SecurityCamera(){
    if(mMotorSFX != -1)
        Mix_HaltChannel(mMotorSFX);
    std::vector<SecurityCamera*>::iterator i = std::find(mGame->GetSecurityCameras().begin(), mGame->GetSecurityCameras().end(), this);
    if(i != mGame->GetSecurityCameras().end())
        mGame->GetSecurityCameras().erase(i);
}

void SecurityCamera::OnUpdate(float deltaTime){
    float playerDistance = (mGame->GetPlayer()->GetPosition() - GetPosition()).Length();
    int volume;
    if(playerDistance > CAMERA_SOUND_DISTANCE){
        volume = 0;
    }
    else if(playerDistance > 500.0f){
        volume = (int)((CAMERA_SOUND_DISTANCE - playerDistance)/1000.0f*128.0f);
    }
    else{
        volume = 128;
    }
    
    if(mCone->GetCameraState() == SecurityCone::CameraState::Idle){
        isDetecting = false;
        switch (rState) {
            case Paused:
            {
                if(pauseTimer < 0.0f){
                    if(moveTimer < 0.0f)
                        rState = Forward;
                    else if(moveTimer > interpTime)
                        rState = Backward;
                    mMotorSFX =  Mix_PlayChannel(Mix_GroupAvailable(1),GetGame()->GetSound("Assets/Sounds/CameraMotor.wav"),0);
                }
                else
                    pauseTimer -= deltaTime;
                break;
            }
                
            case Forward:
            {
                if(moveTimer > interpTime){
                    rState = Paused;
                    pauseTimer = pausedTime;
                    SetQuaternion(mEndQ);
                    
                    Mix_HaltChannel(mMotorSFX);
                    mMotorSFX = -1;
                    int stopSFX = Mix_PlayChannel(Mix_GroupAvailable(1),GetGame()->GetSound("Assets/Sounds/CameraMotorStop.wav"),0);
                    Mix_Volume(stopSFX, volume);
                }
                else{
                    if(mMotorSFX == -1)
                        mMotorSFX = Mix_PlayChannel(Mix_GroupAvailable(1),GetGame()->GetSound("Assets/Sounds/CameraMotor.wav"),0);
                    SetQuaternion(Quaternion::Slerp(mStartQ, mEndQ, moveTimer / interpTime));
                    moveTimer += deltaTime;
                }
                break;
            }
                
            case Backward:
            {
                if(moveTimer < 0.0f){
                    rState = Paused;
                    pauseTimer = pausedTime;
                    SetQuaternion(mStartQ);
                    
                    Mix_HaltChannel(mMotorSFX);
                    mMotorSFX = -1;
                    int stopSFX = Mix_PlayChannel(Mix_GroupAvailable(1),GetGame()->GetSound("Assets/Sounds/CameraMotorStop.wav"),0);
                    Mix_Volume(stopSFX, volume);
                }
                else{
                    if(mMotorSFX == -1)
                        mMotorSFX = Mix_PlayChannel(Mix_GroupAvailable(1),GetGame()->GetSound("Assets/Sounds/CameraMotor.wav"),0);
                    SetQuaternion(Quaternion::Slerp(mStartQ, mEndQ, moveTimer / interpTime));
                    moveTimer -= deltaTime;
                }
                break;
            }
        }
    }
    else{
        if(!isDetecting){
            if(rState != Paused){
                int stopSFX = Mix_PlayChannel(Mix_GroupAvailable(1),GetGame()->GetSound("Assets/Sounds/CameraMotorStop.wav"),0);
                Mix_Volume(stopSFX, volume);
            }
            if(mMotorSFX != -1){
                Mix_HaltChannel(mMotorSFX);
                mMotorSFX = -1;
            }
            isDetecting = true;
        }
    }
    
    if(mMotorSFX != -1)
        Mix_Volume(mMotorSFX, volume);
    
}
