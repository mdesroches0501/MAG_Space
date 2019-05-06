/*
 * Engine.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>
#include <Managers/EntityMgr.h>
#include <Managers/SoundMgr.h>
#include <Managers/GameMgr.h>
#include <Managers/GfxMgr.h>
#include <Managers/InputMgr.h>
#include <Managers/UiMgr.h>

Engine::Engine() {
	m_EntityMgr = 0; //null
	m_GameMgr   = 0;
	m_GfxMgr    = 0;
	m_InputMgr  = 0;
	m_SoundMgr  = 0;
	m_UiMgr     = 0;

	m_KeepRunning = true;

	m_LevelToLoad = "levels/MainMenu/";	
}

Engine::~Engine() {

}

void Engine::Init(){
	m_EntityMgr = new EntityMgr(this);
	m_GameMgr   = new GameMgr(this);
	m_GfxMgr    = new GfxMgr(this);
	m_InputMgr  = new InputMgr(this);
	m_SoundMgr  = new SoundMgr(this);
	m_UiMgr     = new UiMgr(this);

	//--------------------------------------------------------------
	m_EntityMgr->Init();
	m_GfxMgr->Init();
	m_InputMgr->Init(); // must initialize AFTER gfx manager
	m_SoundMgr->Init();
	m_GameMgr->Init();
	m_UiMgr->Init();

	//--------------------------------------------------------------
	LoadLevel(m_LevelToLoad);
}

void Engine::LoadLevel(std::string levelLocation)
{
    m_UiMgr->m_CurrentLevel = m_LevelToLoad;
    m_EntityMgr->LoadLevel(levelLocation);
    m_GfxMgr->LoadLevel(levelLocation);
    m_InputMgr->LoadLevel(levelLocation);
    m_GameMgr->LoadLevel(levelLocation);
    m_SoundMgr->LoadLevel(levelLocation);
    m_UiMgr->LoadLevel(levelLocation);
}

void Engine::TickAll(float dt){
	m_GfxMgr->Tick(dt);
	m_InputMgr->Tick(dt);
	m_EntityMgr->Tick(dt);
	m_SoundMgr->Tick(dt);
	m_GameMgr->Tick(dt);
	m_UiMgr->Tick(dt);
}


void Engine::Run(){
	const float MICROSECONDS_PER_SECOND = 1000000.0f;
	Ogre::Timer* timer = new Ogre::Timer();

	float oldTime = timer->getMicroseconds()/MICROSECONDS_PER_SECOND;
	float newTime = timer->getMicroseconds()/MICROSECONDS_PER_SECOND;
	float dt = newTime - oldTime;

	while(m_KeepRunning){

		TickAll(dt);

		newTime = timer->getMicroseconds()/MICROSECONDS_PER_SECOND;
		dt = newTime - oldTime;
		oldTime = newTime;

	}
	// main must call cleanup or bad stuff happens->Cleanup()
}

void Engine::Cleanup(){
	m_InputMgr->Stop();
	m_EntityMgr->Stop();
	m_GfxMgr->Stop();
	m_SoundMgr->Stop();
	m_GameMgr->Stop();
	m_UiMgr->Stop();
	std::cout << "Stopped" << std::endl;
}

