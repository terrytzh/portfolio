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
#include "Block.h"
#include "Spawner.h"
#include "Collider.h"
#include "Door.h"
#include "SecretBlock.h"
#include "Key.h"
#include "Bat.h"
#include "Skeleton.h"
#include "Boss.h"
#include "Fireball.h"
#include "TriForce.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "TiledBGComponent.h"
#include "CSVHelper.h"
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


void Game::SetCurrentRoom(std::string room){
    SDL_Log("%s Enemy Size: %i", currentRoom.c_str(), enemy_map[currentRoom].size());
    for(auto e : enemy_map[currentRoom]){
        e->SetState(ActorState::Paused);
    }
    
    currentRoom = room;
    
    SDL_Log("%s Enemy Size: %i", currentRoom.c_str(), enemy_map[currentRoom].size());
    for(auto e : enemy_map[currentRoom]){
        e->SetState(ActorState::Active);
    }
    
    SpawnerType type;
    for(auto spawner : spawner_map[currentRoom]){
        if(spawner->GetSpawnedState())
            continue;
        type = spawner->GetType();
        if(type == SpawnerType::Key){
            Key* k = new Key(this);
            k->SetPosition(spawner->GetPosition());
        }
        else if(type == SpawnerType::Bat){
            Bat* b = new Bat(this);
            b->SetPosition(spawner->GetPosition());
        }
        else if(type == SpawnerType::Skeleton){
            Skeleton* s = new Skeleton(this);
            s->SetPosition(spawner->GetPosition());
        }
        else if(type == SpawnerType::Boss){
            Boss* b = new Boss(this);
            b->SetPosition(spawner->GetPosition());
        }
        else if(type == SpawnerType::Triforce){
            TriForce* t = new TriForce(this);
            t->SetPosition(spawner->GetPosition());
        }
    
        spawner->SetSpawnedState(true);
    }
}

void Game::LoadData(){
    bgmusic_channel = Mix_PlayChannel(-1, GetSound("Assets/Sounds/Music.ogg"), -1);
    loadCSVMapFile("Assets/Dungeon/Room1.csv");
    loadCSVMapFile("Assets/Dungeon/Room2.csv");
    loadCSVMapFile("Assets/Dungeon/Room3.csv");
    loadCSVMapFile("Assets/Dungeon/Room4.csv");
    loadCSVMapFile("Assets/Dungeon/Room5.csv");
    loadCSVMapFile("Assets/Dungeon/Room6.csv");
    loadCSVMapFile("Assets/Dungeon/Room7.csv");
    
    SetCurrentRoom("Room1");
    
    Actor* bg = new Actor(this);
    TiledBGComponent* bgComponent = new TiledBGComponent(bg);
    bgComponent->LoadTileCSV("Assets/Dungeon/DungeonMapBG.csv", 32, 32);
    bgComponent->SetTexture(GetTexture("Assets/Dungeon/DungeonTiles.png"));
}

