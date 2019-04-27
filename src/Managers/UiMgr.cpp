/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <Managers/UiMgr.h>
#include <Engine.h>
#include <Managers/GfxMgr.h>
#include <Managers/GameMgr.h>
#include <Managers/SoundMgr.h>
#include <Managers/InputMgr.h>
#include <Managers/EntityMgr.h>
#include <Utilities/Types381.h>

UiMgr::UiMgr(Engine* eng)
        : Mgr(eng)
{
    m_OverlaySystem = NULL;
    m_TrayMgr = NULL;
    m_Label = NULL;
    m_InfoEntityType = NULL;
    m_InfoEntityName = NULL;
    m_InfoEntitySpeed = NULL;
}

UiMgr::~UiMgr()
{ // before gfxMgr destructor

}

void UiMgr::Init()
{
    // Initialize the OverlaySystem (changed for Ogre 1.9)
    m_OverlaySystem = new Ogre::OverlaySystem();
    if(m_OverlaySystem)
    {
        m_Engine->m_GfxMgr->m_SceneMgr->addRenderQueueListener(m_OverlaySystem);
    }
    else
    {
        std::cout << "Oops" << std::endl;
    }

    m_InputContext.mKeyboard = m_Engine->m_InputMgr->GetKeyboardReference();
    m_InputContext.mMouse = m_Engine->m_InputMgr->GetMouseReference();
    //Ogre::WindowEventUtilities::addWindowEventListener(m_Engine->m_GfxMgr->m_Window, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UiMgr::stop()
{

}

void UiMgr::LoadLevel(std::string levelLocation)
{
    //init sdktrays (Make sure to only do this once)
    if(!m_TrayMgr)
    {        
        m_TrayMgr = new OgreBites::SdkTrayManager("InterfaceName", m_Engine->m_GfxMgr->m_Window, m_InputContext, this);
    }
    
    
    m_TrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Spawn Boat!");
    m_TrayMgr->createButton(OgreBites::TL_TOPLEFT, "SelectButton", "Select Next");

    Ogre::StringVector options;
    options.push_back("Select Boat");
    options.push_back("Spawn SpeedBoat");
    options.push_back("Spawn Destroyer");
    options.push_back("Spawn Carrier");
    m_TrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 300, 4, options);

    m_TrayMgr->showBackdrop("ECSLENT/UI");

    m_Label = m_TrayMgr->createLabel(OgreBites::TL_LEFT, "MyLabel", "Label!", 250);

    m_InfoEntityType = m_TrayMgr->createLabel(OgreBites::TL_RIGHT, "InfoEntityType", "No Unit Selected", 250);
    m_InfoEntityName = m_TrayMgr->createLabel(OgreBites::TL_RIGHT, "InfoEntityName", "No Unit Selected", 250);
    m_InfoEntitySpeed = m_TrayMgr->createLabel(OgreBites::TL_RIGHT, "InfoEntitySpeed", "No Unit Selected", 250);

    PlayerEntity381* player = m_Engine->m_EntityMgr->GetPlayerByName("player1");
    
    OgreBites::ProgressBar * pbar;
    pbar = m_TrayMgr->createProgressBar(OgreBites::TL_TOP, "HealthBar", "Health", 300, 200);
    pbar->setProgress(player->m_Health / (float)player->m_MaxHealth);
    std::cout << "UiMgr Health: " << player->m_Health << std::endl; 
    
    m_Panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel","GUI"));
    m_Panel->setMetricsMode(Ogre::GMM_PIXELS);
    m_Panel->setPosition(0,0);
    m_Panel->setDimensions(1.0f,1.0f);
    m_Overlay = Ogre::OverlayManager::getSingletonPtr()->create("GUI_OVERLAY");
    m_Overlay->add2D(m_Panel);
    
    std::string gameOver = "You are dead, deeaad deeaaad!";
    //m_TextArea = static_cast<Ogre::TextAreaOverlayElement*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("TextArea", gameOver));
    //m_TextArea->setDimensions(1.0f,1.0f);
    //m_TextArea->setMetricsMode(Ogre::GMM_RELATIVE);
    //m_TextArea->setCharHeight(0.03f);
    
    //m_Panel->addChild(m_TextArea);
}

void UiMgr::Tick(float dt)
{
    m_TrayMgr->refreshCursor();

    PlayerEntity381* player = m_Engine->m_EntityMgr->GetPlayerByName("player1");
    
    m_InfoEntityType->setCaption("Type: Player");
    m_InfoEntityName->setCaption("Name: " + player->m_Name);
    m_InfoEntitySpeed->setCaption("Speed: " + std::to_string(player->m_Speed));
    
    
    OgreBites::ProgressBar* pbar = (OgreBites::ProgressBar*)m_TrayMgr->getWidget("HealthBar");
    pbar->setProgress(player->m_Health / (float)player->m_MaxHealth);
    std::cout << "UiMgr Health: " << player->m_Health << std::endl; 
    
    if(player->m_Health <= 0)
    {
        //m_Overlay->show(); // Not working right. Should show m_TextArea but instead gives weird triangle artifacts.
    }
    else
    {
        //m_Overlay->hide();
    }
}

void UiMgr::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = m_InputContext.mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw)
{

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg)
{
    std::cout << "Key Pressed: " << arg.key << std::endl;
    return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg)
{
    return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg)
{
    if(m_TrayMgr->injectMouseMove(arg))
        return true;
    return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid)
{
    std::cout << "mouse clicked" << std::endl;
    if(m_TrayMgr->injectMouseDown(me, mid))
        return true;
    return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    if(m_TrayMgr->injectMouseUp(arg, id))
        return true;
    /* normal mouse processing here... */
    return false;
}

void UiMgr::buttonHit(OgreBites::Button *b)
{
    if(b->getName() == "MyButton")
    {
        std::cout << "Boat Spawned!" << std::endl;
        Ogre::Vector3 pos;
        pos.x = 0;
        pos.y = 0;
        pos.z = -100;
        m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(PLAYER_TYPE, pos, "player " + std::to_string(m_PlayerCount++));
    }
    else if(b->getName() == "SelectButton")
    {
        std::cout << "Selection Changed!" << std::endl;
    }
}

void UiMgr::itemSelected(OgreBites::SelectMenu *m)
{
    Ogre::Vector3 pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 100;
    switch(m->getSelectionIndex())
    {
    case 1:
    case 2:
    case 3:
        m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(PLAYER_TYPE, pos, "player " + std::to_string(m_PlayerCount++));
        m_Label->setCaption("Player has Arrived!");
        break;
    default:
        break;
    }

}
