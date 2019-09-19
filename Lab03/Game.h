#pragma once
#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
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
    std::vector<class Block*> GetBlocks(){return blocks;}
    
    class Paddle* GetPaddle(){return paddle;}
    
    SDL_Texture* GetTexture(std::string filename);

    
    constexpr const static float WALL_THICKNESS = 32.0f;
    constexpr const static float WINDOW_WIDTH = 1024.0f;
    constexpr const static float WINDOW_HEIGHT = 768.0f;
    

protected:
    void ProcessInput();
    void GenerateOutput();
    void UpdateGame();
    void LoadData();
    void UnloadData();
    
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> texture_map;
    
    std::vector<class Actor*> actors;
    std::vector<class SpriteComponent*> sprites;
    std::vector<class Block*> blocks;
    class Paddle* paddle;
    
    bool isRunning;
    
    
    unsigned int pre_time = 0;
    
    
    const int MOVE_IDLE = 0;
    const int MOVE_UP = 1;
    const int MOVE_DOWN = 2;
    int direction = 0;
    

};




#endif


// TODO
