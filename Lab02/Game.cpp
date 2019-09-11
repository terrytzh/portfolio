//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"

bool Game::Initialize(){
    if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) == 0){
        window = SDL_CreateWindow("PONG", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
    
}

// TODO
