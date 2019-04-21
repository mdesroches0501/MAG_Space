/*
 * InputMgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef INPUTMGR_H_
#define INPUTMGR_H_

#include <limits>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include <Utilities/KeyMap.h>
#include <Utilities/Actions.h>
#include <Managers/Mgr.h>

extern std::map<std::string, OIS::KeyCode> KeyMap;
extern std::map<std::string, Actions> ActionMap;

class Engine;

class InputMgr : public Mgr, public OIS::KeyListener, public OIS::MouseListener
{

public:
    InputMgr(Engine *engine);
    virtual ~InputMgr();

    void Init();
    void LoadLevel(std::string levelLocation);
    void Tick(float dt);
    void Stop();

    OIS::Keyboard* GetKeyboardReference() const;
    OIS::Mouse* GetMouseReference() const;
    
    bool IsKeyDown(OIS::KeyCode kc) const;
    bool IsMouseButtonDown(OIS::MouseButtonID mb) const;

    void AssignInputsFromFile(std::ifstream& levelEntitiesFile);

    virtual bool keyPressed(const OIS::KeyEvent& ke);
    virtual bool keyReleased(const OIS::KeyEvent& ke);

    virtual bool mouseMoved(const OIS::MouseEvent& me);
    virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);

private:
    OIS::InputManager* m_InputMgr;
    OIS::Keyboard* m_Keyboard;
    OIS::Mouse* m_Mouse;
    
    std::map<OIS::KeyCode, bool> m_KeyStatuses;
    std::map<OIS::MouseButtonID, bool> m_MouseButtonStatuses;
};

#endif /* INPUTMGR_H_ */
