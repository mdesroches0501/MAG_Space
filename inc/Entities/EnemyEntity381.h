/**
 *  @file   EnemyEntity381.h
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#ifndef ENEMYENTITY381_H_
#define ENEMYENTITY381_H_

#include <map>

#include <OgreVector3.h>
#include <OISKeyboard.h>

#include <Entities/FlyingEntity381.h>
#include <Engine.h>

class EnemyEntity381 : public FlyingEntity381
{
public:
    EnemyEntity381(Engine *engine, Ogre::Vector3 pos, int ident);
    virtual ~EnemyEntity381();
};

#endif /* FLYINGENTITY381_H_ */
