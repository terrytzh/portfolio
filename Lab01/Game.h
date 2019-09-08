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
    
    
    SDL_Point pad_pos = SDL_Point();
    SDL_Point ball_pos = SDL_Point();
    
    const int WALL_THICKNESS = 20;
    const int WINDOW_WIDTH = 1024;
    const int WINDOW_HEIGHT = 768;
    const int PADDLE_HEIGHT = 100;
    const int PADDLE_WIDTH = 20;
    const int BALL_WIDTH = 6;
    const int PADDLE_SPEED = 350;
    
    

};


bool Game::Initialize(){
    if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) == 0){
        window = SDL_CreateWindow("PONG", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        pad_pos.x = PADDLE_WIDTH*3/2;
        pad_pos.y = WINDOW_HEIGHT/2;
        
        ball_pos.x = WINDOW_WIDTH/2;
        ball_pos.y = WINDOW_HEIGHT/2;
        pre_time = SDL_GetTicks();
        return true;
    }
    else
        return false;
}

void Game::Shutdown(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::RunLoop(){
    while(isRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}


void Game::ProcessInput(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
                
            default:
                break;
        }
    }
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]){
        isRunning = false;
    }
    else if (state[SDL_SCANCODE_UP]){
        direction = MOVE_UP;
    }
    else if (state[SDL_SCANCODE_DOWN]){
        direction = MOVE_DOWN;
    }
}

void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    
    //Draw Wall
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    SDL_Rect r_up, r_right, r_down;
    r_up.x = 0;
    r_up.y = 0;
    r_up.w = WINDOW_WIDTH;
    r_up.h = WALL_THICKNESS;
    
    r_right.x = WINDOW_WIDTH-WALL_THICKNESS;
    r_right.y = 0;
    r_right.w = WALL_THICKNESS;
    r_right.h = WINDOW_HEIGHT;
    
    r_down.x = 0;
    r_down.y = WINDOW_HEIGHT-WALL_THICKNESS;
    r_down.w = WINDOW_WIDTH;
    r_down.h = WALL_THICKNESS;
    
    SDL_RenderFillRect(renderer, &r_up);
    SDL_RenderFillRect(renderer, &r_right);
    SDL_RenderFillRect(renderer, &r_down);
    
    SDL_Rect r_pad;
    r_pad.x = pad_pos.x - PADDLE_WIDTH/2;
    r_pad.y = pad_pos.y - PADDLE_HEIGHT/2;
    r_pad.w = PADDLE_WIDTH;
    r_pad.h = PADDLE_HEIGHT;
    SDL_RenderFillRect(renderer, &r_pad);
    
    SDL_Rect r_ball;
    r_ball.x = ball_pos.x - BALL_WIDTH/2;
    r_ball.y = ball_pos.y - BALL_WIDTH/2;
    r_ball.w = BALL_WIDTH;
    r_ball.h = BALL_WIDTH;
    SDL_RenderFillRect(renderer, &r_ball);
    
    
    SDL_RenderPresent(renderer);
}

void Game::UpdateGame(){
    unsigned int delta_time;
    unsigned int current_time;
    do{
        current_time = SDL_GetTicks();
        delta_time = current_time - pre_time;
    }
    while(delta_time < 16);
    pre_time = current_time;
    
    if(delta_time>33)
        delta_time = 33;
    
    switch (direction) {
        case 1:
            pad_pos.y -= static_cast<int>(static_cast<float>(delta_time) / 1000 * PADDLE_SPEED);
            break;
        
        case 2:
            pad_pos.y += static_cast<int>(static_cast<float>(delta_time) / 1000 * PADDLE_SPEED);
            
        default:
            break;
    }
    if(pad_pos.y < PADDLE_HEIGHT/2+WALL_THICKNESS)
        pad_pos.y = PADDLE_HEIGHT/2+WALL_THICKNESS;
    else if(pad_pos.y > WINDOW_HEIGHT-WALL_THICKNESS-PADDLE_HEIGHT/2)
        pad_pos.y = WINDOW_HEIGHT-WALL_THICKNESS-PADDLE_HEIGHT/2;
    
    direction = MOVE_IDLE;
    
    //SDL_Log("%i", delta_time);
    
}

#endif


// TODO
