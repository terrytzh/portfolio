#pragma once
#include "MoveComponent.h"
#include "Math.h"

class PacManMove : public MoveComponent
{
public:
	PacManMove(class Actor* owner);
	void Update(float deltaTime) override;
	void ProcessInput(const Uint8* keyState) override;
	
	class PathNode* GetPrevNode() const { return mPrevNode; }
	
	Vector2 GetFacingDir() const { return mFacingDir; }
	
	void StartRespawn(bool isGameIntro = false);
	
	void UpdateSounds(float deltaTime);
private:
	void HandleNodeIntersect(class PathNode* p);
	void UpdateRespawn(float deltaTime);
	
	const float MAX_SPEED = 100.0f;
	const float RESPAWN_TIME = 1.1f;
	// TODO: When you complete parts 1-3, change the
	// INTRO_TIME constant to 4.0f
	const float INTRO_TIME = 0.1f;
	const float CHOMP_GRACE_TIME = 0.1f;
	
	Vector2 mMoveDir = Vector2::Zero;
	Vector2 mFacingDir = Vector2::UnitX;
	Vector2 mInput = Vector2::Zero;
	
	float mRespawnTimer = 0.0f;
	
	class PathNode* mPrevNode;
	
	int mChompSound = -1;
	int mSirenSound = -1;
	int mSirenFrightSound = -1;
	float mChompSoundTimer = 0.0f;
};
