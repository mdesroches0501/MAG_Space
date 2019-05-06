/*
 * UiMgr.h
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#ifndef INC_UIMGR_H_
#define INC_UIMGR_H_

#include <OgreWindowEventUtilities.h>
#include <OgreTextAreaOverlayElement.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <Managers/Mgr.h>
#include <string>

#include <SdkTrays.h>

class UiMgr : public Mgr, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener, public OgreBites::SdkTrayListener
{
private:


protected:
	virtual void windowResized(Ogre::RenderWindow *rw);
	virtual void windowClosed(Ogre::RenderWindow *rw);

    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    void buttonHit(OgreBites::Button *b);
    void itemSelected(OgreBites::SelectMenu *m);

public:

	UiMgr(Engine *engine);
	~UiMgr();
	virtual void Init();
	virtual void Tick(float dt);
	virtual void LoadLevel(std::string levelLocation);
	virtual void Stop();

	OgreBites::InputContext m_InputContext;
	OgreBites::SdkTrayManager* m_TrayMgr;
	Ogre::OverlaySystem* m_OverlaySystem;
	OgreBites::Label *m_Label;
	OgreBites::Label *m_InfoEntityType;
	OgreBites::Label *m_InfoEntityName;
	OgreBites::Label *m_InfoEntitySpeed;
	OgreBites::Label *m_InfoScore;
	
	OgreBites::Button *m_RestartButton;
	OgreBites::Button *m_MainMenu;
	OgreBites::Button *m_Level1;
	
	OgreBites::SdkTrayManager *m_ShowLogo;

	std::string m_CurrentLevel;
	
	Ogre::TextAreaOverlayElement *m_TextArea;
	Ogre::OverlayContainer *m_Panel;
	Ogre::Overlay* m_Overlay;
	
	unsigned int m_PlayerScore;

	// stuff we're playing with
	unsigned char RENDER_QUEUE_BACKGROUND;
	unsigned int m_PlayerCount = 5;
	unsigned int numGroupsIniit = 1;
	unsigned int numGroupsLoad = 1;
	Ogre::Real initProportion = 0.7f;
	
};

#endif /* INC_UIMGR_H_ */
