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
        if(mPath.empty()){
            if(!GetPath(mNextNode, mTargetNode)){
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
                SetDirection();
            }
            else{
                SetDirection();
            }

        }
        else{
            if(mNextNode->GetType() == PathNode::Type::Tunnel){
                mPath.pop_back();
                mNextNode = mPath.back();
            }
            
            mPrevNode = mNextNode;
            mNextNode = mPath.back();
            mPath.pop_back();
            SetDirection();
        }
    }
    Vector2 pos = mGhost->GetPosition();
    pos += direction * GHOST_SPEED * deltaTime;
    mGhost->SetPosition(pos);
}

void GhostAI::SetDirection(){
    AnimatedSprite* asc = mGhost->GetComponent<AnimatedSprite>();
    if(mNextNode->GetPosition().x > mGhost->GetPosition().x){
        direction = Vector2(1,0);
        asc->SetAnimation("right");
    }
    else if(mNextNode->GetPosition().x < mGhost->GetPosition().x){
        direction = Vector2(-1,0);
        asc->SetAnimation("left");
    }
    else if(mNextNode->GetPosition().y > mGhost->GetPosition().y){
        direction = Vector2(0,1);
        asc->SetAnimation("down");
    }
    else if(mNextNode->GetPosition().y < mGhost->GetPosition().y){
        direction = Vector2(0,-1);
        asc->SetAnimation("up");
    }
    return;
}

void GhostAI::Frighten()
{
	// TODO: Implement
}

void GhostAI::Start(PathNode* startNode)
{
	// TODO: Implement
    mOwner->SetPosition(startNode->GetPosition());
    mState = State::Scatter;
    mPrevNode = nullptr;
    mNextNode = nullptr;
    mTargetNode = nullptr;
    GetPath(startNode, mGhost->GetScatterNode());
    SetDirection();
}

void GhostAI::Die()
{
	// TODO: Implement
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

