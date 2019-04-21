/*
 * Engine.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>
#include <Managers/EntityMgr.h>
#include <Managers/GameMgr.h>
#include <Managers/GfxMgr.h>
#include <Managers/InputMgr.h>

Engine::Engine() {
	m_EntityMgr = 0; //null
	m_GameMgr   = 0;
	m_GfxMgr    = 0;
	m_InputMgr  = 0;

	m_KeepRunning = true;

}

Engine::~Engine() {

}

void Engine::Init(){
	m_EntityMgr = new EntityMgr(this);
	m_GameMgr   = new GameMgr(this);
	m_GfxMgr    = new GfxMgr(this);
	m_InputMgr  = new InputMgr(this);

	//--------------------------------------------------------------
	m_EntityMgr->Init();
	m_GfxMgr->Init();
	m_InputMgr->Init(); // must initialize AFTER gfx manager
	m_GameMgr->Init();

	//--------------------------------------------------------------
	m_EntityMgr->LoadLevel();
	m_GfxMgr->LoadLevel();
	m_InputMgr->LoadLevel();
	m_GameMgr->LoadLevel();
}


void Engine::TickAll(float dt){
	m_GfxMgr->Tick(dt);
	m_InputMgr->Tick(dt);
	m_EntityMgr->Tick(dt);
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
	m_GameMgr->Stop();
}

