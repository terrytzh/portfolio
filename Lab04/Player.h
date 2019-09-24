//
//  Player.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/23.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"


class Player : public Actor {
public:
    Player(class Game* g);
    class SpriteComponent* sprite;
    class CollisionComponent* cc;
    class PlayerMove* pm;
    
    
protected:
    const float PLAYER_WIDTH = 32.0f;
    const float PLAYER_HEIGHT = 32.0f;
    
    
};

#endif /* Player_hpp */
