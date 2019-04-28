/*
 * Command.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: Alexander Pasinski
 */

#include <Utilities/Command.h>


Command::Command(Entity381* ent, COMMAND_TYPE ct)
{
    commandType = ct;
    entity = ent;
}

Command::~Command()
{
    
}



MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 location, COMMAND_TYPE type)
    : Command(ent, type)
{
    entity = ent;
    MOVE_DISTANCE_THRESHOLD = std::numeric_limits<float>::infinity();
    targetLocation = location;
}

MoveTo::~MoveTo()
{
    
}

void MoveTo::init()
{
    std::cout << "MOVE TO!" << std::endl;
}

void MoveTo::tick(float dt)
{
    Ogre::Vector3 diff = targetLocation - entity->m_Position;
    float angle = atan2(diff.z, diff.x);
    //entity->m_DesiredHeading = FixAngle(Ogre::Degree(Ogre::Radian(angle)).valueDegrees());
    //entity->m_DesiredSpeed = entity->m_MaxSpeed;
}

bool MoveTo::done()
{
    if(Ogre::Math::Abs(targetLocation.x - entity->m_Position.x) <= 20 && Ogre::Math::Abs(targetLocation.z - entity->m_Position.z) <= 20)
    {
        //entity->m_DesiredSpeed = entity->m_MinSpeed;
        return true;
    }
    else
    {
        return false;
    }
}



Follow::Follow(Entity381* ent, Ogre::Vector3 location, Entity381* targetEnt)
    : MoveTo(ent, location, FOLLOW)
{
    entity = ent;
    targetEntity = targetEnt;
    MOVE_DISTANCE_THRESHOLD = std::numeric_limits<float>::infinity();
    targetLocation = location;
}

Follow::~Follow()
{
    
}

void Follow::init()
{
    std::cout << "FOLLOW!" << std::endl;
}

void Follow::tick(float dt)
{
    targetLocation = targetEntity->m_Position;
    Ogre::Vector3 diff = targetLocation - entity->m_Position;
    float angle = atan2(diff.z, diff.x);
    //entity->m_DesiredHeading = FixAngle(Ogre::Degree(Ogre::Radian(angle)).valueDegrees());
    //entity->m_DesiredSpeed = entity->m_MaxSpeed;
}

bool Follow::done()
{
    if(Ogre::Math::Abs(targetLocation.x - entity->m_Position.x) <= 20 && Ogre::Math::Abs(targetLocation.z - entity->m_Position.z) <= 20)
    {
        //entity->m_DesiredSpeed = entity->m_MinSpeed;
        return true;
    }
    else
    {
        return false;
    }
}
