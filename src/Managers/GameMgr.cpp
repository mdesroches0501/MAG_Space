/*
 * GameMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <Engine.h>
#include <Managers/GameMgr.h>
#include <Managers/EntityMgr.h>
#include <Managers/SoundMgr.h>
#include <Managers/InputMgr.h>
#include <Managers/GfxMgr.h>
#include <Entities/Entity381.h>
#include <Utilities/Types381.h>

#include <iostream>

#include <OgreOverlay.h>
#include <OgreSceneNode.h>

GameMgr::GameMgr(Engine *engine)
        : Mgr(engine)
{
    cameraNode = 0;
    m_Restart = false;
}

GameMgr::~GameMgr()
{
    // TODO Auto-generated destructor stub
}



void GameMgr::Init()
{

}

void GameMgr::LoadLevel(std::string levelLocation)
{
    cameraNode = 0;
    
    m_Engine->m_GfxMgr->m_SceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    m_Engine->m_GfxMgr->m_Camera->lookAt(Ogre::Vector3(0, 0, 0));
    Ogre::Light* light = m_Engine->m_GfxMgr->m_SceneMgr->createLight("MainLight");
    light->setPosition(20.0, 80.0, 50.0);

    // a fixed point in the ocean so you can see relative motion
/*
    Ogre::Entity* ogreEntityFixed = m_Engine->m_GfxMgr->m_SceneMgr->createEntity("robot.mesh");
    Ogre::SceneNode* sceneNode = m_Engine->m_GfxMgr->m_SceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 100, -200));
    sceneNode->attachObject(ogreEntityFixed);
    sceneNode->showBoundingBox(true);
  */  

    // A node to attach the camera to so we can move the camera node instead of the camera.
    cameraNode = m_Engine->m_GfxMgr->m_SceneMgr->getRootSceneNode()->createChildSceneNode("MainCamera");
    cameraNode->setPosition(0, 200, 500);
    //cameraNode->attachObject(m_Engine->m_GfxMgr->mCamera);
    PlayerEntity381* player = m_Engine->m_EntityMgr->GetPlayerByName("player1");
    if(player != NULL)
    {
        player->m_CameraNode->attachObject(m_Engine->m_GfxMgr->m_Camera);
    }
    

    //m_Engine->m_GfxMgr->MakeGround();
    m_Engine->m_GfxMgr->MakeSky();
    MakeEntities();
}

void GameMgr::Tick(float dt)
{
    if(m_Restart)
    {
        m_Restart = false;
        m_Engine->Cleanup();
        m_Engine->LoadLevel(m_Engine->m_LevelToLoad);
    }
}

void GameMgr::Stop()
{
    
}

void GameMgr::MakeEntities()
{
    //Ogre::Vector3 pos = Ogre::Vector3(-1000, 0, 0);
    /*m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(DDG51Type, pos);
     pos.x += 500;
     m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(CarrierType, pos);
     pos.x += 500;
     m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(SpeedBoatType, pos);
     pos.x += 500;
     m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(FrigateType, pos);
     pos.x += 500;
     m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(AlienType, pos);

     pos.x = 0;
     m_Engine->m_EntityMgr->CreateEntityOfTypeAtPosition(BansheeType, pos);

     m_Engine->m_EntityMgr->SelectNextEntity(); //sets selection
     */
}

