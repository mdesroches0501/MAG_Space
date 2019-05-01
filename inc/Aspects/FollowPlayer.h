/**
 *  @file   FollowPlayer.h
 *	
 *  @date   May 1, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#ifndef INC_ASPECTS_FOLLOWPLAYER_H_
#define INC_ASPECTS_FOLLOWPLAYER_H_

#include <Entities/PlayerEntity381.h>
#include <Entities/AsteroidEntity381.h>
#include <Aspects/Aspect.h>
#include <Managers/EntityMgr.h>

class FollowPlayerAspect : public Aspect
{
public:
    FollowPlayerAspect(Entity381* ent, AspectType aspectType);
    ~FollowPlayerAspect();

    void Tick(float dt);
    
    PlayerEntity381* m_PlayerEntity;
    float m_FollowRadius;
    float m_FollowSpeed;
};



#endif /* INC_ASPECTS_FOLLOWPLAYER_H_ */
