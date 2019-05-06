/**
 *  @file   PickUpEntity381.h
 *	
 *  @date   May 5, 2019
 *  @author Michael DesRoches, Alexander Pasinski, and Gianni Pinneri
 *
 *  @brief  
 */

#ifndef INC_ENTITIES_PICKUPENTITY381_H_
#define INC_ENTITIES_PICKUPENTITY381_H_


#include <map>
#include <boost/bimap.hpp>

#include <OgreVector3.h>
#include <OISKeyboard.h>

#include <Entities/Entity381.h>
#include <Engine.h>
#include <Utilities/Actions.h>

class PickUpEntity381 : public Entity381
{
public:
    PickUpEntity381(Engine *engine, Ogre::Vector3 pos, std::string name);
    virtual ~PickUpEntity381();
    
    void Init();
};


#endif /* INC_ENTITIES_PICKUPENTITY381_H_ */
