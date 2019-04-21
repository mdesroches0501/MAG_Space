/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <Engine.h>
#include <Managers/EntityMgr.h>
#include <Managers/InputMgr.h>
#include <Managers/GameMgr.h>
#include <Managers/GfxMgr.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	m_Count = 0;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::Tick(float dt){
    for(int i = 0; i < m_Count; i++){
        m_Entities[i]->Tick(dt);
    }
}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos){

	Entity381 * ent;
	/*switch(entType){
	case DDG51Type:
		//CreateDDG51(pos);
		ent = (Entity381 *) ( new DDG51(engine, pos, count++));
		break;
	case CarrierType:
//		CreateCarrier(pos);
		ent = (Entity381 *) (new Carrier(engine, pos, count++));
		break;
	case SpeedBoatType:
		//CreateSpeedBoat(pos);
		ent =  (Entity381 *) (new SpeedBoat(engine, pos, count++));
		break;
	case FrigateType:
		//CreateFrigate(pos);
		ent = (Entity381 *) (new Frigate(engine, pos, count++));
		break;
	case AlienType:
		//CreateAlien(pos);
		ent = (Entity381 *) (new Alien(engine, pos, count++));
		break;
	case BansheeType:
		ent = (Entity381 *) ((FlyingEntity381*) (new Banshee(engine, pos, count++)));
		break;
	default:
		ent = (Entity381*) (new DDG51(engine, pos, count++));//CreateEntity("robot.mesh", pos);
		break;
	}*/
	ent->Init();
	m_Entities.push_back(ent);

}
