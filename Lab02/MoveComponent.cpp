#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner, 50)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
    mOwner->SetRotation(mOwner->GetRotation() + mAngularSpeed * deltaTime);
    mOwner->SetPosition(mOwner->GetPosition() + mOwner->GetForward() * deltaTime * mForwardSpeed);
}
