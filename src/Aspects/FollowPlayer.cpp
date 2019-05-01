/**
 *  @file   FollowPlayer.cpp
 *	
 *  @date   May 1, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#include <Aspects/FollowPlayer.h>

FollowPlayerAspect::FollowPlayerAspect(Entity381* ent, AspectType aspectType)
        : Aspect(ent, aspectType)
{
    m_FollowRadius = 0;
    m_FollowSpeed = 50;
    m_PlayerEntity = entity->m_Engine->m_EntityMgr->GetPlayerByName("player1");
}

FollowPlayerAspect::~FollowPlayerAspect()
{
    
}

void FollowPlayerAspect::Tick(float dt)
{
    if(m_PlayerEntity != NULL)
    {        
        if(std::abs((entity->m_Position - m_PlayerEntity->m_Position).length()) <= m_FollowRadius)
        {
            Ogre::Vector3 targetLocation = m_PlayerEntity->m_Position;
            Ogre::Vector3 diff = targetLocation - entity->m_Position;
            entity->m_Position += (diff.normalisedCopy() * dt * 100);
            //float angle = atan2(diff.z, diff.x);
            //entity->m_SceneNode->pitch(Ogre::Radian(angle));
            //entity->m_SceneNode->translate(diff/2);
            //entity->m_SceneNode->lookAt(m_PlayerEntity->m_Position, Ogre::Node::TS_WORLD);
            
            //entity->m_SceneNode->translate(0, 0, -m_FollowSpeed, Ogre::Node::TS_LOCAL);
            
            /*
            entity->m_Velocity.x = Ogre::Math::Cos(Ogre::Degree(-entity->m_SceneNode->getOrientation().getYaw()))
                                       * Ogre::Math::Cos(Ogre::Degree(entity->m_SceneNode->getOrientation().getPitch()))
                                       * m_FollowSpeed;
            entity->m_Velocity.z = Ogre::Math::Sin(Ogre::Degree(-entity->m_SceneNode->getOrientation().getYaw()))
                                       * Ogre::Math::Cos(Ogre::Degree(entity->m_SceneNode->getOrientation().getPitch()))
                                       * m_FollowSpeed;
            entity->m_Velocity.y = Ogre::Math::Sin(Ogre::Degree(entity->m_SceneNode->getOrientation().getPitch()))
                                       * m_FollowSpeed;
            */
            /*
            entity->m_Position = entity->m_Position + entity->m_Velocity * dt;
            
            
            */
            entity->m_SceneNode->setPosition(entity->m_Position);
           
        }
    }
    else
    {
        std::cerr << "Player not found in FollowPlayerAspect for entity: " << entity->m_Name << std::endl;
    }
}


