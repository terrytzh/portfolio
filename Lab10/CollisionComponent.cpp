#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
,mDepth(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	Vector3 aMin = GetMin();
	Vector3 aMax = GetMax();
	Vector3 bMin = other->GetMin();
	Vector3 bMax = other->GetMax();

	bool no = aMax.x < bMin.x ||
		aMax.y < bMin.y ||
		aMax.z < bMin.z ||
		bMax.x < aMin.x ||
		bMax.y < aMin.y ||
		bMax.z < aMin.z;

	return !no;
}

Vector3 CollisionComponent::GetMin() const
{
	Vector3 v = mOwner->GetPosition();
	v.x -= mDepth * mOwner->GetScale() / 2.0f;
	v.y -= mWidth * mOwner->GetScale() / 2.0f;
	v.z -= mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

Vector3 CollisionComponent::GetMax() const
{
	Vector3 v = mOwner->GetPosition();
	v.x += mDepth * mOwner->GetScale() / 2.0f;
	v.y += mWidth * mOwner->GetScale() / 2.0f;
	v.z += mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

const Vector3& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

CollSide CollisionComponent::GetMinOverlap(
	const CollisionComponent* other, Vector3& offset)
{
    if(!Intersect(other))
        return CollSide::None;
    else{
        float dx1,dx2,dy1,dy2,dz1,dz2;
        dx1 = Math::Abs(other->GetMin().x - GetMax().x);
        dx2 = Math::Abs(other->GetMax().x - GetMin().x);
        dy1 = Math::Abs(other->GetMin().y - GetMax().y);
        dy2 = Math::Abs(other->GetMax().y - GetMin().y);
        dz1 = Math::Abs(other->GetMin().z - GetMax().z);
        dz2 = Math::Abs(other->GetMax().z - GetMin().z);
        
        std::vector<float> temp = {dx1,dx2,dy1,dy2,dz1,dz2};
        std::sort(temp.begin(), temp.end(), [](float a, float b){
            return a < b;
        });
        
        if(temp[0] == dx1){
            offset.x = -dx1;
            return CollSide::Side;
        }
        else if(temp[0] == dx2){
            offset.x = dx2;
            return CollSide::Side;
        }
        else if(temp[0] == dy1){
            offset.y = -dy1;
            return CollSide::Side;
        }
        else if(temp[0] == dy2){
            offset.y = dy2;
            return CollSide::Side;
        }
        else if(temp[0] == dz1){
            offset.z = -dz1;
            return CollSide::Bottom;
        }
        else{
            offset.z = dz2;
            return CollSide::Top;
        }
    }
}

