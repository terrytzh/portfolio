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
    
protected:
    bool pedalPressed = false;
    MoveState moveState = Idle;
    Vector3 velocity;
    float angularVelocity = 0.0f;
    float accelerateTimer = 0.0f;
    
    float MIN_LINEAR_ACCELERATION = 1000.0f;
    float MAX_LINEAR_ACCELERATION = 2000.0f;
    float ACCELERATION_RAMP_TIME = 3.0f;
    float ANGULER_ACCELERATION = 5.0f * Math::Pi;
    float NORMAL_DRAG_COEFFICIENT = 0.95f;
    float PEDAL_DRAG_COEFFICIENT = 0.975f;
    float ANGULER_DRAG_COEFFICIENT = 0.9f;
};

#endif /* VehicleMove_hpp */
