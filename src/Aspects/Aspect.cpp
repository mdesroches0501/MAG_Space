/*
 * Aspect.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <Aspects/Aspect.h>
#include <Entities/Entity381.h>  //Aspect includes Entity381.h

Aspect::Aspect(Entity381 *ent, AspectType aType)
{
    entity = ent;
    aspectType = aType;
}

Aspect::~Aspect()
{

}

void Aspect::Tick(float dt)
{

}

Renderable::Renderable(Entity381* ent, AspectType aType)
        : Aspect(ent, aType)
{

}

Renderable::~Renderable()
{

}

void Renderable::Tick(float dt)
{
    //Ogre::Vector3 translateVec = entity->m_Position - entity->m_OldPosition;
    
    //entity->m_SceneNode->translate(translateVec, Ogre::Node::TS_LOCAL); //now ogre should render the sceneNode at the new position...
    entity->m_SceneNode->setPosition(entity->m_Position);
    //entity->m_SceneNode->resetOrientation(); // rotation is cumulative, so set current xyz-rotation to 0
    //entity->m_MeshNode->resetOrientation();
    /*Ogre::Matrix3 localAxes = entity->m_SceneNode->getLocalAxes();
    Ogre::Quaternion xAxis(Ogre::Degree(entity->m_Pitch), Ogre::Vector3::UNIT_X);
    Ogre::Quaternion yAxis(Ogre::Degree(-entity->m_Yaw), Ogre::Vector3::UNIT_Y);
    Ogre::Quaternion zAxis(Ogre::Degree(entity->m_Roll), Ogre::Vector3::UNIT_Z);
    Ogre::Quaternion rotation = xAxis * yAxis * zAxis;
    entity->m_SceneNode->rotate(rotation, Ogre::Node::TS_WORLD);
    */
    
    //Ogre::Quaternion()
    
    /*float pitchChange = entity->m_Pitch - entity->m_OldPitch;
    float yawChange = entity->m_Yaw - entity->m_OldYaw;
    float rollChange = entity->m_Roll - entity->m_OldRoll;
    
    entity->m_SceneNode->yaw(Ogre::Degree(-yawChange)); //ogre's yaw is in the direction of -z
    entity->m_SceneNode->pitch(Ogre::Degree(rollChange));
    entity->m_SceneNode->roll(Ogre::Degree(pitchChange));
    
    entity->m_OldPitch = entity->m_Pitch;
    entity->m_OldYaw = entity->m_Yaw;
    entity->m_OldRoll = entity->m_Roll;
    */
    
    //entity->m_MeshNode->yaw(Ogre::Degree(-entity->m_Yaw));
    //entity->m_MeshNode->pitch(Ogre::Degree(entity->m_Roll), Ogre::Node::TS_WORLD);
    //entity->m_SceneNode->roll(Ogre::Degree(entity->m_Pitch), Ogre::Node::TS_WORLD);
    
}
