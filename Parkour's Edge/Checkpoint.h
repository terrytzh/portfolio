//
//  Checkpoint.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/7.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Checkpoint_hpp
#define Checkpoint_hpp

#include <stdio.h>
#include <string>
#include "Actor.h"

class Checkpoint : public Actor{
public:
    Checkpoint(class Game* g, Actor* parent);
    class MeshComponent* mc;
    class CollisionComponent* cc;
    void SetIsActivated(bool b) {isActivated = b;}
    void SetLevelString(std::string s) {mLevelString = s;}
    void SetTextString(std::string s) {mText = s;}
    std::string GetTextString() {return mText;}
    
protected:
    void OnUpdate(float deltaTime) override;
    
    bool isActivated = false;
    std::string mLevelString;
    std::string mText;
};

#endif /* Checkpoint_hpp */
