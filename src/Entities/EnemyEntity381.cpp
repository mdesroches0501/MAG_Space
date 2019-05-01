/**
 *  @file   EnemyEntity381.cpp
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#include <Aspects/UnitAI.h>
#include <Entities/EnemyEntity381.h>

EnemyEntity381::EnemyEntity381(Engine *engine, Ogre::Vector3 pos, std::string name)
        : FlyingEntity381(engine, pos, name)
{
    m_Meshfilename = "banshee.mesh";
    m_EntityType = ENEMY_TYPE;

    m_Acceleration = 10.0f;
    m_YawRate = 10.0f;

    m_MinSpeed = 0;
    m_MaxSpeed = 100;

    m_Altitude = 20;
    m_Position.y = 20;
    m_MaxAltitude = 1000;
    m_MinAltitude = 10;
    std::cout << "Created: " << this->m_Name << std::endl;
    
    UnitAI * unitAI = new UnitAI(this, UNIT_AI);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::UNIT_AI, (Aspect*)unitAI));
}

EnemyEntity381::~EnemyEntity381()
{

}



void EnemyEntity381::Init()
{
    FlyingEntity381::Init();
}
