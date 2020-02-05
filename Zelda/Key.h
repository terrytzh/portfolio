//
//  Key.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/9.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Key_hpp
#define Key_hpp

#include <stdio.h>
#include "Actor.h"

class Key : public Actor {
public:
    Key(class Game* g);
    class SpriteComponent* sprite;
    class CollisionComponent* cc;
};

#endif /* Key_hpp */
