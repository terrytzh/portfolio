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
    
    // Score
    int bounce_count = 0;
    
    unsigned int pre_time = 0;
    
    
    const int MOVE_IDLE = 0;
    const int MOVE_UP = 1;
    const int MOVE_DOWN = 2;
    int direction = 0;
    
    
    SDL_Point pad_pos = SDL_Point();
    SDL_Point ball_pos = SDL_Point();
    SDL_Point ball_speed = SDL_Point();
    
    const int WALL_THICKNESS = 20;
    const int WINDOW_WIDTH = 1024;
    const int WINDOW_HEIGHT = 768;
    const int PADDLE_HEIGHT = 100;
    const int PADDLE_WIDTH = 20;
    const int PADDLE_SPEED = 500;
    const int BALL_WIDTH = 6;
    
    //Initial Speed
    const int BALL_X_SPEED = 300;
    const int BALL_Y_SPEED = 300;
    
    

};



#endif


// TODO
