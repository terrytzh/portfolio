#include "GhostAI.h"
#include "Actor.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "PathNode.h"
#include "AnimatedSprite.h"
#include <SDL/SDL.h>
#include <unordered_map>
#include <algorithm>
#include "Ghost.h"
#include "PacMan.h"
#include "Random.h"

GhostAI::GhostAI(class Actor* owner)
:Component(owner, 50)
{
	mGhost = static_cast<Ghost*>(owner);
}

void GhostAI::Update(float deltaTime)
{
    if(mGhost->GetComponent<CollisionComponent>()->Intersect(mNextNode->GetComponent<CollisionComponent>())){
        mGhost->SetPosition(mNextNode->GetPosition());
        if(mState == State::Dead){
            DeadHelper();
        }
        else if(mState == State::Frightened)
            FrightenedHelper();
        else if(mState == State::Chase)
            ChaseHelper();
        else
            ScatterHelper();
    }
    Vector2 pos = mGhost->GetPosition();
    if(mState == State::Dead)
        pos += direction * GHOST_DEAD_SPEED * deltaTime;
    else if(mState == State::Frightened)
        pos += direction * GHOST_FRIGHTEN_SPEED * deltaTime;
    else
        pos += direction * GHOST_SPEED * deltaTime;
    mGhost->SetPosition(pos);
    
    if(frightenedTimer > 0.0f){
        frightenedTimer -= deltaTime;
        if(frightenedTimer <= 0.0f){
            mState = State::Scatter;
            scatterTimer = GHOST_SCATTER_TIME;
            mPath.clear();
        }
    }
    if(scatterTimer > 0.0f){
        scatterTimer -= deltaTime;
        if(scatterTimer <= 0.0f){
            mState = State::Chase;
            chaseTimer = GHOST_CHASE_TIME;
        }
    }
    if(chaseTimer > 0.0f){
        chaseTimer -= deltaTime;
        if(chaseTimer <= 0.0f){
            mState = State::Scatter;
            scatterTimer = GHOST_SCATTER_TIME;
            mPath.clear();
        }
    }
    
}

void GhostAI::ScatterHelper(){
    if(mPath.empty()){
        SetPathWithFailsafe(mNextNode, mTargetNode);
        
    }
    else{
        if(mNextNode == mGhost->GetGame()->mTunnelLeft){
            mPath.pop_back();
            mNextNode = mPath.back();
            mGhost->SetPosition(mGhost->GetGame()->mTunnelRight->GetPosition());
        }
        else if(mNextNode == mGhost->GetGame()->mTunnelRight){
            mPath.pop_back();
            mNextNode = mPath.back();
            mGhost->SetPosition(mGhost->GetGame()->mTunnelLeft->GetPosition());
        }
        
        mPrevNode = mNextNode;
        mNextNode = mPath.back();
        mPath.pop_back();
        SetDirection();
    }
}

void GhostAI::FrightenedHelper(){
    if(mNextNode == mGhost->GetGame()->mTunnelLeft){
        mGhost->SetPosition(mGhost->GetGame()->mTunnelRight->GetPosition());
        mPrevNode = mGhost->GetGame()->mTunnelRight;
        mNextNode = mGhost->GetGame()->mTunnelRight->mAdjacent[0];
        return;
    }
    else if(mNextNode == mGhost->GetGame()->mTunnelRight){
        mGhost->SetPosition(mGhost->GetGame()->mTunnelLeft->GetPosition());
        mPrevNode = mGhost->GetGame()->mTunnelLeft;
        mNextNode = mGhost->GetGame()->mTunnelLeft->mAdjacent[0];
        return;
    }
    
    int index;
    if(mNextNode->mAdjacent.size()<=1)
        index = 0;
    else{
        index = Random::GetIntRange(0, static_cast<int>(mNextNode->mAdjacent.size())-1);
        while(mNextNode->mAdjacent[index] == mPrevNode)
            index = Random::GetIntRange(0, static_cast<int>(mNextNode->mAdjacent.size())-1);
    }
    
    mPrevNode = mNextNode;
    mNextNode = mNextNode->mAdjacent[index];
    mPath.clear();
    SetDirection();
}

