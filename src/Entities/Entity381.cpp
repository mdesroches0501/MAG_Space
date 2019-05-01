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


void DestroyAllAttachedMovableObjects(Ogre::SceneNode* node)
{
    // Destroy all the attached objects
    auto objectIter = node->getAttachedObjectIterator();

    while ( objectIter.hasMoreElements() )
    {
      auto moveableObject = static_cast<Ogre::MovableObject*>(objectIter.getNext());
      node->getCreator()->destroyMovableObject( moveableObject );
    }
    
    // Recurse to child SceneNodes
    auto childIter = node->getChildIterator();
    
    while ( childIter.hasMoreElements() )
    {
      Ogre::SceneNode* pChildNode = static_cast<Ogre::SceneNode*>(childIter.getNext());
      DestroyAllAttachedMovableObjects( pChildNode );
    }
}


Entity381::Entity381(Engine *engine, Ogre::Vector3 pos, std::string name)
{

    this->m_Engine = engine;

    m_EntityType = NONE;
    m_Meshfilename = std::string();
    m_Position = pos;
    m_OldPosition = pos;
    m_Velocity = Ogre::Vector3(0, 0, 0);
    m_Name = name;
    
    m_Yaw = m_Roll = m_Pitch = m_OldYaw = m_OldRoll = m_OldPitch = 0;

    m_SceneNode = 0;
    m_CameraNode = 0;
    m_OgreEntity = 0;
    
    m_PlaySound = false;
    m_AuioId = 0;
    
    m_DeleteNextTick = false;
    
    Renderable* renderable = new Renderable(this, RENDERABLE);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::RENDERABLE, (Aspect*)renderable));
}

Entity381::~Entity381()
{
    std::cout << "I should be dying" << std::endl;
    for(auto iter = m_Aspects.begin(); iter != m_Aspects.end(); iter++)
    {
        delete iter->second;
    }
    
    m_Aspects.clear();
    
    DestroyAllAttachedMovableObjects(m_SceneNode);
    
    m_SceneNode->removeAndDestroyAllChildren();
    m_Engine->m_GfxMgr->m_SceneMgr->destroySceneNode(m_SceneNode);
}

void Entity381::Init()
{
    m_OgreEntity = m_Engine->m_GfxMgr->m_SceneMgr->createEntity(m_Meshfilename);
    m_SceneNode = m_Engine->m_GfxMgr->m_SceneMgr->getRootSceneNode()->createChildSceneNode(m_Position);
    
    m_CameraNode = m_SceneNode->createChildSceneNode();
    m_CameraNode->yaw(Ogre::Radian(Ogre::Degree(-90)));
    m_CameraNode->translate(-200, 50, 0);

    m_SceneNode->attachObject(m_OgreEntity);
    
    m_SoundFile = "Boat-Sound.wav";

    m_AuioId = 0;
}

void Entity381::Tick(float dt)
{
    for(auto iter = m_Aspects.begin(); iter != m_Aspects.end(); iter++)
    {
        iter->second->Tick(dt);
    }
}
