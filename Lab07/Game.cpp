//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include <fstream>
#include "Renderer.h"
#include "Random.h"
#include "Player.h"
#include "SideBlock.h"
#include "Block.h"
#include "MeshComponent.h"

Game::Game()
:mIsRunning(true)
{
	
}

bool Game::Initialize()
{
	Random::Init();

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// TODO: Create renderer
    mRenderer = new Renderer(this);
    if(!mRenderer->Initialize(1024.0f, 768.0f))
        return false;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.01667f)
	{
		deltaTime = 0.01667f;
	}
	mTicksCount = SDL_GetTicks();
	
	// Make copy of actor vector
	// (iterate over this in case new actors are created)
	std::vector<Actor*> copy = mActors;
	// Update all actors
	for (auto actor : copy)
	{
		actor->Update(deltaTime);
	}

	// Add any actors to destroy to a temp vector
	std::vector<Actor*> destroyActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == ActorState::Destroy)
		{
			destroyActors.emplace_back(actor);
		}
	}

	// Delete the destroyed actors (which will
	// remove them from mActors)
	for (auto actor : destroyActors)
	{
		delete actor;
	}
    
    //Dynamically create blocks
    if(mPlayer->GetPosition().x + SIDEBLOCK_GENERATE_DISTANCE > LastBlockX + SIDEBLOCK_X_LENGTH){
        SideBlock* sl = new SideBlock(this);
        SideBlock* sr = new SideBlock(this);
        sl->SetPosition(Vector3(LastBlockX + SIDEBLOCK_X_LENGTH,-SIDEBLOCK_Y_POSITION,0.0f));
        sr->SetPosition(Vector3(LastBlockX + SIDEBLOCK_X_LENGTH,SIDEBLOCK_Y_POSITION,0.0f));
        int index = (static_cast<int>(sl->GetPosition().x) / 500) % 4;
        sl->mc->SetTextureIndex(index);
        sr->mc->SetTextureIndex(index);
        LastBlockX += SIDEBLOCK_X_LENGTH;
        if(static_cast<int>(LastBlockX + SIDEBLOCK_X_LENGTH) % 1000 == 0){
            int index = static_cast<int>(LastBlockX + SIDEBLOCK_X_LENGTH) / 1000;
            if(index <= 20){
                LoadBlocks("Assets/Blocks/" + std::to_string(index) + ".txt", index * 1000);
            }
            else{
                LoadBlocks("Assets/Blocks/" + std::to_string(Random::GetIntRange(1, 20)) + ".txt", index * 1000);
            }
        }
    }
}

void Game::GenerateOutput()
{
	// TODO: tell renderer to draw
    mRenderer->Draw();
}

void Game::LoadData()
{
    mPlayer = new Player(this);
    for(float x = 0.0f; x < 3000.0f; x += SIDEBLOCK_X_LENGTH){
        SideBlock* sl = new SideBlock(this);
        SideBlock* sr = new SideBlock(this);
        sl->SetPosition(Vector3(x,-SIDEBLOCK_Y_POSITION,0.0f));
        sr->SetPosition(Vector3(x,SIDEBLOCK_Y_POSITION,0.0f));
        int index = (static_cast<int>(sl->GetPosition().x) / 500) % 4;
        sl->mc->SetTextureIndex(index);
        sr->mc->SetTextureIndex(index);
    }
    for(float x = 1000.0f; x <= 3000.0f; x += BLOCK_X_LENGTH){
        int index = static_cast<int>( x / 1000.0f);
        LoadBlocks("Assets/Blocks/" + std::to_string(index) + ".txt", x);
    }
    LastBlockX = 2500.0f;
    BGMChannel = Mix_PlayChannel(-1, mPlayer->GetGame()->GetSound("Assets/Sounds/ShipLoop.wav"), -1);
    
    Matrix4 projectionMatrix = Matrix4::CreatePerspectiveFOV(1.22f, 1024.0f, 768.0f, 10.0f, 10000.0f);
    mRenderer->SetProjectionMatrix(projectionMatrix);
    Matrix4 viewMatrix = Matrix4::CreateLookAt(Vector3(-300.0f,0.0f,100.0f), Vector3(20.0f,0.0f,0.0f), Vector3::UnitZ);
    mRenderer->SetViewMatrix(viewMatrix);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy sounds
	for (auto s : mSounds)
	{
		Mix_FreeChunk(s.second);
	}
	mSounds.clear();
}

void Game::AddBlock(class Block* b){
    mBlocks.push_back(b);
}
void Game::RemoveBlock(class Block* b){
    std::vector<Block*>::iterator i = find(mBlocks.begin(),mBlocks.end(),b);
    if(i != mBlocks.end()){
        mBlocks.erase(i);
    }
}

Mix_Chunk* Game::GetSound(const std::string& fileName)
{
	Mix_Chunk* chunk = nullptr;
	auto iter = mSounds.find(fileName);
	if (iter != mSounds.end())
	{
		chunk = iter->second;
	}
	else
	{
		chunk = Mix_LoadWAV(fileName.c_str());
		if (!chunk)
		{
			SDL_Log("Failed to load sound file %s", fileName.c_str());
			return nullptr;
		}

		mSounds.emplace(fileName, chunk);
	}
	return chunk;
}

void Game::Shutdown()
{
	UnloadData();
	Mix_CloseAudio();
	// TODO: Delete renderer
    mRenderer->Shutdown();
    delete mRenderer;
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		auto iter2 = mActors.end() - 1;
		std::iter_swap(iter, iter2);
		mActors.pop_back();
	}
}

void Game::LoadBlocks(std::string filename, float x){
    std::ifstream in(filename);
    Vector3 pos(x, -237.5f, 237.5f);
    if(in){
        std::string line;
        while(getline(in,line)){
            for(auto b : line){
                if(b == 'A'){
                    Block* a = new Block(this, false);
                    a->SetPosition(pos);
                }
                else if(b == 'B'){
                    Block* b = new Block(this, true);
                    b->SetPosition(pos);
                }
                pos.y += 25.0f;
            }
            pos.z -= 25.0f;
            pos.y = -237.5f;
        }
    }
}
