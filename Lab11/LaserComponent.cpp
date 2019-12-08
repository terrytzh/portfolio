//
//  LaserComponent.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/2.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "LaserComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Block.h"
#include "Mesh.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Renderer.h"
#include "Game.h"

LaserComponent::LaserComponent(class Actor* owner) : MeshComponent(owner, true){
    SetMesh(owner->GetGame()->GetRenderer()->GetMesh("Assets/Laser.gpmesh"));
}

void LaserComponent::Draw(class Shader* shader){
    if (mMesh)
    {
        for(LineSegment ls : lines){
            // Set the world transform
            shader->SetMatrixUniform("uWorldTransform",
                                     GetWorldTransformFromLine(ls));
            // Set the active texture
            Texture* t = mMesh->GetTexture(mTextureIndex);
            if (t)
            {
                t->SetActive();
            }
            // Set the mesh's vertex array as active
            VertexArray* va = mMesh->GetVertexArray();
            va->SetActive();
            // Draw
            glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
        }
    }
}

void LaserComponent::Update(float deltaTime){
    lines.clear();
    LineSegment ls;
    Vector3 forward = mOwner->GetWorldForward();
    ls.mStart = mOwner->GetWorldPosition();
    ls.mEnd = mOwner->GetWorldPosition() + forward * LASER_LENGTH;
    
    CastInfo outinfo;
    Actor* ignoreActor = mOwner->mParent;
    bool lineReflected = false;
    if(SegmentCast(mOwner->GetGame()->GetPlayer(), ls, outinfo)){
        ls.mEnd = outinfo.mPoint;
        lines.push_back(ls);
    }
    else{
        do {
            if(SegmentCast(mOwner->GetGame()->GetObjects(), ls, outinfo, ignoreActor)){
                ls.mEnd = outinfo.mPoint;
                lines.push_back(ls);
                if(static_cast<Block*>(outinfo.mActor)->GetIsMirror()){
                    lineReflected = true;
                    ls = LineSegment();
                    ls.mStart = outinfo.mPoint;
                    forward = Vector3::Reflect(forward, outinfo.mNormal);
                    ls.mEnd = ls.mStart + forward * LASER_LENGTH;
                    ignoreActor = outinfo.mActor;
                }
                else{
                    lineReflected = false;
                }
            }
            else{
                lineReflected = false;
                if(outinfo.mActor != mOwner->mParent)
                    lines.push_back(ls);
            }
        } while (lineReflected);
        
    }
    
}

Matrix4 LaserComponent::GetWorldTransformFromLine(LineSegment ls){
    Matrix4 scaleMatrix = Matrix4::CreateScale(ls.Length(), 1.0, 1.0);
    Quaternion q;
    Vector3 dir = ls.mEnd - ls.mStart;
    dir.Normalize();
    float angle = Math::Acos(Vector3::Dot(Vector3::UnitX, dir));
    if(Vector3::Dot(Vector3::UnitX, dir) == 1.0){
        q = Quaternion::Identity;
    }
    else if(Vector3::Dot(Vector3::UnitX, dir) == -1.0){
        q = Quaternion(Vector3::UnitZ, Math::Pi);
    }
    else{
        Vector3 axis = Vector3::Cross(Vector3::UnitX, dir);
        axis *= 1.0 / axis.Length();
        q = Quaternion(axis, angle);
    }
    
    
    Matrix4 qRotationMatrix = Matrix4::CreateFromQuaternion(q);
    Matrix4 translationMatrix = Matrix4::CreateTranslation((ls.mStart + ls.mEnd) * 0.5f);
    Matrix4 worldTransform = scaleMatrix * qRotationMatrix * translationMatrix;
    return worldTransform;
}
