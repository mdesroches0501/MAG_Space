/**
 *  @file   PlayerEntity381.h
 *	
 *  @date   Apr 20, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#ifndef PLAYERENTITY381_H_
#define PLAYERENTITY381_H_

#include <map>

#include <OgreVector3.h>
#include <OISKeyboard.h>

#include <Entities/FlyingEntity381.h>
#include <Engine.h>
#include <Utilities/Actions.h>

class PlayerEntity381 : public FlyingEntity381
{
public:
    PlayerEntity381(Engine *engine, Ogre::Vector3 pos, int ident);
    virtual ~PlayerEntity381();

    std::map<OIS::KeyCode, Actions> m_MappedInputs;
};

#endif /* FLYINGENTITY381_H_ */
