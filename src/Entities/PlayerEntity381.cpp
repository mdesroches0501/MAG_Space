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

PlayerEntity381::PlayerEntity381(Engine *engine, Ogre::Vector3 pos, int ident)
        : FlyingEntity381(engine, pos, ident)
{
    m_Meshfilename = "banshee.mesh";
    m_EntityType = PLAYER_TYPE;

    m_Acceleration = m_YawRate = m_PitchRate = m_RollRate = 10.0f;

    m_MinSpeed = 20;
    m_MaxSpeed = 100;

    m_Altitude = 20;
    m_Position.y = 20;
    m_MaxAltitude = 1000;
    m_MinAltitude = 10;
    
    InputAspect* inputAspect = new InputAspect(this, INPUT);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::INPUT, (Aspect*)inputAspect));
    
    std::cout << "Created: " << this->m_Name << std::endl;
}

PlayerEntity381::~PlayerEntity381()
{
    
}
