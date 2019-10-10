//
//  EnemyComponent.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef EnemyComponent_hpp
#define EnemyComponent_hpp

#include <stdio.h>
#include <string>
#include "Component.h"

class EnemyComponent : public Component{
public:
    EnemyComponent(class Actor* owner);
    ~EnemyComponent();
    
protected:
    std::string currentRoom;
};

#endif /* EnemyComponent_hpp */
