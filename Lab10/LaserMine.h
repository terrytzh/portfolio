//
//  LaserMine.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/12/1.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef LaserMine_hpp
#define LaserMine_hpp

#include <stdio.h>
#include "Actor.h"

class LaserMine : public Actor{
public:
    LaserMine(class Game* g);
    
protected:
    class MeshComponent* mc;
};

#endif /* LaserMine_hpp */
