/**
 *  @file   ColliderAspect.h
 *	
 *  @date   Apr 28, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#ifndef INC_ASPECTS_COLLIDERASPECT_H_
#define INC_ASPECTS_COLLIDERASPECT_H_

#include <Entities/PlayerEntity381.h>
#include <Entities/AsteroidEntity381.h>
#include <Entities/PickUpEntity381.h>
#include <Aspects/Aspect.h>
#include <Utilities/Types381.h>

class ColliderAspect : public Aspect
{
public:
    ColliderAspect(Entity381* ent, AspectType aspectType);
    ~ColliderAspect();

    void Tick(float dt);
    
    virtual void Collided() = 0;
    
    Entity381* m_CollidedEntity;
    float m_CollisionRadius;
};


class PlayerCollider : public ColliderAspect
{
public:
    PlayerCollider(PlayerEntity381* ent, AspectType aspectType);
    ~PlayerCollider();
    
    void Collided();
};


class AsteroidCollider : public ColliderAspect
{
public:
    AsteroidCollider(AsteroidEntity381* ent, AspectType aspectType);
    ~AsteroidCollider();
    
    void Collided();
};


class PickUpCollider : public ColliderAspect
{
public:
    PickUpCollider(PickUpEntity381* ent, AspectType aspectType);
    ~PickUpCollider();
    
    void Collided();
};


#endif /* INC_ASPECTS_COLLIDERASPECT_H_ */
