//
//  VehicleMove.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "VehicleMove.h"
#include "Game.h"
#include "Actor.h"
#include "HeightMap.h"
#include "CSVHelper.h"
#include <fstream>

VehicleMove::VehicleMove(Actor* owner, bool isEnemy) : Component(owner, 50){
    velocity = Vector3::Zero;
    if(isEnemy){
        MAX_LINEAR_ACCELERATION = 2500.0f;
        NORMAL_DRAG_COEFFICIENT = 0.82f;
        ANGULER_DRAG_COEFFICIENT = 0.85f;
        ACCELERATION_RAMP_TIME = 2.0f;
        ANGULER_ACCELERATION = 10.0f * Math::Pi;
        CHECKPOINT_EXTENDTION = 100.0f;
    }
    
    std::ifstream ifs("Assets/HeightMap/Checkpoints.csv");
    std::string temp;
    std::vector<std::string> checkpointString;
    
    while(getline(ifs,temp)){
        if(!temp.empty()){
            checkpointString = CSVHelper::Split(temp);
            if(checkpointString[0] == "Type")
                continue;
            std::vector<int> cellData;
            for(auto s : checkpointString){
                if(s != "Checkpoint")
                    cellData.push_back(std::stoi(s));
            }
            Vector3 minCellCoor = mOwner->GetGame()->GetHeightMap()->CellToWorld(cellData[0], cellData[2]);
            Vector3 maxCellCoor = mOwner->GetGame()->GetHeightMap()->CellToWorld(cellData[1], cellData[3]);
            std::vector<float> checkpointData = {minCellCoor.x, maxCellCoor.x, minCellCoor.y, maxCellCoor.y};
            checkpoints.push_back(checkpointData);
            checkpointString.clear();
        }
    }
}

void VehicleMove::Update(float deltaTime){
    Vector3 pos = mOwner->GetPosition();
    //For checkpoint detecting
    if(pedalPressed){
        accelerateTimer += deltaTime;
        float lerpCoefficient = accelerateTimer / ACCELERATION_RAMP_TIME;
        if(lerpCoefficient > 1.0f)
            lerpCoefficient = 1.0f;
        float acceleration = Math::Lerp(MIN_LINEAR_ACCELERATION, MAX_LINEAR_ACCELERATION, lerpCoefficient);
        velocity += mOwner->GetForward() * acceleration * deltaTime;
        pos += velocity * deltaTime;
        velocity *= PEDAL_DRAG_COEFFICIENT;
    }
    else{
        accelerateTimer = 0.0f;
        pos += velocity * deltaTime;
        velocity *= NORMAL_DRAG_COEFFICIENT;
    }
    
    if(mOwner->GetGame()->GetHeightMap()->IsOnTrack(pos.x, pos.y)){
        float height = mOwner->GetGame()->GetHeightMap()->GetHeight(pos.x, pos.y);
        pos.z = Math::Lerp(pos.z, height, 0.1f);
    }
    mOwner->SetPosition(pos);
    
    switch (moveState) {
        case Left:{
            angularVelocity += ANGULER_ACCELERATION * -1.0f * deltaTime;
            break;
            }
            
        case Right:{
            angularVelocity += ANGULER_ACCELERATION * 1.0f * deltaTime;
            break;
        }
            
        default:
            break;
    }
    
    float angle = mOwner->GetRotation();
    angle += angularVelocity * deltaTime;
    mOwner->SetRotation(angle);
    angularVelocity *= ANGULER_DRAG_COEFFICIENT;
    
    int expectedIndex = lastCheckpoint + 1;
    if(expectedIndex >= checkpoints.size())
        expectedIndex = 0;
    
    if(checkpoints[expectedIndex][0] == checkpoints[expectedIndex][1]){
        if(pos.y > checkpoints[expectedIndex][2] - CHECKPOINT_EXTENDTION
           && pos.y < checkpoints[expectedIndex][3] + CHECKPOINT_EXTENDTION
           && Math::Abs(pos.x - checkpoints[expectedIndex][0]) < 20.0f
           ){
            //Passed checkpoint
            lastCheckpoint++;
            if(lastCheckpoint == 0){
                currentLap++;
                OnLapChange(currentLap);
            }
            else if(lastCheckpoint >= checkpoints.size()){
                lastCheckpoint = 0;
                currentLap++;
                OnLapChange(currentLap);
            }
        }
    }
    else if(checkpoints[expectedIndex][2] == checkpoints[expectedIndex][3]){
        if(pos.x < checkpoints[expectedIndex][0] + CHECKPOINT_EXTENDTION
           && pos.x > checkpoints[expectedIndex][1] - CHECKPOINT_EXTENDTION
           && Math::Abs(pos.y - checkpoints[expectedIndex][2]) < 20.0f
           ){
            //Passed checkpoint
            lastCheckpoint++;
            if(lastCheckpoint >= checkpoints.size()){
                lastCheckpoint = 0;
                currentLap++;
                OnLapChange(currentLap);
            }
        }
    }
}

float VehicleMove::GetDistanceFromNextCheckpoint(){
    int expectedIndex = lastCheckpoint + 1;
    if(expectedIndex >= checkpoints.size())
        expectedIndex = 0;
    return (mOwner->GetPosition() - Vector3((checkpoints[expectedIndex][0]+checkpoints[expectedIndex][1])/2.0f,
                                    (checkpoints[expectedIndex][2]+checkpoints[expectedIndex][3])/2.0f,
                                            0.0f)).Length();
}
