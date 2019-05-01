/*
 * Engine.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <string>

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;
class SoundMgr;
class UiMgr;

class Engine {
public:
	Engine();
	virtual ~Engine();

	void Init();
	void LoadLevel(std::string levelLocation);
	void Run();
	void TickAll(float dt);
	void Cleanup();
	
	bool m_KeepRunning;
	
	EntityMgr *m_EntityMgr;
	GameMgr   *m_GameMgr;
	GfxMgr    *m_GfxMgr;
	InputMgr  *m_InputMgr;
	SoundMgr  *m_SoundMgr;
	UiMgr     *m_UiMgr;
	
	
	std::string m_LevelToLoad;
};

#endif /* ENGINE_H_ */
