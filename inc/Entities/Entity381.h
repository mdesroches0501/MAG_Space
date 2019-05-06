/**
 *  @file   Entity381.h
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#ifndef __Entity381_h_
#define __Entity381_h_

#include <map>

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>

#include <Aspects/Aspect.h>
#include <Utilities/Types381.h>
#include <Engine.h>

class Entity381
{
public:
    Entity381(Engine *engine, Ogre::Vector3 pos, std::string name);
    virtual ~Entity381();

    virtual void Init();
    void Tick(float dt);

    Engine *m_Engine;

    //static data
    std::string m_Name;
    std::string m_Meshfilename;
    Ogre::SceneNode* m_SceneNode;
    Ogre::Entity* m_OgreEntity;
    Ogre::SceneNode* m_MeshNode;
    Ogre::SceneNode* m_CameraNode;

    //dynamic data
    Ogre::Vector3 m_Position;
    Ogre::Vector3 m_OldPosition;
    Ogre::Quaternion m_Orientation;
    Ogre::Quaternion m_OldOrientation;
    Ogre::Vector3 m_Velocity;
    
    //sound
    std::string m_SoundFile;
    bool m_PlaySound;
    unsigned int m_AuioId; // An ID that tells the sound manager what type of sound to play.
    
    float m_Yaw, m_Roll, m_Pitch;
    float m_OldYaw, m_OldRoll, m_OldPitch;

    EntityTypes m_EntityType;

    bool m_DeleteNextTick;
    
    std::map<AspectType, Aspect*> m_Aspects;
};

#endif // #ifndef __Entity381_h_
