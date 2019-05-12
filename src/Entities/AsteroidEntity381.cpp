/*
 * AsteroidEntity.cpp
 *
 *  Created on: Apr 28, 2019
 *      Author: michael
 */



#include <Entities/AsteroidEntity381.h>
#include <Aspects/ColliderAspect.h>
#include <Aspects/FollowPlayer.h>

AsteroidEntity381::AsteroidEntity381(Engine *engine, Ogre::Vector3 pos, std::string name)
        : FlyingEntity381(engine, pos, name)
{
    m_Meshfilename = "Asteroid.mesh";
    m_EntityType = ASTEROID_TYPE;

    m_Acceleration = 50;
    m_YawRate = m_PitchRate = 100.0f;
    m_RollRate = 60.0f;

    m_MinSpeed = 0;
    m_MaxSpeed = 0;

    m_Altitude = m_Position.y;
    m_MaxAltitude = 1000;
    m_MinAltitude = 10;
    
    AsteroidCollider* asteroidCollider = new AsteroidCollider(this, COLLIDER);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::COLLIDER, (Aspect*)asteroidCollider)); 
    
    FollowPlayerAspect* followPlayerAspect = new FollowPlayerAspect(this, FOLLOW_PLAYER);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::FOLLOW_PLAYER, (Aspect*)followPlayerAspect)); 

    std::cout << "Created: " << this->m_Name << std::endl;
}

AsteroidEntity381::~AsteroidEntity381()
{
    
}

void AsteroidEntity381::Init()
{
    Entity381::Init();
    m_SceneNode->scale(0.04, 0.04, 0.04);
}