void GhostAI::DeadHelper(){
    if(mNextNode == mTargetNode){
        mState = State::Scatter;
        mGhost->Start();
        return;
    }
    if(mPath.empty()){
        SetPathWithFailsafe(mNextNode, mTargetNode);
        if(mNextNode == mGhost->GetGame()->mTunnelLeft){
            mPath.pop_back();
            mNextNode = mPath.back();
            mGhost->SetPosition(mGhost->GetGame()->mTunnelRight->GetPosition());
            
        }
        else if(mNextNode == mGhost->GetGame()->mTunnelRight){
            mPath.pop_back();
            mNextNode = mPath.back();
            mGhost->SetPosition(mGhost->GetGame()->mTunnelLeft->GetPosition());
        }
    }
    else{
        if(mNextNode == mGhost->GetGame()->mTunnelLeft){
            mPath.pop_back();
            mNextNode = mPath.back();
            mGhost->SetPosition(mGhost->GetGame()->mTunnelRight->GetPosition());
        }
        else if(mNextNode == mGhost->GetGame()->mTunnelRight){
            mPath.pop_back();
            mNextNode = mPath.back();
            mGhost->SetPosition(mGhost->GetGame()->mTunnelLeft->GetPosition());
        }
        
        mPrevNode = mNextNode;
        mNextNode = mPath.back();
        mPath.pop_back();
        SetDirection();
    }
}

void GhostAI::ChaseHelper(){
    if(mNextNode == mGhost->GetGame()->mTunnelLeft){
        mPath.pop_back();
        mPrevNode = mGhost->GetGame()->mTunnelRight;
        if(mNextNode == mTargetNode){
            mNextNode = mGhost->GetGame()->mTunnelRight->mAdjacent[0];
            mTargetNode = mNextNode;
        }
        mGhost->SetPosition(mGhost->GetGame()->mTunnelRight->GetPosition());
        return;
    }
    else if(mNextNode == mGhost->GetGame()->mTunnelRight){
        mPath.pop_back();
        mPrevNode = mGhost->GetGame()->mTunnelLeft;
        if(mNextNode == mTargetNode){
            mNextNode = mGhost->GetGame()->mTunnelLeft->mAdjacent[0];
            mTargetNode = mNextNode;
        }
        mGhost->SetPosition(mGhost->GetGame()->mTunnelLeft->GetPosition());
        return;
    }
    
    switch (mGhost->GetType()) {
        case Ghost::Type::Blinky: {
            SetPathWithFailsafe(mNextNode, mGhost->GetGame()->mPlayer->GetPrevNode());
            break;
        }
            
        case Ghost::Type::Pinky: {
            Vector2 pos = mGhost->GetGame()->mPlayer->GetPointInFrontOf(80.0f);
            PathNode* temp = mGhost->GetGame()->mPathNodes[0];
            float distance = (mGhost->GetGame()->mPathNodes[0]->GetPosition()-pos).Length();
            for(auto n : mGhost->GetGame()->mPathNodes){
                if(n == mPrevNode)
                    continue;
                if((n->GetPosition()-pos).Length() < distance){
                    distance = (n->GetPosition()-pos).Length();
                    temp = n;
                }
            }
            SetPathWithFailsafe(mNextNode, temp);
            break;
        }
        case Ghost::Type::Inky: {
            Vector2 point = mGhost->GetGame()->mPlayer->GetPointInFrontOf(40.0f);
            Vector2 pos = mGhost->GetPosition() + 2*(point - mGhost->GetPosition());
            PathNode* temp = mGhost->GetGame()->mPathNodes[0];
            float distance = (mGhost->GetGame()->mPathNodes[0]->GetPosition()-pos).Length();
            for(auto n : mGhost->GetGame()->mPathNodes){
                if(n == mPrevNode)
                    continue;
                if((n->GetPosition()-pos).Length() < distance){
                    distance = (n->GetPosition()-pos).Length();
                    temp = n;
                }
            }
            SetPathWithFailsafe(mNextNode, temp);
            break;
        }
            
        case Ghost::Type::Clyde: {
            if((mGhost->GetPosition() - mGhost->GetGame()->mPlayer->GetPosition()).Length() > 150.0f){
                SetPathWithFailsafe(mNextNode, mGhost->GetGame()->mPlayer->GetPrevNode());
            }
            else{
                SetPathWithFailsafe(mNextNode, mGhost->GetScatterNode());
            }
            break;
        }
    }
}

