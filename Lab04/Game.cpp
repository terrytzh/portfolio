//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "Player.h"
#include "Goomba.h"
#include "Block.h"
#include "Spawner.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Random.h"

bool Game::Initialize(){
    if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) == 0){
        Random::Init();
        window = SDL_CreateWindow("MAIN_WINDOW", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        IMG_Init(IMG_INIT_PNG);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        isRunning = true;
        LoadData();
        pre_time = SDL_GetTicks();
        return true;
    }
    else
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
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
    
    float delta_time = static_cast<float>(temp) / 1000.0;
    
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

void Game::AddBlock(class Block *block){
    blocks.push_back(block);
}

void Game::RemoveBlock(class Block *block){
    std::vector<Block*>::iterator i = std::find(blocks.begin(), blocks.end(), block);
    if(i!=blocks.end())
        blocks.erase(i);
}

void Game::AddEnemy(class Goomba *e){
    enemies.push_back(e);
}

void Game::RemoveEnemy(class Goomba *e){
    std::vector<Goomba*>::iterator i = std::find(enemies.begin(), enemies.end(), e);
    if(i!=enemies.end())
        enemies.erase(i);
}

void Game::LoadData(){
    Actor* background = new Actor(this);
    background->SetPosition(Vector2(3392,224));
    SpriteComponent* background_texture = new SpriteComponent(background);
    background_texture->SetTexture(GetTexture("Assets/Background.png"));
    bgmusic_channel = Mix_PlayChannel(-1, GetSound("Assets/Sounds/Music.ogg"), -1);
    
    //Load Map
    std::ifstream in("Assets/Level1.txt");
    if(in){
        std::string line;
        Vector2 position(16.0f,16.0f);
        while(getline(in,line)){
            for(auto b : line){
                if(b == 'P'){
                    player = new Player(this);
                    player->SetPosition(position);
                }
                else if(b == 'Y'){
                    Spawner* s = new Spawner(this);
                    s->SetPosition(position);
                }
                else if(b != '.'){
                    Block* block = new Block(this, b);
                    block->SetPosition(position);
                }
                position.x += 32.0f;
            }
            position.y += 32.0f;
            position.x = 16.0f;
        }
    }
}

void Game::UnloadData(){
    while(!actors.empty())
        delete actors.back();
    for(std::unordered_map<std::string, SDL_Texture*>::iterator i = texture_map.begin(); i != texture_map.end(); i++)
        SDL_DestroyTexture((*i).second);
    texture_map.clear();
    for(auto m : mix_map)
        Mix_FreeChunk(m.second);
}

SDL_Texture* Game::GetTexture(const std::string filename){
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

Mix_Chunk* Game::GetSound(const std::string& filename){
    if(mix_map.find(filename) == mix_map.end()){
        Mix_Chunk* mix = Mix_LoadWAV(filename.c_str());
        if(mix == nullptr){
            SDL_Log("[ERROR] Failed to load %s", filename.c_str());
            return nullptr;
        }
        mix_map.insert(std::pair<std::string, Mix_Chunk*>(filename, mix));
        return mix;
    }
    else{
        return mix_map[filename];
    }
}
