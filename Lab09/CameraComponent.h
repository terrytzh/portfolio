//
//  CameraComponent.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef CameraComponent_hpp
#define CameraComponent_hpp

#include <stdio.h>
#include "Component.h"

class CameraComponent : public Component{
public:
    CameraComponent(class Actor* owner);
    void Update(float deltaTime) override;
    void SetPitchSpeed(float speed) {mPitchSpeed = speed;}
    float GetPitchSpeed() {return mPitchSpeed;}
    
protected:
    
    const float HDist = 60.0f;
    const float VDist = 70.0f;
    const float TargetDist = 50.0f;
    float mPitchAngle = 0.0f;
    float mPitchSpeed = 0.0f;
    
};

#endif /* CameraComponent_hpp */
