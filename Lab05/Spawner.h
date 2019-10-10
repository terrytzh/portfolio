//
//  Spawner.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/9/24.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef Spawner_hpp
#define Spawner_hpp

#include <stdio.h>
#include "Actor.h"

enum class SpawnerType{
    Key,Bat
};

//Just for spawning!
class Spawner : public Actor{
public:
    Spawner(class Game* g, SpawnerType type = SpawnerType::Key);
    
    SpawnerType GetType(){return mType;}
    void SetType(SpawnerType type){mType = type;}
    
    bool GetSpawnedState(){return spawned;}
    void SetSpawnedState(bool s){spawned = s;}
    
protected:
    SpawnerType mType;
    bool spawned;
};

#endif /* Spawner_hpp */
