//
//  SideBlock.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/29.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef SideBlock_hpp
#define SideBlock_hpp

#include <stdio.h>
#include "Actor.h"

class SideBlock : public Actor{
public:
    SideBlock(class Game* g);
    class MeshComponent* mc;
    
protected:
    void OnUpdate(float deltaTime) override;
};

#endif /* SideBlock_hpp */
