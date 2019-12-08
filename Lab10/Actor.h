#pragma once
#include <vector>
#include <SDL/SDL_stdinc.h>
#include "Math.h"


enum class ActorState
{
	Active,
	Paused,
	Destroy
};

class Actor
{
public:
	Actor(class Game* game, Actor* parent);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const Uint8* keyState);

	// Getters/setters
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
    Vector3 GetForward() const {
        return Vector3(cos(mRotation), sin(mRotation), 0.0f);
    }
    Vector3 GetQuaternionForward() const {
        Vector3 qForward = Vector3::Transform(Vector3::UnitX, mQuaternion);
        qForward.Normalize();
        return qForward;
    }
    Vector3 GetRight() const {
        return Vector3(cos(mRotation+Math::PiOver2), sin(mRotation+Math::PiOver2), 0.0f);
    }
    const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	
	ActorState GetState() const { return mState; }
	void SetState(ActorState state) { mState = state; }
    
    Quaternion GetQuaternion() const {return mQuaternion;}
    void SetQuaternion(Quaternion q) {mQuaternion = q;}
    
    void AddChild(Actor* child){
        mChildren.push_back(child);
    }
    void RemoveChild(Actor* child){
        std::vector<Actor*>::iterator i = std::find(mChildren.begin(), mChildren.end(), child);
        if(i != mChildren.end()){
            mChildren.erase(i);
        }
    }
    
    void CalcWorldTransform();
    Matrix4 GetWorldRotTrans();
    Vector3 GetWorldPosition(){
        return mWorldTransform.GetTranslation();
    }
    Vector3 GetWorldForward(){
        return mWorldTransform.GetXAxis();
    }

	class Game* GetGame() { return mGame; }
	
	// Adds component to Actor (this is automatically called
	// in the component constructor)
	void AddComponent(class Component* c);
	
	// Returns component of type T, or null if doesn't exist
	template <typename T>
	T* GetComponent() const
	{
		for (auto c : mComponents)
		{
			T* t = dynamic_cast<T*>(c);
			if (t != nullptr)
			{
				return t;
			}
		}
		
		return nullptr;
	}
    
    Actor* mParent;
    std::vector<Actor*> mChildren;
    
protected:
	// Any actor-specific update code (overridable)
	virtual void OnUpdate(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void OnProcessInput(const Uint8* keyState);
    
    
	
	class Game* mGame;
	// Actor's state
	ActorState mState;
    bool mInheritScale = false;

	// Transform
	Vector3 mPosition;
    Matrix4 mWorldTransform;
	float mScale;
	float mRotation;
    
    Quaternion mQuaternion;
	
	// Components
	std::vector<class Component*> mComponents;
};
