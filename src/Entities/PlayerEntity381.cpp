/**
 *  @file   PlayerEntity381.cpp
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#include <Entities/PlayerEntity381.h>
#include <Aspects/InputAspect.h>

PlayerEntity381::PlayerEntity381(Engine *engine, Ogre::Vector3 pos, std::string name)
        : FlyingEntity381(engine, pos, name)
{
    m_Meshfilename = "banshee.mesh";
    m_EntityType = PLAYER_TYPE;

    m_Acceleration = 5.0f;
    m_YawRate = m_PitchRate = 15.0f;
    m_RollRate = 60.0f;

    m_MinSpeed = 20;
    m_MaxSpeed = 100;

    m_Altitude = m_Position.y;
    m_MaxAltitude = 1000;
    m_MinAltitude = 10;
    
    InputAspect* inputAspect = new InputAspect(this, INPUT);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::INPUT, (Aspect*)inputAspect));
    
    std::cout << "Created: " << this->m_Name << std::endl;
}

PlayerEntity381::~PlayerEntity381()
{
    
}
