//
//  VehicleMove.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef VehicleMove_hpp
#define VehicleMove_hpp

#include <stdio.h>
#include <vector>
#include "Component.h"

class VehicleMove : public Component {
public:
    enum MoveState{
        Left,Right,Idle
    };
    
    VehicleMove(class Actor* owner, bool isEnemy = false);
    void Update(float deltaTime) override;
    
    void SetPedal(bool pedal){pedalPressed = pedal;}
    void SetMoveState(MoveState ms){moveState = ms;}
    int GetCurrentLap(){return currentLap;}
    int GetCurrentCheckpoint(){
        return lastCheckpoint;
    }
    float GetDistanceFromNextCheckpoint();
    virtual void OnLapChange(int newLap) { }
    
protected:
    bool pedalPressed = false;
    MoveState moveState = Idle;
    Vector3 velocity;
    std::vector<std::vector<float>> checkpoints;
    float angularVelocity = 0.0f;
    float accelerateTimer = 0.0f;
    int currentLap = 0;
    int lastCheckpoint = -1;
    
    float MIN_LINEAR_ACCELERATION = 1000.0f;
    float MAX_LINEAR_ACCELERATION = 2000.0f;
    float ACCELERATION_RAMP_TIME = 3.0f;
    float ANGULER_ACCELERATION = 8.0f * Math::Pi;
    float NORMAL_DRAG_COEFFICIENT = 0.95f;
    float PEDAL_DRAG_COEFFICIENT = 0.975f;
    float ANGULER_DRAG_COEFFICIENT = 0.88f;
    float CHECKPOINT_EXTENDTION = 20.0f;
};

#endif /* VehicleMove_hpp */
