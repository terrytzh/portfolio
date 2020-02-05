//
//  TiledBGComponent.cpp
//  Game-mac
//
//  Created by Terry Tang on 2019/10/1.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include <fstream>
#include "TiledBGComponent.h"
#include "Actor.h"
#include "Game.h"
#include "CSVHelper.h"

TiledBGComponent::TiledBGComponent(class Actor* owner, int drawOrder) : SpriteComponent(owner, drawOrder){
    
}

void TiledBGComponent::Draw(SDL_Renderer *renderer){
    if (mTexture)
    {
        SDL_Rect r;
        r.w = mTileWidth;
        r.h = mTileHeight;
        
        
        //Read CSV File
        int row;
        int col;
        int csvCode;
        SDL_Rect origin;
        origin.w = mTileWidth;
        origin.h = mTileHeight;
        for(int i = 0; i < static_cast<int>(CSVData.size()); i++){
            for(int k = 0; k < static_cast<int>(CSVData[i].size()); k++){
                csvCode = CSVData[i][k];
                if(csvCode == -1)
                    continue;
                
                row = csvCode / 13;
                col = csvCode % 13;
                
                origin.x = col * mTileWidth;
                origin.y = row * mTileHeight;
                
                // Center the rectangle around the position of the owner
                r.x = k * mTileWidth;
                r.y = i * mTileHeight;
                
                
                //Adjust position according to cam position
                r.x -= static_cast<int>(mOwner->GetGame()->GetCamPosition().x);
                r.y -= static_cast<int>(mOwner->GetGame()->GetCamPosition().y);
                
                // Draw (have to convert angle from radians to degrees, and clockwise to counter)
                SDL_RenderCopyEx(renderer,
                                 mTexture,
                                 &origin,
                                 &r,
                                 0.0,
                                 nullptr,
                                 SDL_FLIP_NONE);
            
            }
        }
    }
        
}

void TiledBGComponent::LoadTileCSV(const std::string& fileName, int tileWidth, int tileHeight){
    mTileWidth = tileWidth;
    mTileHeight = tileHeight;
    
    std::ifstream ifs(fileName);
    std::string temp;
    std::vector<int> CSVTarget;
    while(getline(ifs,temp)){
        if(!temp.empty()){
            for(auto s : CSVHelper::Split(temp)){
                CSVTarget.push_back(std::stoi(s));
            }
            CSVData.push_back(CSVTarget);
            CSVTarget.clear();
        }
    }
}
