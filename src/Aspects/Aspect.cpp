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
    entity->m_SceneNode->setPosition(entity->m_Position); //now ogre should render the sceneNode at the new position...

    entity->m_SceneNode->resetOrientation(); // rotation is cumulative, so set current xyz-rotation to 0
    /*Ogre::Matrix3 localAxes = entity->m_SceneNode->getLocalAxes();
    Ogre::Quaternion xAxis(Ogre::Degree(entity->m_Pitch), Ogre::Vector3::UNIT_X);
    Ogre::Quaternion yAxis(Ogre::Degree(-entity->m_Yaw), Ogre::Vector3::UNIT_Y);
    Ogre::Quaternion zAxis(Ogre::Degree(entity->m_Roll), Ogre::Vector3::UNIT_Z);
    Ogre::Quaternion rotation = xAxis * yAxis * zAxis;
    entity->m_SceneNode->rotate(rotation, Ogre::Node::TS_WORLD);
    */
    
    entity->m_SceneNode->yaw(Ogre::Degree(-entity->m_Yaw)); //ogre's yaw is in the direction of -z
    entity->m_SceneNode->pitch(Ogre::Degree(entity->m_Roll));
    entity->m_SceneNode->roll(Ogre::Degree(entity->m_Pitch));
    

}