void GhostAI::SetDirection(){
    AnimatedSprite* asc = mGhost->GetComponent<AnimatedSprite>();
    if(mNextNode->GetPosition().x > mGhost->GetPosition().x){
        direction = Vector2(1,0);
        if(mState == State::Dead){
            asc->SetAnimation("deadright");
        }
        else if(frightenedTimer > 2.0f){
            asc->SetAnimation("scared0");
        }
        else if(frightenedTimer > 0.0f){
            asc->SetAnimation("scared1");
        }
        else
            asc->SetAnimation("right");
    }
    else if(mNextNode->GetPosition().x < mGhost->GetPosition().x){
        direction = Vector2(-1,0);
        if(mState == State::Dead){
            asc->SetAnimation("deadleft");
        }
        else if(frightenedTimer > 2.0f){
            asc->SetAnimation("scared0");
        }
        else if(frightenedTimer > 0.0f){
            asc->SetAnimation("scared1");
        }
        else
            asc->SetAnimation("left");
    }
    else if(mNextNode->GetPosition().y > mGhost->GetPosition().y){
        direction = Vector2(0,1);
        if(mState == State::Dead){
            asc->SetAnimation("deaddown");
        }
        else if(frightenedTimer > 2.0f){
            asc->SetAnimation("scared0");
        }
        else if(frightenedTimer > 0.0f){
            asc->SetAnimation("scared1");
        }
        else
            asc->SetAnimation("down");
    }
    else if(mNextNode->GetPosition().y < mGhost->GetPosition().y){
        direction = Vector2(0,-1);
        if(mState == State::Dead){
            asc->SetAnimation("deadup");
        }
        else if(frightenedTimer > 2.0f){
            asc->SetAnimation("scared0");
        }
        else if(frightenedTimer > 0.0f){
            asc->SetAnimation("scared1");
        }
        else
            asc->SetAnimation("up");
    }
    return;
}

void GhostAI::Frighten()
{
	// TODO: Implement
    if(mState == State::Dead)
        return;
    frightenedTimer = 7.0f;
    scatterTimer = 0.0f;
    chaseTimer = 0.0f;
    mState = State::Frightened;
    mNextNode = mPrevNode;
    SetDirection();
}

void GhostAI::Start(PathNode* startNode)
{
	// TODO: Implement
    mOwner->SetPosition(startNode->GetPosition());
    mState = State::Scatter;
    scatterTimer = GHOST_SCATTER_TIME;
    mPrevNode = nullptr;
    mNextNode = nullptr;
    mTargetNode = nullptr;
    GetPath(startNode, mGhost->GetScatterNode());
    SetDirection();
}

void GhostAI::Die()
{
	// TODO: Implement
    mState = State::Dead;
    frightenedTimer = 0.0f;
    SetDirection();
    mTargetNode = mGhost->GetGame()->mGhostPen;
}

void GhostAI::SetPathWithFailsafe(PathNode *start, PathNode *destination){
    if(!GetPath(start, destination)){
        PathNode* temp;
        if(mNextNode->mAdjacent[0] == mPrevNode)
            temp = mNextNode->mAdjacent[1];
        else
            temp = mNextNode->mAdjacent[0];
        
        for(auto n : mNextNode->mAdjacent){
            if(n == mPrevNode)
                continue;
            if(GetHeuristic(mTargetNode, n) < GetHeuristic(mTargetNode, temp))
                temp = n;
        }
        mPrevNode = mNextNode;
        mNextNode = temp;
    }
    SetDirection();
}

void GhostAI::DebugDrawPath(SDL_Renderer* render)
{
	// Draw a rectangle at the target node
	if (mTargetNode != nullptr)
	{
		const int SIZE = 16;
		SDL_Rect r;
		r.x = static_cast<int>(mTargetNode->GetPosition().x) - SIZE / 2;
		r.y = static_cast<int>(mTargetNode->GetPosition().y) - SIZE / 2;
		r.w = SIZE;
		r.h = SIZE;
		SDL_RenderDrawRect(render, &r);
	}

	// Line from ghost to next node
	if (mNextNode != nullptr)
	{
		SDL_RenderDrawLine(render,
			static_cast<int>(mOwner->GetPosition().x),
			static_cast<int>(mOwner->GetPosition().y),
			static_cast<int>(mNextNode->GetPosition().x),
			static_cast<int>(mNextNode->GetPosition().y));
	}

	// Exit if no path
	if (mPath.empty())
	{
		return;
	}

	// Line from next node to subsequent on path
	SDL_RenderDrawLine(render,
		static_cast<int>(mNextNode->GetPosition().x),
		static_cast<int>(mNextNode->GetPosition().y),
		static_cast<int>(mPath.back()->GetPosition().x),
		static_cast<int>(mPath.back()->GetPosition().y));

	// Lines for rest of path
	for (size_t i = 0; i < mPath.size() - 1; i++)
	{
		SDL_RenderDrawLine(render,
			static_cast<int>(mPath[i]->GetPosition().x),
			static_cast<int>(mPath[i]->GetPosition().y),
				static_cast<int>(mPath[i + 1]->GetPosition().x),
			static_cast<int>(mPath[i + 1]->GetPosition().y));
	}
}

