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
    
    std::string GetCurrentRoom(){return currentRoom;}
    void SetCurrentRoom(std::string room);
    
    class Player* GetPlayer(){return player;}
    
    std::vector<class Collider*> GetColliders(){return colliders;}
    std::vector<class SecretBlock*> GetSecretBlocks(){return secretBlocks;}
    std::vector<class Actor*> GetEnemies(std::string room){return enemy_map[room];}
    void AddToEnemies(std::string room, Actor* actor){
        enemy_map[room].push_back(actor);
    }
    void RemoveFromEnemies(std::string room, Actor* actor){
        for(std::vector<Actor*>::iterator i = enemy_map[room].begin(); i != enemy_map[room].end(); i++){
            if((*i) == actor){
                enemy_map[room].erase(i);
                break;
            }
        }
    }
    
    Vector2 GetCamPosition(){return camPosition;}
    void SetCamPosition(Vector2 pos){camPosition = pos;}
    
    int GetBGChannel(){return bgmusic_channel;}
    
    
    SDL_Texture* GetTexture(std::string filename);
    Mix_Chunk* GetSound(const std::string& filename);
    std::vector<class Door*> GetDoors(){return room_map[currentRoom];}
    
    
    constexpr const static float WALL_THICKNESS = 32.0f;
    constexpr const static int WINDOW_WIDTH = 600;
    constexpr const static int WINDOW_HEIGHT = 448;
    

protected:
    void ProcessInput();
    void GenerateOutput();
    void UpdateGame();
    void LoadData();
    void UnloadData();
    
    void loadCSVMapFile(std::string fileName);
    
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> texture_map;
    std::unordered_map<std::string, Mix_Chunk*> mix_map;
    std::unordered_map<std::string, std::vector<class Door*>> room_map;
    std::unordered_map<std::string, std::vector<class Spawner*>> spawner_map;
    std::unordered_map<std::string, std::vector<class Actor*>> enemy_map;
    std::string currentRoom;
    
    std::vector<class Actor*> actors;
    std::vector<class SpriteComponent*> sprites;
    std::vector<class Collider*> colliders;
    std::vector<class SecretBlock*> secretBlocks;
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
