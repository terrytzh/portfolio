#pragma once
#include "Component.h"
#include "Math.h"
#include <vector>

class GhostAI : public Component
{
public:
	// Used to track the four different GhostAI states
	enum State
	{
		Scatter,
		Chase,
		Frightened,
		Dead
	};
	
	GhostAI(class Actor* owner);

	void Update(float deltaTime) override;
	
	// Called when the Ghost starts at the beginning
	// (or when the ghosts should respawn)
	void Start(class PathNode* startNode);
	
	// Get the current state
	State GetState() const { return mState; }
	
	// Called when the ghost should switch to the "Frightened" state
	void Frighten();
	
	// Called when the ghost should switch to the "Dead" state
	void Die();

	//  Helper function to draw GhostAI's current path
	void DebugDrawPath(struct SDL_Renderer* render);
private:
	// Member data for pathfinding

	// TargetNode is our current goal node
	class PathNode* mTargetNode = nullptr;
	// PrevNode is the last node we intersected
	// with prior to the current position
	class PathNode* mPrevNode = nullptr;
	// NextNode is the next node we're trying
	// to get to
	class PathNode* mNextNode = nullptr;

	// This vector always contains the path
	// from "next node" to "target node"
	// (if there is still such a path)
	std::vector<class PathNode*> mPath;

	// Current state of the Ghost AI
	State mState = Scatter;

	// Save the owning actor (cast to a Ghost*)
	class Ghost* mGhost;
    
	// TODO: Add any member data/helper functions here!
    bool GetPath(class PathNode* start, class PathNode* destination);
    float GetHeuristic(class PathNode* start, class PathNode* end);
    void SetDirection();
    void SetPathWithFailsafe(class PathNode* start, class PathNode* destination);
    Vector2 direction;
    

    float frightenedTimer= 0.0f;
    float chaseTimer=0.0f;
    float scatterTimer = 0.0f;
    void FrightenedHelper();
    void ScatterHelper();
    void DeadHelper();
    void ChaseHelper();
    
    const float GHOST_SPEED = 90.0f;
    const float GHOST_FRIGHTEN_SPEED = 65.0f;
    const float GHOST_DEAD_SPEED = 125.0f;
    const float GHOST_CHASE_TIME = 20.0f;
    const float GHOST_SCATTER_TIME = 5.0f;
};
