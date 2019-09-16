//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"

bool Game::Initialize(){
    if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) == 0){
        Random::Init();
        window = SDL_CreateWindow("MAIN_WINDOW", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        IMG_Init(IMG_INIT_PNG);
        isRunning = true;
        LoadData();
        pre_time = SDL_GetTicks();
        return true;
    }
    else
        Shutdown();
        return false;
}

void Game::Shutdown(){
    UnloadData();
    IMG_Quit();
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
    
    //Process Keyboard Input
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
    
    std::vector<Actor*> temp = actors;
    for(std::vector<Actor*>::iterator i = temp.begin(); i != temp.end(); i++)
        (*i)->ProcessInput(state);
    
}

void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    //Draw Wall
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    for(std::vector<SpriteComponent*>::iterator i = sprites.begin(); i != sprites.end(); i++){
        if((*i)->IsVisible())
            (*i)->Draw(renderer);
    }
    
    SDL_RenderPresent(renderer);
}

void Game::UpdateGame(){
    unsigned int temp;
    unsigned int current_time;
    do{
        current_time = SDL_GetTicks();
        temp = current_time - pre_time;
    }
    while(temp < 16);
    pre_time = current_time;
    
    if(temp>33)
        temp = 33;
    
    float delta_time = static_cast<float>(temp) / 1000.0f;
    
    std::vector<Actor*> a = actors;
    for(std::vector<Actor*>::iterator i = a.begin(); i != a.end(); i++)
        (*i)->Update(delta_time);
    std::vector<Actor*> removeList;
    for(std::vector<Actor*>::iterator i = a.begin(); i != a.end(); i++)
        if((*i)->GetState() == ActorState::Destroy)
            removeList.push_back(*i);
    for(std::vector<Actor*>::iterator i = removeList.begin(); i != removeList.end(); i++)
        delete *i;
    
}

void Game::AddActor(class Actor* actor){
    actors.push_back(actor);
}

void Game::RemoveActor(class Actor *actor){
    std::vector<class Actor*>::iterator i = std::find(actors.begin(), actors.end(), actor);
    if(i!=actors.end())
        actors.erase(i);
}

void Game::AddSprite(class SpriteComponent* sprite){
    sprites.push_back(sprite);
    std::sort(sprites.begin(), sprites.end(), [](SpriteComponent* a, SpriteComponent* b){
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveSprite(class SpriteComponent* sprite){
    std::vector<SpriteComponent*>::iterator temp = std::find(sprites.begin(), sprites.end(), sprite);
    if(temp != sprites.end())
        sprites.erase(temp);
}

void Game::AddAsteroid(class Asteroid *as){
    asteroids.push_back(as);
}

void Game::RemoveAsteroid(class Asteroid *as){
    std::vector<class Asteroid*>::iterator i = std::find(asteroids.begin(), asteroids.end(), as);
    if(i!=asteroids.end())
        asteroids.erase(i);
}

void Game::LoadData(){
    // Background
    Actor* stars = new Actor(this);
    stars->SetPosition(Vector2(512,384));
    SpriteComponent* s4 = new SpriteComponent(stars,0);
    s4->SetTexture(GetTexture("Assets/Stars.png"));
    
    Ship* s = new Ship(this);
    s->SetPosition(Vector2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
    s->move->SetAngularSpeed(0);
    s->move->SetForwardSpeed(100);
    
    Asteroid* a;
    for(int i = 0; i < 10; i++){
        a = new Asteroid(this);
    }
}

void Game::UnloadData(){
    while(!actors.empty())
        delete actors.back();
    for(std::unordered_map<std::string, SDL_Texture*>::iterator i = texture_map.begin(); i != texture_map.end(); i++)
        SDL_DestroyTexture((*i).second);
    texture_map.clear();
}

SDL_Texture* Game::GetTexture(std::string filename){
    if(texture_map.find(filename) == texture_map.end()){
        SDL_Surface* sur  = IMG_Load(filename.c_str());
        if(sur == nullptr){
            SDL_Log("[ERROR] Failed to load %s", filename.c_str());
            return nullptr;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, sur);
        SDL_FreeSurface(sur);
        texture_map.insert(std::pair<std::string, SDL_Texture*>(filename, texture));
        return texture;
    }
    else{
        return texture_map[filename];
    }
}

// TODO
