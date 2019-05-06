/**
 *  @file   PlayerEntity381.cpp
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#include <Entities/PlayerEntity381.h>
#include <Aspects/InputAspect.h>
#include <Aspects/ColliderAspect.h>
#include <Managers/GfxMgr.h>
#include <Managers/SoundMgr.h>

PlayerEntity381::PlayerEntity381(Engine *engine, Ogre::Vector3 pos, std::string name)
        : FlyingEntity381(engine, pos, name)
{
    m_Meshfilename = "banshee.mesh";
    m_EntityType = PLAYER_TYPE;

    m_Acceleration = 5.0f;
    m_YawRate = m_PitchRate = 40.0f;
    m_RollRate = 80.0f;

    m_MinSpeed = 20;
    m_MaxSpeed = 100;

    m_Altitude = m_Position.y;
    m_MaxAltitude = 1000;
    m_MinAltitude = 10;
    
    m_Health = m_MaxHealth = 100;
    
    InputAspect* inputAspect = new InputAspect(this, INPUT);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::INPUT, (Aspect*)inputAspect));
    
    PlayerCollider* playerCollider = new PlayerCollider(this, COLLIDER);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::COLLIDER, (Aspect*)playerCollider));
    
    std::cout << "Created: " << this->m_Name << std::endl;
}

PlayerEntity381::~PlayerEntity381()
{
    m_CameraNode->detachObject(m_Engine->m_GfxMgr->m_Camera);
    m_Engine->m_GfxMgr->m_SceneMgr->getSceneNode("MainCamera")->attachObject(m_Engine->m_GfxMgr->m_Camera);
    m_Engine->m_GfxMgr->m_SceneMgr->getSceneNode("MainCamera")->setPosition(m_CameraNode->getPosition());
    m_Engine->m_GfxMgr->m_SceneMgr->getSceneNode("MainCamera")->setOrientation(m_CameraNode->getOrientation());
    
    m_Engine->m_SoundMgr->loadStartBackground();
}


void PlayerEntity381::Init()
{
    FlyingEntity381::Init();
}
