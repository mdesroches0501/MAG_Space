/*
 * Physics3D.cpp
 *
 *  Created on: Mar 7, 2018
 *      Author: sushil
 */

#include <Aspects/FlyingPhysics.h>
#include <Entities/Entity381.h>
#include <Utilities/Utils.h>

FlyingPhysics::FlyingPhysics(FlyingEntity381 * ent, AspectType aType)
        : Aspect((Entity381*)ent, aType)
{
    // TODO Auto-generated constructor stub
    flyingEntity = ent;
}

FlyingPhysics::~FlyingPhysics()
{
    // TODO Auto-generated destructor stub
}

void FlyingPhysics::Tick(float dt)
{
    //first, get new speed from desired speed
    flyingEntity->m_DesiredSpeed = Clamp(flyingEntity->m_MinSpeed, flyingEntity->m_MaxSpeed, flyingEntity->m_DesiredSpeed);
    if(flyingEntity->m_DesiredSpeed > flyingEntity->m_Speed)
    {
        flyingEntity->m_Speed += flyingEntity->m_Acceleration * dt;
    }
    else if(flyingEntity->m_DesiredSpeed < flyingEntity->m_Speed)
    {
        flyingEntity->m_Speed -= flyingEntity->m_Acceleration * dt;
    }
    flyingEntity->m_Speed = Clamp(flyingEntity->m_MinSpeed, flyingEntity->m_MaxSpeed, flyingEntity->m_Speed);

    //When I try to go from a yaw of 350 to a yaw of 10,
    //I should turn to right/starboard not keep decreasing heading till I get to 10 because it is 20 degrees from -10 (350) to +10 by turning to port/right and
    //340 degrees from 350 (-10) to 10 by turning left/port
    
    //UpdateRotationAxis(flyingEntity->m_Pitch, flyingEntity->m_DesiredPitch, flyingEntity->m_PitchRate, dt);
    //UpdateRotationAxis(flyingEntity->m_Yaw, flyingEntity->m_DesiredYaw, flyingEntity->m_YawRate, dt);
    //std::cout << "BEFORE: DesiredRoll: " << flyingEntity->m_DesiredRoll << " Roll: " << flyingEntity->m_Roll << std::endl;
    UpdateRotationAxis(flyingEntity->m_Roll, flyingEntity->m_DesiredRoll, flyingEntity->m_RollRate, dt);
    //std::cout << "AFTER: DesiredRoll: " << flyingEntity->m_DesiredRoll << " Roll: " << flyingEntity->m_Roll << std::endl;

    //Now do the trig
    /*
    Ogre::Vector3 xForward = flyingEntity->m_SceneNode->getOrientation() * Ogre::Vector3(1, 0, 0);
    Ogre::Vector3 yForward = flyingEntity->m_SceneNode->getOrientation() * Ogre::Vector3(0, 1, 0);
    Ogre::Vector3 zForward = flyingEntity->m_SceneNode->getOrientation() * Ogre::Vector3(0, 0, 1);
    flyingEntity->m_Velocity.x = xForward.x * flyingEntity->m_Speed;
    flyingEntity->m_Velocity.y = yForward.y * flyingEntity->m_Speed;
    flyingEntity->m_Velocity.z = zForward.z * flyingEntity->m_Speed;
    */
    
    flyingEntity->m_Velocity.x = Ogre::Math::Cos(Ogre::Degree(flyingEntity->m_Yaw))
                               * Ogre::Math::Cos(Ogre::Degree(flyingEntity->m_Pitch))
                               * flyingEntity->m_Speed;
    flyingEntity->m_Velocity.z = Ogre::Math::Sin(Ogre::Degree(flyingEntity->m_Yaw))
                               * Ogre::Math::Cos(Ogre::Degree(flyingEntity->m_Pitch))
                               * flyingEntity->m_Speed;
    flyingEntity->m_Velocity.y = Ogre::Math::Sin(Ogre::Degree(flyingEntity->m_Pitch))
                               * flyingEntity->m_Speed;
    
    if(flyingEntity->m_Name == "none")
    {
        std::cout << "x: " << flyingEntity->m_Velocity.x << " y: " << flyingEntity->m_Velocity.y << " z: " << flyingEntity->m_Velocity.z << std::endl;
    }
    
    //This does not change!
    flyingEntity->m_OldPosition = flyingEntity->m_Position;
    flyingEntity->m_Position = flyingEntity->m_Position + flyingEntity->m_Velocity * dt;

    //flyingEntity->m_Altitude = Clamp(flyingEntity->m_MinAltitude, flyingEntity->m_MaxAltitude, flyingEntity->m_Altitude);
    //flyingEntity->m_Position.y = flyingEntity->m_Altitude;
}

void FlyingPhysics::UpdateRotationAxis(float& currentValue, float& desiredValue, float& rateOfChange, float dt)
{
    if(desiredValue > currentValue)
    {
        if(desiredValue - currentValue > 180)
            currentValue -= rateOfChange * dt;
        else
            currentValue += rateOfChange * dt;
    }
    else if(desiredValue < currentValue)
    {
        if(desiredValue - currentValue < -180)
            currentValue += rateOfChange * dt;
        else
            currentValue -= rateOfChange * dt;
        ;
    }
    //currentValue = FixAngle(currentValue);
}
