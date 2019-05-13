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

#include <OgreRectangle2D.h>

UiMgr::UiMgr(Engine* eng)
        : Mgr(eng)
{
    m_OverlaySystem = NULL;
    m_TrayMgr = NULL;
    m_Label = NULL;
    m_InfoEntityType = NULL;
    m_InfoEntityName = NULL;
    m_InfoEntitySpeed = NULL;
    
    m_PlayerScore = 0;
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

void UiMgr::LoadLevel(std::string levelLocation)
{
    //init sdktrays (Make sure to only do this once)
    if(!m_TrayMgr)
    {        
        m_TrayMgr = new OgreBites::SdkTrayManager("InterfaceName", m_Engine->m_GfxMgr->m_Window, m_InputContext, this);
    }
    
  //  m_TrayMgr->showBackdrop("ECSLENT/UI");

    m_InfoEntityType = m_TrayMgr->createLabel(OgreBites::TL_RIGHT, "InfoEntityType", "No Unit Selected", 370);
    m_InfoEntityName = m_TrayMgr->createLabel(OgreBites::TL_RIGHT, "InfoEntityName", "No Unit Selected", 370);
    m_InfoEntitySpeed = m_TrayMgr->createLabel(OgreBites::TL_RIGHT, "InfoEntitySpeed", "No Unit Selected", 370);
    m_InfoScore = m_TrayMgr->createLabel(OgreBites::TL_BOTTOM, "InfoScore", "", 370);
    
    m_MainMenu = m_TrayMgr->createButton(OgreBites::TL_TOPLEFT, "MainMenuButton", "Main Menu", 310);
    m_Level1 = m_TrayMgr->createButton(OgreBites::TL_TOPLEFT, "Level1Button", "Level 1", 310);
    m_Level2 = m_TrayMgr->createButton(OgreBites::TL_TOPLEFT, "Level2Button", "Level 2", 310);
    m_RestartButton = m_TrayMgr->createButton(OgreBites::TL_TOPLEFT, "GameOverButton", "Restart?", 310);
    
    PlayerEntity381* player = m_Engine->m_EntityMgr->GetPlayerByName("player1");
    
    if(m_CurrentLevel != "levels/MainMenu/")
    {
        OgreBites::ProgressBar * pbar;        
        pbar = m_TrayMgr->createProgressBar(OgreBites:: TL_BOTTOM, "HealthBar", "Health", 300, 200);
        if(player == NULL)
        {
            std::cerr << "UiMgr::LoadLevel : No Player Found!" << std::endl;
            pbar->setProgress(0);
            pbar->hide();
            m_InfoScore->hide();
        }
        else
        {
            pbar->setProgress(player->m_Health / (float)player->m_MaxHealth);
            std::cout << "UiMgr Health: " << player->m_Health << std::endl;
            m_InfoScore->setCaption("Score: " + std::to_string(m_PlayerScore));
            m_InfoScore->show();
        }
    }
    /*
    if(m_Panel == NULL)
    {        
        m_Panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingletonPtr()->createOverlayElement("Panel","GUI"));
        m_Panel->setMetricsMode(Ogre::GMM_PIXELS);
        m_Panel->setPosition(0,0);
        m_Panel->setDimensions(0.5f,0.5f);
        m_Overlay = Ogre::OverlayManager::getSingletonPtr()->create("GUI_OVERLAY");
        m_Overlay->add2D(m_Panel);
    }
    */
    m_CurrentLevel = levelLocation;
    
    if(m_CurrentLevel == "levels/MainMenu/")
    {

    	m_Label = m_TrayMgr->createLabel(OgreBites::TL_TOP, "TempSplash", "MAG Space", 700);
    	m_Label = m_TrayMgr->createLabel(OgreBites::TL_TOP, "TempSplash1", "Instructions: select level, WASD for controls, watch out for asteroids!", 700);
    	m_Label = m_TrayMgr->createLabel(OgreBites::TL_TOP, "TempSplash2", "Created by: Michael Des Roches, Alex Pansinski, Gianni Pinneri (MAG)", 700);

    	
    	//m_TrayMgr->showLoadingBar(numGroupsIniit, numGroupsLoad, initProportion);
    	//m_TrayMgr->showLogo(OgreBites::TL_CENTER, 1);
    	// Create background material
    	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
    	material->getTechnique(0)->getPass(0)->createTextureUnitState("splash.png");
    	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
    	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

    	// Create background rectangle covering the whole screen
    	Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
    	rect->setCorners(-0.3, 0.5, 0.3, -0.5);
    	rect->setMaterial("Background");

    	// Render the background before everything else
    	//rect->Ogre::RenderQueueGroupID::RENDER_QUEUE_BACKGROUND;
    	//rect->setRenderQueueGroup(Ogre::RenderQueueGroupID::RENDER_QUEUE_BACKGROUND);

    	// Use infinite AAB to always stay visible
    	Ogre::AxisAlignedBox aabInf;
    	aabInf.setInfinite();
    	rect->setBoundingBox(aabInf);

    	// Attach background to the scene
    	Ogre::SceneNode* node = m_Engine->m_GfxMgr->m_SceneMgr->getRootSceneNode()->createChildSceneNode("Background");
    	node->attachObject(rect);

    	// Example of background scrolling
    	//material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setScrollAnimation(-0.25, 0.0);

    	// Don't forget to delete the Rectangle2D in the destructor of your application:
    	//delete rect;*/



    }
    else
    {
        // Hide title card
    }
    
    
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
    
    if(player != NULL)
    {        
        m_InfoEntityType->setCaption("Type: Player");
        m_InfoEntityName->setCaption("Name: " + player->m_Name);
        m_InfoEntitySpeed->setCaption("Speed: " + std::to_string(player->m_Speed));
        
        OgreBites::ProgressBar* pbar = (OgreBites::ProgressBar*)m_TrayMgr->getWidget("HealthBar");
        pbar->setProgress(player->m_Health / (float)player->m_MaxHealth);
        m_InfoScore->setCaption("Score: " + std::to_string(m_PlayerScore));
    }
    else
    {
        if(m_CurrentLevel == "levels/MainMenu/")
        {
            m_InfoEntityType->setCaption("Mike - Lead Artist");
            m_InfoEntityName->setCaption("Alex - Lead Programmer");
            m_InfoEntitySpeed->setCaption("Gianni - Lead Producer");
        }
        else
        {            
            OgreBites::ProgressBar* pbar = (OgreBites::ProgressBar*)m_TrayMgr->getWidget("HealthBar");
            m_InfoEntityType->setCaption("Type: Dead");
            m_InfoEntityName->setCaption("Name: Guitar Warrior");
            m_InfoEntitySpeed->setCaption("YOU ARE DEAD, DEEEAD DEEAAAD!");
            m_InfoScore->setCaption("Your lousy score was: " + std::to_string(m_PlayerScore));
            pbar->setProgress(0);
        }
        
    }
    
    //std::cout << "UiMgr Health: " << player->m_Health << std::endl; 
    
//    if(player->m_Health <= 0)
//    {
//        //m_Overlay->show(); // Not working right. Should show m_TextArea but instead gives weird triangle artifacts.
//    }
//    else
//    {
//        //m_Overlay->hide();
//    }
}

void UiMgr::Stop()
{
    delete m_TrayMgr;
    m_TrayMgr = NULL;
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
    else if(b->getName() == "GameOverButton")
    {
        m_Engine->m_GameMgr->m_Restart = true;
    }
    else if(b->getName() == "MainMenuButton")
    {
        m_Engine->m_LevelToLoad = "levels/MainMenu/";
        m_Engine->m_GameMgr->m_Restart = true;
    }
    else if(b->getName() == "Level1Button")
    {
        m_Engine->m_LevelToLoad = "levels/level1/";
        m_Engine->m_GameMgr->m_Restart = true;
    }
    else if(b->getName() == "Level2Button")
    {
        m_Engine->m_LevelToLoad = "levels/level2/";
        m_Engine->m_GameMgr->m_Restart = true;
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
