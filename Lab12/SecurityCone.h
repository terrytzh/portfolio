//
//  SecurityCone.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/8.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef SecurityCone_hpp
#define SecurityCone_hpp

#include <stdio.h>
#include "Actor.h"

class SecurityCone : public Actor{
public:
    SecurityCone(class Game* g, Actor* parent);
    class MeshComponent* mc;
    enum CameraState{
        Idle,Aware,Alert
    };
    CameraState GetCameraState() {return mState;}

protected:
    void OnUpdate(float deltaTime) override;
    
    float securityTimer = 0.0f;
    int mDetectedSFX = -1;
    CameraState mState = Idle;
    
    const Vector3 RELATIVE_POS = Vector3(30.0f,0.0f,0.0f);
    const float CONE_SCALE = 3.0f;
    const float AWARE_TIME = 2.0f;
    const float ALERT_TIME = 0.5f;
    const float CONE_HEIGHT = CONE_SCALE * 100.0f;
};

#endif /* SecurityCone_hpp */
