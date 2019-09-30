#pragma once
#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "Math.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>

class Game{
public:
    Game(){};
    bool Initialize();
    void Shutdown();
    void RunLoop();
    
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    
    void AddBlock(class Block* block);
    void RemoveBlock(class Block* block);
    const std::vector<class Block*> GetBlocks(){return blocks;}
    
    class Player* GetPlayer(){return player;}
    
    void AddEnemy(class Goomba* e);
    void RemoveEnemy(class Goomba* e);
    const std::vector<class Goomba*> GetEnemies(){return enemies;}
    
    const Vector2 GetCamPosition(){return camPosition;}
    void SetCamPosition(Vector2 pos){camPosition = pos;}
    
    int GetBGChannel(){return bgmusic_channel;}
    
    
    SDL_Texture* GetTexture(const std::string filename);
    
    Mix_Chunk* GetSound(const std::string& filename);
    
    constexpr const static float WALL_THICKNESS = 32.0f;
    constexpr const static int WINDOW_WIDTH = 600;
    constexpr const static int WINDOW_HEIGHT = 448;
    

protected:
    void ProcessInput();
    void GenerateOutput();
    void UpdateGame();
    void LoadData();
    void UnloadData();
    
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> texture_map;
    std::unordered_map<std::string, Mix_Chunk*> mix_map;
    
    std::vector<class Actor*> actors;
    std::vector<class SpriteComponent*> sprites;
    std::vector<class Block*> blocks;
    std::vector<class Goomba*> enemies;
    class Player* player;
    Vector2 camPosition;
    
    int bgmusic_channel;
    
    bool isRunning;
    
    
    unsigned int pre_time = 0;
    
    
    const int MOVE_IDLE = 0;
    const int MOVE_UP = 1;
    const int MOVE_DOWN = 2;
    int direction = 0;
    

};




#endif


// TODO
