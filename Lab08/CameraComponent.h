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
    
protected:
    Vector3 CalculateIdealPosition();
    
    const float HDist = 60.0f;
    const float VDist = 70.0f;
    const float TargetDist = 50.0f;
    const float SPRING_CONSTANT = 256.0f;
    
    float dampConstant;
    Vector3 camVelocity;
    Vector3 camPosition;
};

#endif /* CameraComponent_hpp */
