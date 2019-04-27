/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <Managers/UiMgr.h>
#include <Engine.h>
#include <Managers/GfxMgr.h>
#include <Managers/InputMgr.h>
#include <Managers/EntityMgr.h>
#include <Utilities/Types381.h>

UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
    mOverlaySystem = new Ogre::OverlaySystem();
    if(mOverlaySystem)
    {	        
        m_Engine->m_GfxMgr->m_SceneMgr->addRenderQueueListener(mOverlaySystem);
    }
    else
    {
        std::cout << "Oops" << std::endl;
    }

    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){
	//init sdktrays

    mInputContext.mKeyboard = m_Engine->m_InputMgr->GetKeyboardReference();
    mInputContext.mMouse = m_Engine->m_InputMgr->GetMouseReference();
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", m_Engine->m_GfxMgr->m_Window, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UiMgr::stop(){

}

void UiMgr::LoadLevel(std::string levelLocation){
	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Spawn Boat!");
	mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "SelectButton", "Select Next");


	Ogre::StringVector options;
	options.push_back("Select Boat");
	options.push_back("Spawn SpeedBoat");
	options.push_back("Spawn Destroyer");
	options.push_back("Spawn Carrier");
	mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 300, 4,options);

	mTrayMgr->showBackdrop("ECSLENT/UI");

	mLabel = mTrayMgr->createLabel(OgreBites::TL_LEFT,"MyLabel","Label!",250);

	infoLabel = mTrayMgr->createLabel(OgreBites::TL_RIGHT, "infoLabel", "No Unit Selected", 250);
	infoLabel2 = mTrayMgr->createLabel(OgreBites::TL_RIGHT, "infoLabel2", "No Unit Selected", 250);
	infoLabel3 = mTrayMgr->createLabel(OgreBites::TL_RIGHT, "infoLabel3", "No Unit Selected", 250);


	OgreBites::ProgressBar * pbar;
	pbar = mTrayMgr->createProgressBar(OgreBites::TL_TOP,"HealthBar", "Health", 300, 200);
	pbar->setProgress(100);

}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();

    infoLabel->setCaption("Type: Player");
    infoLabel2->setCaption("Heading: " + m_Engine->m_EntityMgr->GetPlayerByName("player1")->m_Name);
    infoLabel3->setCaption("Speed: " + std::to_string(m_Engine->m_EntityMgr->GetPlayerByName("player1")->m_Speed));

}

void UiMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mInputContext.mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){
    if(b->getName()=="MyButton")
    {
        std::cout <<"Boat Spawned!" << std::endl;
        Ogre::Vector3 pos;
        pos.x = 0;
        pos.y = 0;
        pos.z = -100;
        m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(PLAYER_TYPE, pos, "player " + std::to_string(playerCount++));
    }
    else if(b->getName()=="SelectButton")
    {
        std::cout <<"Selection Changed!" << std::endl;
    }
}

void UiMgr::itemSelected(OgreBites::SelectMenu *m){
    Ogre::Vector3 pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 100;
    switch(m->getSelectionIndex()){
    case 1: case 2: case 3:
        m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(PLAYER_TYPE, pos, "player " + std::to_string(playerCount++));
    	mLabel->setCaption("Player has Arrived!");
    	break;
    default:
    	break;
    }

}
