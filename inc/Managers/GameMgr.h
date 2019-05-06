/*
 * GameMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GAMEMGR_H_
#define GAMEMGR_H_

#include <OgreSceneNode.h>

#include <Managers/Mgr.h>

class GameMgr: public Mgr {
public:
	GameMgr(Engine *engine);
	virtual ~GameMgr();

	void Init();
	void LoadLevel(std::string levelLocation);
	void Tick(float dt);
	void Stop();

	void MakeGround();
	void MakeSky();
	void MakeEntities();

	Ogre::SceneNode *cameraNode;
	
	bool m_Restart;

};

#endif /* GAMEMGR_H_ */
