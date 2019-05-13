/*
 * AsteroidEntity.cpp
 *
 *  Created on: Apr 28, 2019
 *      Author: michael
 */



#include <Entities/PickUpEntity381.h>
#include <Aspects/ColliderAspect.h>

PickUpEntity381::PickUpEntity381(Engine *engine, Ogre::Vector3 pos, std::string name)
        : Entity381(engine, pos, name)
{
    m_Meshfilename = "Barrel.mesh";
    m_EntityType = PICKUP_TYPE;
    
    PickUpCollider* pickupCollider = new PickUpCollider(this, COLLIDER);
    m_Aspects.insert(std::pair<AspectType, Aspect*>(AspectType::COLLIDER, (Aspect*)pickupCollider));

    std::cout << "Created: " << this->m_Name << std::endl;
}

PickUpEntity381::~PickUpEntity381()
{
    
}

void PickUpEntity381::Init()
{
    Entity381::Init();
    //m_SceneNode->scale(1.4, 1.4, 1.4);
    m_SceneNode->scale(2, 2, 2);
}