float GhostAI::GetHeuristic(PathNode* start, PathNode* end){
    if(start->GetType() == PathNode::Type::Tunnel && end->GetType() == PathNode::Type::Tunnel)
        return 0.0f;
    float a = (start->GetPosition()-end->GetPosition()).Length();
    float b = (start->GetPosition()-mOwner->GetGame()->mTunnelLeft->GetPosition()).Length() +
    (mOwner->GetGame()->mTunnelRight->GetPosition()-end->GetPosition()).Length();
    float c = (start->GetPosition()-mOwner->GetGame()->mTunnelRight->GetPosition()).Length() +
    (mOwner->GetGame()->mTunnelLeft->GetPosition()-end->GetPosition()).Length();
    return Math::Min(a, Math::Min(b, c));
}

bool GhostAI::GetPath(PathNode* start, PathNode* destination){
    if(start == destination || ((mPrevNode != NULL) && (mPrevNode == mTargetNode))){
        mTargetNode = destination;
        mPath.clear();
        return false;
    }
    std::vector<PathNode*> openSet, closedSet;
    std::unordered_map<PathNode*, std::vector<float>> nodeValueMap;
    std::unordered_map<PathNode*, PathNode*> nodeParentMap;
    PathNode* currentNode = start;
    nodeValueMap[currentNode] = {0.0f,0.0f,0.0f};
    closedSet.push_back(currentNode);
    do{
        std::vector<float> values = {0.0f,0.0f,0.0f};
        for (auto n : currentNode->mAdjacent){
            if(n == mPrevNode)
                continue;
            if(std::find(closedSet.begin(), closedSet.end(), n) != closedSet.end())
                continue;
            else if(std::find(openSet.begin(), openSet.end(), n) != openSet.end()){
                float new_g = GetHeuristic(currentNode, n) + nodeValueMap[currentNode][1];
                if(nodeValueMap.find(n) != nodeValueMap.end()){
                    if(new_g < nodeValueMap[n][1]){
                        nodeParentMap[n] = currentNode;
                        nodeValueMap[n][1] = new_g;
                        nodeValueMap[n][0] = nodeValueMap[n][1] + nodeValueMap[n][2];
                    }
                }
            }
            else{
                nodeParentMap[n] = currentNode;
                values[2] = GetHeuristic(n, destination);
                values[1] = GetHeuristic(n, nodeParentMap[n]) + nodeValueMap[nodeParentMap[n]][1];
                values[0] = values[2] + values[1];
                nodeValueMap[n] = values;
                openSet.push_back(n);
            }
        }
        
        if(openSet.empty())
            break;
        
        PathNode* lowestF = openSet[0];
        for(auto n : openSet){
            if(nodeValueMap[n][0] < nodeValueMap[lowestF][0])
                lowestF = n;
        }
        currentNode = lowestF;
        
        openSet.erase(std::find(openSet.begin(), openSet.end(), currentNode));
        closedSet.push_back(currentNode);
    }
    while(currentNode != destination);
    
    mTargetNode = destination;
    mPrevNode = start;
    PathNode* temp = destination;
    
    if(nodeParentMap[temp] == start)
        mNextNode = temp;
    else if(nodeParentMap[temp] == NULL)
        return false;
    
    mPath.clear();
    while(nodeParentMap[temp] != start){
        mPath.push_back(temp);
        if(nodeParentMap[nodeParentMap[temp]] == start){
            mNextNode = nodeParentMap[temp];
            break;
        }
        temp = nodeParentMap[temp];
    }
    
    return true;
}

