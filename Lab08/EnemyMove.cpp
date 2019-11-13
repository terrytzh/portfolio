//
//  EnemyMove.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "EnemyMove.h"
#include "Game.h"
#include "Actor.h"
#include "Enemy.h"
#include "CSVHelper.h"
#include "HeightMap.h"
#include <fstream>

EnemyMove::EnemyMove(Enemy* enemy) : VehicleMove(enemy, true){
    mEnemy = enemy;
    std::ifstream ifs("Assets/HeightMap/Path.csv");
    std::string temp;
    std::vector<std::string> waypointData;
    
    while(getline(ifs,temp)){
        if(!temp.empty()){
            waypointData = CSVHelper::Split(temp);
            if(waypointData[0] == "Node"){
                Vector3 waypoint = mOwner->GetGame()->GetHeightMap()->CellToWorld(std::stoi(waypointData[1]), std::stoi(waypointData[2]));
                waypoints.push_back(waypoint);
            }
        }
    }
    
    enemy->SetPosition(waypoints[0]);
    nextWayPointIndex = 1;
}

void EnemyMove::Update(float deltaTime){
    Vector3 v = waypoints[nextWayPointIndex] - mEnemy->GetPosition();
    if(v.Length() < 150.0f){
        nextWayPointIndex++;
        if(nextWayPointIndex >= waypoints.size())
            nextWayPointIndex = 0;
        SetPedal(false);
    }
    else{
        v.Normalize();
        if(Math::Acos(Vector3::Dot(v, mEnemy->GetForward())) < Math::Pi / 8.0f){
            SetPedal(true);
        }
        else{
            SetPedal(false);
        }
        if(Math::Acos(Vector3::Dot(v, mEnemy->GetForward())) > Math::Pi / 16.0f){
            Vector3 crossProduct = Vector3::Cross(mEnemy->GetForward(), v);
            if(crossProduct.z > 0.0f){
                SetMoveState(Right);
            }
            else if(crossProduct.z < 0.0f){
                SetMoveState(Left);
            }
        }
        else{
            SetMoveState(Idle);
        }
    }
    VehicleMove::Update(deltaTime);
}
