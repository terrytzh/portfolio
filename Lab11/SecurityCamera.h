//
//  SecurityCamera.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/8.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef SecurityCamera_hpp
#define SecurityCamera_hpp

#include <stdio.h>
#include "Actor.h"

class SecurityCamera : public Actor{
public:
    SecurityCamera(class Game* g, Actor* parent);
    ~SecurityCamera();
    class MeshComponent* mc;
    class SecurityCone* mCone;
    
    Quaternion GetStartQuat() {return mStartQ;}
    void SetStartQuat(Quaternion q) {mStartQ = q;}
    Quaternion GetEndQuat() {return mEndQ;}
    void SetEndQuat(Quaternion q) {mEndQ = q;}
    
    float GetInterpTime() {return interpTime;}
    void SetInterpTime(float f) {interpTime = f;}
    float GetPausedTime() {return pausedTime;}
    void SetPausedTime(float f) {pausedTime = f;}
    
    int GetMotorSFX(){return mMotorSFX;}
    
    enum RotateState{
        Paused,Forward,Backward
    };
    
protected:
    void OnUpdate(float deltaTime) override;
    
    Quaternion mStartQ;
    Quaternion mEndQ;
    float interpTime = 2.0f;
    float pausedTime = 1.0f;
    float moveTimer = 0.0f;
    float pauseTimer = 0.0f;
    RotateState rState = Forward;
    bool isDetecting = false;
    
    const float CAMERA_SOUND_DISTANCE = 1500.0f;
    
    int mMotorSFX = -1;
};

#endif /* SecurityCamera_hpp */
