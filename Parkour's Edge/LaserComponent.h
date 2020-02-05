//
//  LaserComponent.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/2.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef LaserComponent_hpp
#define LaserComponent_hpp

#include <stdio.h>
#include "MeshComponent.h"
#include "SegmentCast.h"

class LaserComponent : public MeshComponent{
public:
    LaserComponent(class Actor* owner);
    void Draw(class Shader* shader) override;
    void Update(float deltaTime) override;
    
    
protected:
    Matrix4 GetWorldTransformFromLine(LineSegment ls);
    
    std::vector<LineSegment> lines;
    const float LASER_LENGTH = 500.0f;
    
};

#endif /* LaserComponent_hpp */
