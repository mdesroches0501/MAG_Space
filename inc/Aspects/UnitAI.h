/*
 * UnitAI.h
 *
 *  Created on: Mar 28, 2018
 *      Author: sushil
 */

#ifndef UNITAI_H_
#define UNITAI_H_

#include <list>
#include <Aspects/Aspect.h>
#include <Utilities/Command.h>

class UnitAI: public Aspect {

public:

	std::list<Command*> commands;

	UnitAI(Entity381* ent, AspectType aspectType);
	~UnitAI();

	void Tick(float dt);
	void SetCommand(Command *c);
	void AddCommand(Command *c);

};





#endif /* UNITAI_H_ */
