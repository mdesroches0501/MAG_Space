/*
 * AsteroidEntity.cpp
 *
 *  Created on: Apr 28, 2019
 *      Author: michael
 */



#include <Entities/AsteroidEntity381.h>
#include <Aspects/InputAspect.h>

AsteroidEntity381::AsteroidEntity381(Engine *engine, Ogre::Vector3 pos, std::string name)
        : FlyingEntity381(engine, pos, name)
{
    m_Meshfilename = "sphere.mesh";
    m_EntityType = ASTEROID_TYPE;

    m_Acceleration = 50;
    m_YawRate = m_PitchRate = 100.0f;
    m_RollRate = 60.0f;

    m_MinSpeed = 0;
    m_MaxSpeed = 0;

    m_Altitude = m_Position.y;
    m_MaxAltitude = 1000;
    m_MinAltitude = 10;

    m_Health = m_MaxHealth = 100;

 /*   InputAspect* inputAspect = new InputAspect(this, INPUT);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::INPUT, (Aspect*)inputAspect)); */

    std::cout << "Created: " << this->m_Name << std::endl;
}

AsteroidEntity381::~AsteroidEntity381()
{

}

