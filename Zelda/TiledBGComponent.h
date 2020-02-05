//
//  TiledBGComponent.hpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/1.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#ifndef TiledBGComponent_hpp
#define TiledBGComponent_hpp

#include <stdio.h>
#include <vector>
#include "SpriteComponent.h"

class TiledBGComponent : public SpriteComponent{
public:
    TiledBGComponent(class Actor* owner, int drawOrder = 50);
    void Draw(SDL_Renderer* renderer) override;
    
    void LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight);
    
protected:
    int mTileWidth;
    int mTileHeight;
    std::vector<std::vector<int>> CSVData;
};

#endif /* TiledBGComponent_hpp */
