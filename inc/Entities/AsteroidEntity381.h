/*
 * AsteroidEntity381.h
 *
 *  Created on: Apr 28, 2019
 *      Author: michael
 */

#ifndef INC_ENTITIES_ASTEROIDENTITY381_H_
#define INC_ENTITIES_ASTEROIDENTITY381_H_


#include <map>
#include <boost/bimap.hpp>

#include <OgreVector3.h>
#include <OISKeyboard.h>

#include <Entities/FlyingEntity381.h>
#include <Engine.h>
#include <Utilities/Actions.h>

class AsteroidEntity381 : public FlyingEntity381
{
public:
    AsteroidEntity381(Engine *engine, Ogre::Vector3 pos, std::string name);
    virtual ~AsteroidEntity381();

    boost::bimap<OIS::KeyCode, Actions> m_MappedInputs;

    unsigned int m_Health;
    unsigned int m_MaxHealth;
};


#endif /* INC_ENTITIES_ASTEROIDENTITY381_H_ */
