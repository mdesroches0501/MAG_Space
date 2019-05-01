/**
 *  @file   ColliderAspect.cpp
 *	
 *  @date   Apr 28, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */


#include <Aspects/ColliderAspect.h>
#include <Entities/Entity381.h>
#include <Managers/EntityMgr.h>

ColliderAspect::ColliderAspect(Entity381* ent, AspectType aspectType)
        : Aspect(ent, aspectType)
{
    m_CollidedEntity = NULL;
    m_CollisionRadius = 20;
}

ColliderAspect::~ColliderAspect()
{
    
}



void ColliderAspect::Tick(float dt)
{
    for(auto iter = entity->m_Engine->m_EntityMgr->m_Entities.begin(); iter < entity->m_Engine->m_EntityMgr->m_Entities.end(); iter++){
        if(*iter != entity && std::abs(((*iter)->m_Position - entity->m_Position).length()) < m_CollisionRadius)
        {
            ColliderAspect* collidedAspect = (ColliderAspect*) (*iter)->m_Aspects.find(COLLIDER)->second;
            collidedAspect->m_CollidedEntity = entity;
            collidedAspect->Collided();

            m_CollidedEntity = (*iter);
            Collided();
            
            break;
        }
    }
}



PlayerCollider::PlayerCollider(PlayerEntity381* ent, AspectType aspectType)
        : ColliderAspect(ent, aspectType)
{
    
}

PlayerCollider::~PlayerCollider()
{
    
}

void PlayerCollider::Collided()
{
    EntityTypes entType = m_CollidedEntity->m_EntityType;
    PlayerEntity381* player = (PlayerEntity381*) entity;
    switch(entType)
    {
    case ASTEROID_TYPE:
        player->m_Health -= 50;
        if(player->m_Health <= 0)
        {
            entity->m_DeleteNextTick = true;
            std::cout << entity->m_Name << " Deleted" << std::endl;
        }
        std::cout << entity->m_Name + " collided with " + m_CollidedEntity->m_Name << std::endl;
        break;
    case PLAYER_TYPE:
        std::cout << entity->m_Name + " collided with " + m_CollidedEntity->m_Name << std::endl;
        break;
    case ENEMY_TYPE:
        std::cout << entity->m_Name + " collided with " + m_CollidedEntity->m_Name << std::endl;
        break;
    case PICKUP_TYPE:
        std::cout << entity->m_Name + " collided with " + m_CollidedEntity->m_Name << std::endl;
        break;
    default:
        break;
    }
}



AsteroidCollider::AsteroidCollider(AsteroidEntity381* ent, AspectType aspectType)
        : ColliderAspect(ent, aspectType)
{
    
}

AsteroidCollider::~AsteroidCollider()
{
    
}

void AsteroidCollider::Collided()
{
    EntityTypes entType = m_CollidedEntity->m_EntityType;
    switch(entType)
    {
    case ASTEROID_TYPE:
        std::cout << entity->m_Name + " collided with " + m_CollidedEntity->m_Name << std::endl;
        break;
    case PLAYER_TYPE:
        std::cout << entity->m_Name + " collided with " + m_CollidedEntity->m_Name << std::endl;
        entity->m_DeleteNextTick = true;
        std::cout << entity->m_Name << "Deleted" << std::endl;
        break;
    case ENEMY_TYPE:
        std::cout << entity->m_Name + " collided with " + m_CollidedEntity->m_Name << std::endl;
        break;
    case PICKUP_TYPE:
        std::cout << entity->m_Name + " collided with " + m_CollidedEntity->m_Name << std::endl;
        break;
    default:
        break;
    }
}
