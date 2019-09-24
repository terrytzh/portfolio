#include "CollisionComponent.h"
#include "Actor.h"
#include "SDL/SDL.h"
#include <algorithm>
#include <vector>

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	if(GetMax().x < other->GetMin().x)
        return false;
    else if(GetMin().x > other->GetMax().x)
        return false;
    else if(GetMax().y < other->GetMin().y)
        return false;
    else if(GetMin().y > other->GetMax().y)
        return false;
    else{
        return true;
    }
}

Vector2 CollisionComponent::GetMin() const
{
    float minx = mOwner->GetPosition().x - (mWidth * mOwner->GetScale())/2.0f;
    float miny = mOwner->GetPosition().y - (mHeight * mOwner->GetScale())/2.0f;
	return Vector2(minx,miny);
}

Vector2 CollisionComponent::GetMax() const
{
    float maxx = mOwner->GetPosition().x + (mWidth * mOwner->GetScale())/2.0f;
    float maxy = mOwner->GetPosition().y + (mHeight * mOwner->GetScale())/2.0f;
    return Vector2(maxx,maxy);
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector2& offset)
{
	if(!Intersect(other))
        return CollSide::None;
    else{
        float dx1,dx2,dy1,dy2;
        dx1 = Math::Abs(other->GetMin().x - GetMax().x); //Left
        dx2 = Math::Abs(other->GetMax().x - GetMin().x); //Right
        dy1 = Math::Abs(other->GetMin().y - GetMax().y); //Up
        dy2 = Math::Abs(other->GetMax().y - GetMin().y); //Down
        
        std::vector<float> temp;
        temp.push_back(dx1);
        temp.push_back(dx2);
        temp.push_back(dy1);
        temp.push_back(dy2);
        std::sort(temp.begin(), temp.end(), [](float a, float b){
            return a < b;
        });
        
        if(temp[0] == dx1){
            offset.x = dx1;
            return CollSide::Left;
        }
        else if(temp[0] == dx2){
            offset.x = -dx2;
            return CollSide::Right;
        }
        else if(temp[0] == dy1){
            offset.y = dy1;
            return CollSide::Top;
        }
        else{
            offset.y = -dy2;
            return CollSide::Bottom;
        }
    }
}
