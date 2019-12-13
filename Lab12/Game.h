#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
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
    void SetPlayer(class Player* p){mPlayer = p;}
    std::vector<Actor*>& GetObjects(){return mObjects;}
    std::queue<class Checkpoint*>& GetCheckpoints(){return mCheckpoints;}
    std::vector<class SecurityCamera*>& GetSecurityCameras() {return mSecurityCameras;}
    
    void SetNextLevel(std::string s) {mNextLevel = s;}
    
    int GetBGMChannel(){return BGMChannel;}

	Mix_Chunk* GetSound(const std::string& fileName);

	class Renderer* GetRenderer() {	return mRenderer; }
    
    float& GetTime() {return mTime;}
    float& GetCheckpointTimer() {return mCheckpointTextTimer;}
    int& GetCoinCount() {return coinCount;}
    
    std::string GetCurrCheckpointText() {return mCurrCheckpointText;}
    void SetCurrCheckpointText(std::string s) {mCurrCheckpointText = s;}
    
    void LoadNextLevel();
    
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
    std::vector<class Actor*> mObjects;
    std::vector<class SecurityCamera*> mSecurityCameras;
    std::queue<class Checkpoint*> mCheckpoints;

	class Renderer* mRenderer;
    class Player* mPlayer;
    class Arrow* mArrow;
    std::string mNextLevel;
    std::string mCurrCheckpointText = " ";
    
    int BGMChannel = -1;
    float mTime = 0.0f;
    float mCheckpointTextTimer = 0.0f;
    int coinCount = 0;

	Uint32 mTicksCount;
	bool mIsRunning;
};
