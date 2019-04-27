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

}

Engine::~Engine() {

}

void Engine::Init(){
	m_EntityMgr = new EntityMgr(this);
	m_GameMgr   = new GameMgr(this);
	m_GfxMgr    = new GfxMgr(this);
	m_InputMgr  = new InputMgr(this);
	m_SoundMgr  = new SoundMgr(this);
	//m_UiMgr     = new UiMgr(this);

	//--------------------------------------------------------------
	m_EntityMgr->Init();
	m_GfxMgr->Init();
	m_InputMgr->Init(); // must initialize AFTER gfx manager
	m_SoundMgr->Init();
	//m_UiMgr->Init();
	m_GameMgr->Init();

	//--------------------------------------------------------------
	m_EntityMgr->LoadLevel("levels/level1/");
	m_GfxMgr->LoadLevel("levels/level1/");
	m_InputMgr->LoadLevel("levels/level1/");
	m_SoundMgr->LoadLevel("levels/level1/");
	//m_UiMgr->LoadLevel("levels/level1/");
	m_GameMgr->LoadLevel("levels/level1/");
}


void Engine::TickAll(float dt){
	m_GfxMgr->Tick(dt);
	m_InputMgr->Tick(dt);
	m_EntityMgr->Tick(dt);
	m_SoundMgr->Tick(dt);
	//m_UiMgr->Tick(dt);
	m_GameMgr->Tick(dt);
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
	m_GfxMgr->Stop();
	m_EntityMgr->Stop();
	m_SoundMgr->Stop();
	//m_UiMgr->Stop();
	m_GameMgr->Stop();
}

