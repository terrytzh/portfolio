#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game, Actor* parent)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector3::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
    ,mParent(parent)
{
    if(parent == NULL)
        mGame->AddActor(this);
    else
        mParent->AddChild(this);
}

Actor::~Actor()
{
    while(!mChildren.empty()){
        delete mChildren.back();
    }
    
    if(mParent == NULL)
        mGame->RemoveActor(this);
    else
        mParent->RemoveChild(this);
    for(std::vector<class Component*>::iterator i = mComponents.begin(); i != mComponents.end(); i++)
        delete *i;
    
}

void Actor::Update(float deltaTime)
{
    CalcWorldTransform();
    if(mState == ActorState::Active){
        for(std::vector<Component*>::iterator i = mComponents.begin(); i != mComponents.end(); i++){
            Component* temp = *i;
            temp->Update(deltaTime);
        }
        this->OnUpdate(deltaTime);
    }
    
    CalcWorldTransform();
    for(Actor* child : mChildren){
        child->Update(deltaTime);
    }
}

void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
    if(mState == ActorState::Active){
        for(std::vector<Component*>::iterator i = mComponents.begin(); i != mComponents.end(); i++){
            Component* temp = *i;
            temp->ProcessInput(keyState);
        }
        this->OnProcessInput(keyState);
    }
}

void Actor::OnProcessInput(const Uint8* keyState)
{
}

void Actor::AddComponent(Component* c)
{
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}

void Actor::CalcWorldTransform(){
    Matrix4 scaleMatrix = Matrix4::CreateScale(mScale);
    Matrix4 positionMatrix = Matrix4::CreateTranslation(mPosition);
    Matrix4 rotationMatrix = Matrix4::CreateRotationZ(mRotation);
    Matrix4 qRotationMatrix = Matrix4::CreateFromQuaternion(GetQuaternion());
    mWorldTransform = scaleMatrix * rotationMatrix * qRotationMatrix * positionMatrix;
    
    if(mParent != NULL){
        if(mInheritScale){
            mWorldTransform *= mParent->GetWorldTransform();
        }
        else{
            mWorldTransform *= mParent->GetWorldRotTrans();
        }
    }
}

Matrix4 Actor::GetWorldRotTrans(){
    Matrix4 positionMatrix = Matrix4::CreateTranslation(mPosition);
    Matrix4 rotationMatrix = Matrix4::CreateRotationZ(mRotation);
    Matrix4 qRotationMatrix = Matrix4::CreateFromQuaternion(GetQuaternion());
    Matrix4 worldTempMatrix = rotationMatrix * qRotationMatrix * positionMatrix;
    if(mParent != NULL){
        worldTempMatrix *= mParent->GetWorldRotTrans();
    }
    return worldTempMatrix;
}
