//
//  EnemyMove.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef EnemyMove_hpp
#define EnemyMove_hpp

#include <stdio.h>
#include "VehicleMove.h"
#include <vector>

class EnemyMove : public VehicleMove{
public:
    EnemyMove(class Enemy* enemy);
    void Update(float deltaTime) override;
    
protected:
    class Enemy* mEnemy;
    std::vector<Vector3> waypoints;
    int nextWayPointIndex;
};
#endif /* EnemyMove_hpp */
