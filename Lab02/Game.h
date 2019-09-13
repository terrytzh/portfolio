#pragma once
#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

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

protected:
    void ProcessInput();
    void GenerateOutput();
    void UpdateGame();
    void LoadData();
    void UnloadData();
    SDL_Texture* GetTexture(std::string filename);
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<class Actor*> actors;
    std::vector<class SpriteComponent*> sprites;
    std::unordered_map<std::string, SDL_Texture*> texture_map;
    
    bool isRunning;
    
    
    unsigned int pre_time = 0;
    
    
    const int MOVE_IDLE = 0;
    const int MOVE_UP = 1;
    const int MOVE_DOWN = 2;
    int direction = 0;
    
    
    
    const int WALL_THICKNESS = 20;
    const int WINDOW_WIDTH = 1024;
    const int WINDOW_HEIGHT = 768;
    

};




#endif


// TODO
