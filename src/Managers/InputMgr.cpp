/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include <cfloat>

#include <Engine.h>
#include <Managers/InputMgr.h>
#include <Managers/GfxMgr.h>
#include <Managers/EntityMgr.h>
#include <Managers/GameMgr.h>
#include <Aspects/UnitAI.h>
#include <Utilities/Command.h>
#include <Utilities/Utils.h>

InputMgr::InputMgr(Engine *engine)
        : Mgr(engine), OIS::KeyListener(), OIS::MouseListener()
{
    this->m_InputMgr = 0;
    this->m_Keyboard = 0;
    this->m_Mouse = 0;
}

InputMgr::~InputMgr()
{

}

void InputMgr::Init()
{
    OIS::ParamList pl;
    size_t windowHandle = 0;
    std::ostringstream windowHandleStr;

    m_Engine->m_GfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
    windowHandleStr << windowHandle;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
    // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
#if defined OIS_WIN32_PLATFORM
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

    m_InputMgr = OIS::InputManager::createInputSystem(pl);

    m_Keyboard = static_cast<OIS::Keyboard*>(m_InputMgr->createInputObject(OIS::OISKeyboard, true));
    m_Mouse = static_cast<OIS::Mouse*>(m_InputMgr->createInputObject(OIS::OISMouse, true));

    int left, top;
    unsigned int width, height, depth;

    m_Engine->m_GfxMgr->mWindow->getMetrics(width, height, depth, left, top);
    const OIS::MouseState &ms = m_Mouse->getMouseState();
    ms.width = width;
    ms.height = height;
    m_Mouse->setEventCallback(this);
    m_Keyboard->setEventCallback(this);

    
    
    for(unsigned int key = (unsigned int)OIS::KC_UNASSIGNED; key <= (unsigned int)OIS::KC_MEDIASELECT; key++)
    {
        m_KeyStatuses.insert(std::pair<OIS::KeyCode, bool>((OIS::KeyCode)key, false));
    }

    for(unsigned int mouseButton = (unsigned int)OIS::MB_Left; mouseButton <= (unsigned int)OIS::MB_Button7; mouseButton++)
    {
        m_MouseButtonStatuses.insert(std::pair<OIS::MouseButtonID, bool>((OIS::MouseButtonID)mouseButton, false));
    }
}

void InputMgr::LoadLevel()
{

}

void InputMgr::Tick(float dt)
{
    m_Keyboard->capture();
    if(m_Keyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        m_Engine->m_KeepRunning = false;
    }
    m_Mouse->capture();

}

void InputMgr::Stop()
{
    if(m_InputMgr)
    {
        m_InputMgr->destroyInputObject(m_Mouse);
        m_InputMgr->destroyInputObject(m_Keyboard);

        OIS::InputManager::destroyInputSystem(m_InputMgr);
        m_InputMgr = 0;
    }
}



OIS::Keyboard* InputMgr::GetKeyboardReference() const
{
    return m_Keyboard;
}

OIS::Mouse* InputMgr::GetMouseReference() const
{
    return m_Mouse;
}

bool InputMgr::IsKeyDown(OIS::KeyCode kc) const
{
    auto iter = m_KeyStatuses.find(kc);
    return iter->second;
}

bool InputMgr::IsMouseButtonDown(OIS::MouseButtonID mb) const
{
    auto iter = m_MouseButtonStatuses.find(mb);
    return iter->second;
}



bool InputMgr::keyPressed(const OIS::KeyEvent& ke)
{
    m_KeyStatuses[ke.key] = true;
    return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke)
{
    m_KeyStatuses[ke.key] = false;
    return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me)
{
    return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid)
{
    m_MouseButtonStatuses[mid] = true;
    return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid)
{
    m_MouseButtonStatuses[mid] = false;
    return true;
}

