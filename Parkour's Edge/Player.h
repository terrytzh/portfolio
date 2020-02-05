//
//  Player.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Actor.h"
#include <SDL/SDL_stdinc.h>

class Player : public Actor{
public:
    Player(class Game* g, Actor* parent);
    class CollisionComponent* cc;
    class PlayerMove* pm;
    class CameraComponent* camc;
    class HUD* hud;
    void SetRespawnPos(Vector3 pos) {mRespawnPosition = pos;}
    Vector3 GetRespawnPos() {return mRespawnPosition;}
protected:
    Vector3 mRespawnPosition;
};

#endif /* Player_hpp */
