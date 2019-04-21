/**
 *  @file   Entity381.cpp
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#include <Managers/GfxMgr.h>
#include <Entities/Entity381.h>
#include <Aspects/UnitAI.h>
#include <Utilities/Utils.h>

Entity381::Entity381(Engine *engine, Ogre::Vector3 pos, int ident)
{

    this->m_Engine = engine;

    m_EntityType = NONE;
    m_Meshfilename = std::string();
    m_Position = pos;
    m_Velocity = Ogre::Vector3(0, 0, 0);
    m_Identity = ident;
    m_Name = "Entity381";
    
    m_Yaw = m_Roll = m_Pitch = 0;

    m_SceneNode = 0;
    m_CameraNode = 0;
    m_OgreEntity = 0;

    Renderable* renderable = new Renderable(this, RENDERABLE);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::RENDERABLE, (Aspect*)renderable));
}

Entity381::~Entity381()
{

}

void Entity381::Init()
{
    m_Name = m_Meshfilename + IntToString(m_Identity);
    m_OgreEntity = m_Engine->m_GfxMgr->mSceneMgr->createEntity(m_Meshfilename);
    m_SceneNode = m_Engine->m_GfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(m_Position);
    
    m_CameraNode = m_SceneNode->createChildSceneNode();
    m_CameraNode->yaw(Ogre::Radian(Ogre::Degree(-90)));
    m_CameraNode->translate(-200, 75, 0);

    m_SceneNode->attachObject(m_OgreEntity);
}

void Entity381::Tick(float dt)
{
    for(auto iter = m_Aspects.begin(); iter != m_Aspects.end(); iter++)
    {
        iter->second->Tick(dt);
    }
}
