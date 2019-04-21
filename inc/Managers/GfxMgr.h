/*
 * GfxMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef GFXMGR_H_
#define GFXMGR_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <Managers/Mgr.h>


class GfxMgr:
		public Mgr,
		public Ogre::WindowEventListener,
		public Ogre::FrameListener {
public:
	GfxMgr(Engine *engine);
	virtual ~GfxMgr();

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual void windowClosed(Ogre::RenderWindow* rw);
//---------------
	void Init();
	void LoadLevel(std::string levelLocation);
	void Tick(float dt);
	void Stop();

	void MakeGround();
	Ogre::Plane m_OceanSurface;
	float m_OceanHeight;
	void MakeSky();

	//Ogre related stuff
	Ogre::Root* m_Root;
	Ogre::String m_ResourcesCfg;
	Ogre::String m_PluginsCfg;
	Ogre::RenderWindow* m_Window;
	Ogre::SceneManager* m_SceneMgr;
	Ogre::Camera* m_Camera;
	
	bool m_FirstPerson;

};

#endif /* GFXMGR_H_ */
