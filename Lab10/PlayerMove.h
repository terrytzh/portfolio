//
//  PlayerMove.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/29.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef PlayerMove_hpp
#define PlayerMove_hpp

#include <stdio.h>
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "Math.h"

class PlayerMove : public MoveComponent{
public:
    enum MoveState{
        OnGround,Jump,Falling
    };
    
    PlayerMove(class Player* owner);
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    void ChangeState(MoveState ms){mCurrentState = ms;}
    
    
    
protected:
    class Player* mPlayer;
    MoveState mCurrentState;
    //float mZSpeed = 0.0f;
    bool SpacebarPressed = false;
    Vector3 mVelocity;
    Vector3 mAcceleration;
    Vector3 mPendingForces;
    float mMass = 1.0f;
    Vector3 mGravity = Vector3(0.0f,0.0f,-980.0f);
    Vector3 mJumpForce = Vector3(0.f,0.f,35000.0f);
    const float MAX_SPEED = 400.0f;
    const float BRAKE_FACTOR = 0.9f;
    const float MOUSE_CONVERSION_FACTOR = 500.0f;
    const float MOVE_FORCE = 700.0f;
    
    //const float GRAVITY_ACCELERATION = -980.0f;
    //const float JUMP_SPEED = 500.0f;
    
    
    void UpdateOnGround(float deltaTime);
    void UpdateJump(float deltaTime);
    void UpdateFalling(float deltaTime);
    void FixXYVelocity();
    
    void PhysicsUpdate(float deltaTime);
    void AddForce(const Vector3& force){
        mPendingForces += force;
    }
    CollSide FixCollision(class CollisionComponent* self, class CollisionComponent* block);
};

#endif /* PlayerMove_hpp */
