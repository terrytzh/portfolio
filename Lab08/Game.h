#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
    
    class Player* GetPlayer(){return mPlayer;}
    class HeightMap* GetHeightMap(){return heightMap;}
    class Enemy* GetEnemy(){return mEnemy;}
    
    int GetBGMChannel(){return BGMChannel;}
    void SetBGMChannel(int channel){BGMChannel = channel;}

	Mix_Chunk* GetSound(const std::string& fileName);

	class Renderer* GetRenderer() {	return mRenderer; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
    void LoadBlocks(std::string filename, float x);

	std::unordered_map<std::string, Mix_Chunk*> mSounds;

	// All the actors in the game
	std::vector<class Actor*> mActors;

	class Renderer* mRenderer;
    class Player* mPlayer;
    class HeightMap* heightMap;
    class Enemy* mEnemy;
    
    float startTimer = 8.5f;
    bool started = false;
    int BGMChannel;

	Uint32 mTicksCount;
	bool mIsRunning;
};
