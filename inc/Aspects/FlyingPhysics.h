/*
 * Physics3D.h
 *
 *  Created on: Mar 7, 2018
 *      Author: sushil
 */

#ifndef FLYINGPHYSICS_H_
#define FLYINGPHYSICS_H_

#include <Entities/FlyingEntity381.h>
#include <Aspects/Aspect.h>

class FlyingPhysics: public Aspect {
public:
	FlyingPhysics(FlyingEntity381* ent, AspectType aspectType);
	virtual ~FlyingPhysics();
	
	void UpdateRotationAxis(float& currentValue, float& desiredValue, float& rateOfChange, float dt);

	FlyingEntity381 *flyingEntity;

	void Tick(float dt);

};

#endif /* FLYINGPHYSICS_H_ */
