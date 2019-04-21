/**
 *  @file   FlyingEntity381.h
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#ifndef FLYINGENTITY381_H_
#define FLYINGENTITY381_H_

#include <OgreVector3.h>

#include <Entities/Entity381.h>
#include <Engine.h>

class FlyingEntity381 : public Entity381
{
public:
    FlyingEntity381(Engine *engine, Ogre::Vector3 pos, std::string name);
    virtual ~FlyingEntity381();

    float m_Acceleration, m_YawRate, m_RollRate, m_PitchRate;
    float m_DesiredSpeed, m_DesiredYaw, m_DesiredRoll, m_DesiredPitch;
    float m_Speed;
    float m_MinSpeed, m_MaxSpeed;
    
    float m_MinAltitude, m_MaxAltitude;
    float m_Altitude;
};

#endif /* FLYINGENTITY381_H_ */