void Game::loadCSVMapFile(std::string fileName){
    std::ifstream ifs(fileName);
    std::string temp;
    std::vector<std::string> CSVTarget;
    
    //For addition to the map
    std::vector<Door*> doors;
    std::vector<Spawner*> spawners;
    std::vector<Actor*> enemies;
    std::string roomName = fileName.substr(fileName.length()-9,5);
    SDL_Log("%s", roomName.c_str());
    
    
    while(getline(ifs,temp)){
        if(!temp.empty()){
            CSVTarget = CSVHelper::Split(temp);
            
            if(CSVTarget[0] == "Player"){
                player = new Player(this);
                player->SetPosition(Vector2(std::stoi(CSVTarget[1]),std::stoi(CSVTarget[2])));
            }
            
            
            else if(CSVTarget[0] == "Collider"){
                Collider* c = new Collider(this);
                float width = std::stof(CSVTarget[3]);
                float height = std::stof(CSVTarget[4]);
                c->SetPosition(Vector2(std::stoi(CSVTarget[1])+width/2.0f,std::stoi(CSVTarget[2])+height/2.0f));
                c->setCollisionComponent(width, height);
                colliders.push_back(c);
            }
            
            
            else if(CSVTarget[0] == "Door"){
                Door* d = new Door(this);
                float width = std::stof(CSVTarget[3]);
                float height = std::stof(CSVTarget[4]);
                d->SetPosition(Vector2(std::stoi(CSVTarget[1])+width/2.0f,std::stoi(CSVTarget[2])+height/2.0f));
                
                if(CSVTarget[6] == "Left"){
                    d->SetDirection(DoorDirection::Left);
                }
                else if(CSVTarget[6] == "Right"){
                    d->SetDirection(DoorDirection::Right);
                }
                else if(CSVTarget[6] == "Up"){
                    d->SetDirection(DoorDirection::Up);
                }
                else if(CSVTarget[6] == "Down"){
                    d->SetDirection(DoorDirection::Down);
                }
                
                if(CSVTarget[7] == "Open"){
                    d->SetState(DoorState::Open);
                }
                else if(CSVTarget[7] == "Closed"){
                    d->SetState(DoorState::Closed);
                }
                else if(CSVTarget[7] == "Locked"){
                    d->SetState(DoorState::Locked);
                }
                d->UpdateComponents();
                d->SetDestination(CSVTarget[5]);
                
                doors.push_back(d);
            }
            
            
            else if(CSVTarget[0] == "SecretBlock"){
                SecretBlock* s = new SecretBlock(this);
                float width = std::stof(CSVTarget[3]);
                float height = std::stof(CSVTarget[4]);
                s->SetPosition(Vector2(std::stoi(CSVTarget[1])+width/2.0f,std::stoi(CSVTarget[2])+height/2.0f));
                if(CSVTarget[6] == "Left"){
                    s->SetDirection(SecretBlockDirection::Left);
                }
                else if(CSVTarget[6] == "Right"){
                    s->SetDirection(SecretBlockDirection::Right);
                }
                else if(CSVTarget[6] == "Up"){
                    s->SetDirection(SecretBlockDirection::Up);
                }
                else if(CSVTarget[6] == "Down"){
                    s->SetDirection(SecretBlockDirection::Down);
                }
                secretBlocks.push_back(s);
            }
            
            
            else if(CSVTarget[0] == "Key"){
                Spawner* spawner = new Spawner(this, SpawnerType::Key);
                float width = std::stof(CSVTarget[3]);
                float height = std::stof(CSVTarget[4]);
                spawner->SetPosition(Vector2(std::stoi(CSVTarget[1])+width/2.0f,std::stoi(CSVTarget[2])+height/2.0f));
                spawners.push_back(spawner);
            }
            
            
            else if(CSVTarget[0] == "Bat"){
                Spawner* spawner = new Spawner(this, SpawnerType::Bat);
                float width = std::stof(CSVTarget[3]);
                float height = std::stof(CSVTarget[4]);
                spawner->SetPosition(Vector2(std::stoi(CSVTarget[1])+width/2.0f,std::stoi(CSVTarget[2])+height/2.0f));
                spawners.push_back(spawner);
            }
            
            
            else if(CSVTarget[0] == "Skeleton"){
                Spawner* spawner = new Spawner(this, SpawnerType::Skeleton);
                float width = std::stof(CSVTarget[3]);
                float height = std::stof(CSVTarget[4]);
                spawner->SetPosition(Vector2(std::stoi(CSVTarget[1])+width/2.0f,std::stoi(CSVTarget[2])+height/2.0f));
                spawners.push_back(spawner);
            }
            
            
            else if(CSVTarget[0] == "Boss"){
                Spawner* spawner = new Spawner(this, SpawnerType::Boss);
                float width = std::stof(CSVTarget[3]);
                float height = std::stof(CSVTarget[4]);
                spawner->SetPosition(Vector2(std::stoi(CSVTarget[1])+width/2.0f,std::stoi(CSVTarget[2])+height/2.0f));
                spawners.push_back(spawner);
            }
            
            
            else if(CSVTarget[0] == "Triforce"){
                Spawner* spawner = new Spawner(this, SpawnerType::Triforce);
                float width = std::stof(CSVTarget[3]);
                float height = std::stof(CSVTarget[4]);
                spawner->SetPosition(Vector2(std::stoi(CSVTarget[1])+width/2.0f,std::stoi(CSVTarget[2])+height/2.0f));
                spawners.push_back(spawner);
            }
        }
    }
    SDL_Log("Room: %s, door: %i", roomName.c_str(), doors.size());
    room_map.insert(std::pair<std::string, std::vector<Door*>>(roomName, doors));
    spawner_map.insert(std::pair<std::string, std::vector<Spawner*>>(roomName, spawners));
    enemy_map.insert(std::pair<std::string, std::vector<Actor*>>(roomName, enemies));
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
