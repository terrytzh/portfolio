#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    for(std::vector<class Component*>::iterator i = mComponents.begin(); i != mComponents.end(); i++)
        delete *i;
    
}

void Actor::Update(float deltaTime)
{
    if(mState == ActorState::Active){
        for(std::vector<Component*>::iterator i = mComponents.begin(); i != mComponents.end(); i++){
            Component* temp = *i;
            temp->Update(deltaTime);
        }
        this->OnUpdate(deltaTime);
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
