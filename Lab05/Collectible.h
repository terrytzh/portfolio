//
//  Collectible.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Collectible_hpp
#define Collectible_hpp

#include <stdio.h>
#include <functional>
#include "Component.h"

class Collectible : public Component{
public:
    Collectible(class Actor* owner);
    void Update(float deltaTime) override;
    
    void SetOnCollect(std::function<void()> func){mOnCollect = func;}
    
protected:
    std::function<void()> mOnCollect;
};

#endif /* Collectible_hpp */
