//
//  HeightMap.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/11/6.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef HeightMap_hpp
#define HeightMap_hpp

#include <stdio.h>
#include <vector>
#include "Math.h"

class HeightMap{
public:
    HeightMap();
    Vector3 CellToWorld(int row, int col);
    Vector2 WorldToCell(float x, float y);
    bool IsOnTrack(float x, float y);
    float GetHeight(float x, float y);
    
    std::vector<std::vector<int>> heightMap;
    
private:
    bool IsCellOnTrack(int row, int col);
    float GetHeightFromCell(int row, int col);
    
    const float CELL_SIZE = 40.55f;
    const float GRID_TOP = 1280.0f;
    const float GRID_LEFT = -1641.0f;
    
};

#endif /* HeightMap_hpp */
