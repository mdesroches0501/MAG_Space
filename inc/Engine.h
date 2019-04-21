/*
 * Engine.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef ENGINE_H_
#define ENGINE_H_

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;
class SoundMgr;

class Engine {
public:
	Engine();
	virtual ~Engine();

	void Init();
	void Run();
	void TickAll(float dt);
	void Cleanup();
	
	bool m_KeepRunning;
	
	EntityMgr *m_EntityMgr;
	GameMgr   *m_GameMgr;
	GfxMgr    *m_GfxMgr;
	InputMgr  *m_InputMgr;
	SoundMgr  *m_SoundMgr;
};

#endif /* ENGINE_H_ */
