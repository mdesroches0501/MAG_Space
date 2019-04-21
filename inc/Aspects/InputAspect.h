/*
 * InputAspect.h
 *
 *  Created on: Mar 28, 2018
 *      Author: sushil
 */

#ifndef INPUTASPECT_H_
#define INPUTASPECT_H_

#include <list>
#include <iterator>

#include <OISKeyboard.h>

#include <Utilities/Actions.h>
#include <Entities/PlayerEntity381.h>
#include <Aspects/Aspect.h>

class InputAspect : public Aspect
{
public:
    InputAspect(PlayerEntity381* ent, AspectType aspectType);
    ~InputAspect();
    
    void Tick(float dt);
    
    OIS::Keyboard* m_KeyboardReference;
    PlayerEntity381* m_PlayerEntity;
    
    float m_KeyboardTimer;
    const static float KEY_TIME;
    
    bool m_RollLeftToggle, m_RollRightToggle;
};

#endif /* INPUTASPECT_H_ */
