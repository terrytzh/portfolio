//
//  HeightMap.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "HeightMap.h"
#include "CSVHelper.h"
#include <fstream>
#include <string>


HeightMap::HeightMap(){
    std::ifstream ifs("Assets/HeightMap/HeightMap.csv");
    std::string temp;
    
    while(getline(ifs,temp)){
        if(!temp.empty()){
            std::vector<int> HeightMapRow;
            for(auto s : CSVHelper::Split(temp)){
                HeightMapRow.push_back(std::stoi(s));
            }
            heightMap.push_back(HeightMapRow);
        }
    }
}

bool HeightMap::IsCellOnTrack(int row, int col){
    if(row > 63 || row < 0 || col > 63 || col < 0)
        return false;
    return !(heightMap[row][col] == -1);
}

float HeightMap::GetHeightFromCell(int row, int col){
    return -40.0f + static_cast<float>(heightMap[row][col]) * 5.0f;
}

Vector3 HeightMap::CellToWorld(int row, int col){
    if(IsCellOnTrack(row, col)){
        return Vector3(
        GRID_TOP - static_cast<float>(row) * CELL_SIZE,
        GRID_LEFT + static_cast<float>(col) * CELL_SIZE,
        GetHeightFromCell(row, col)
        );
    }
    else
        return Vector3::Zero;
}

Vector2 HeightMap::WorldToCell(float x, float y){
    int row = static_cast<int>((Math::Abs(x - GRID_TOP) + CELL_SIZE / 2.0f) / CELL_SIZE);
    int col = static_cast<int>((Math::Abs(y - GRID_LEFT) + CELL_SIZE / 2.0f) / CELL_SIZE);
    return Vector2(row, col);
}

bool HeightMap::IsOnTrack(float x, float y){
    Vector2 cellCoor = WorldToCell(x, y);
    return IsCellOnTrack(static_cast<int>(cellCoor.x), static_cast<int>(cellCoor.y));
}

float HeightMap::GetHeight(float x, float y){
    if(IsOnTrack(x, y)){
        Vector2 cellCoor = WorldToCell(x, y);
        return GetHeightFromCell(static_cast<int>(cellCoor.x), static_cast<int>(cellCoor.y));
    }
    else
        return -1000.0f;
}
