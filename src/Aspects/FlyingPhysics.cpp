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
    flyingEntity = ent;
}

FlyingPhysics::~FlyingPhysics()
{
    
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
    
    //UpdateRotationAxis(flyingEntity->m_Roll, flyingEntity->m_DesiredRoll, flyingEntity->m_RollRate, dt);

    //Now do the trig
    /*
    Ogre::Vector3 xForward = flyingEntity->m_SceneNode->getOrientation() * Ogre::Vector3(1, 0, 0);
    Ogre::Vector3 yForward = flyingEntity->m_SceneNode->getOrientation() * Ogre::Vector3(0, 1, 0);
    Ogre::Vector3 zForward = flyingEntity->m_SceneNode->getOrientation() * Ogre::Vector3(0, 0, 1);
    flyingEntity->m_Velocity.x = xForward.x * flyingEntity->m_Speed;
    flyingEntity->m_Velocity.y = yForward.y * flyingEntity->m_Speed;
    flyingEntity->m_Velocity.z = zForward.z * flyingEntity->m_Speed;
    */
    
    
    /*
    flyingEntity->m_Velocity.x = Ogre::Math::Cos(Ogre::Degree(flyingEntity->m_Yaw))
                               * Ogre::Math::Cos(Ogre::Degree(flyingEntity->m_Pitch))
                               * flyingEntity->m_Speed;
    flyingEntity->m_Velocity.z = Ogre::Math::Sin(Ogre::Degree(flyingEntity->m_Yaw))
                               * Ogre::Math::Cos(Ogre::Degree(flyingEntity->m_Pitch))
                               * flyingEntity->m_Speed;
    flyingEntity->m_Velocity.y = Ogre::Math::Sin(Ogre::Degree(flyingEntity->m_Pitch))
                               * flyingEntity->m_Speed;
    */

    //flyingEntity->m_Velocity = flyingEntity->m_Orientation * Ogre::Vector3::UNIT_SCALE  * flyingEntity->m_Speed;
    
    if(flyingEntity->m_Name == "none")
    {
        std::cout << "x: " << flyingEntity->m_Velocity.x << " y: " << flyingEntity->m_Velocity.y << " z: " << flyingEntity->m_Velocity.z << std::endl;
    }
    
    //flyingEntity->m_OldPosition = flyingEntity->m_Position;
    flyingEntity->m_Position = flyingEntity->m_Position + flyingEntity->m_SceneNode->getOrientation().xAxis() * dt * flyingEntity->m_Speed;
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
