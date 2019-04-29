/**
 *  @file   FlyingEntity381.cpp
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#include <Aspects/FlyingPhysics.h>
#include <Entities/FlyingEntity381.h>

FlyingEntity381::FlyingEntity381(Engine *engine, Ogre::Vector3 pos, std::string name)
        : Entity381(engine, pos, name)
{
    m_MinSpeed = m_MaxSpeed = 0;
    m_MinAltitude = 0;
    m_MaxAltitude = 1000;
        
    m_Altitude = 0;

    m_Acceleration = 0;
    m_YawRate = 0;
    m_RollRate = 0;
    m_PitchRate = 0;
    
    m_DesiredSpeed = m_Speed = 0;
    m_DesiredYaw = m_Yaw = 0;
    m_DesiredPitch = m_Pitch = 0;
    m_DesiredRoll = m_Roll = 0;
    
    FlyingPhysics * flyingPhysics = new FlyingPhysics(this, FLYING_PHYSICS);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::FLYING_PHYSICS, (Aspect*)flyingPhysics));
}

FlyingEntity381::~FlyingEntity381()
{

}


void FlyingEntity381::Init()
{
    Entity381::Init();
}
