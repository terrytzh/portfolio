#pragma once
#ifndef GAME_H
#define GAME_H

#include "SDL/SDL.h"

class Game{
public:
    Game(){};
    bool Initialize();
    void Shutdown();
    void RunLoop();

protected:
    void ProcessInput();
    void GenerateOutput();
    void UpdateGame();
    SDL_Window* window;
    SDL_Renderer* renderer;
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
