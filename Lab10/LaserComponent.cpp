//
//  LaserComponent.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/2.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "LaserComponent.h"
#include "Actor.h"
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
        // Set the world transform
        shader->SetMatrixUniform("uWorldTransform",
                                 mOwner->GetWorldTransform());
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

void LaserComponent::Update(float deltaTime){
    ls.mStart = mOwner->GetPosition();
    ls.mEnd = mOwner->GetPosition() + mOwner->GetForward() * 500.0f;
}

Matrix4 LaserComponent::GetWorldTransformFromLine(LineSegment ls){
    Matrix4 WorldTransform = 
}
