/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <Engine.h>
#include <Managers/EntityMgr.h>
#include <Managers/SoundMgr.h>
#include <Managers/InputMgr.h>
#include <Managers/GameMgr.h>
#include <Managers/GfxMgr.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	m_Count = 0;
}

EntityMgr::~EntityMgr(){

}

void EntityMgr::Init()
{
    entityTypesMap.insert(std::pair<std::string, EntityTypes>("player", PLAYER_TYPE));
    entityTypesMap.insert(std::pair<std::string, EntityTypes>("enemy", ENEMY_TYPE));
    entityTypesMap.insert(std::pair<std::string, EntityTypes>("asteroid", ASTEROID_TYPE));
    entityTypesMap.insert(std::pair<std::string, EntityTypes>("pickup", PICKUP_TYPE));
}

void EntityMgr::LoadLevel(std::string levelLocation)
{
    std::ifstream levelEntitiesFile;
    levelEntitiesFile.open(levelLocation + "entities.mag");
    if(levelEntitiesFile.is_open() && m_Engine->m_KeepRunning)
    {
        std::string line;
        while(getline(levelEntitiesFile, line))
        {
            boost::algorithm::to_lower(line);
            if(line == "start")
            {
                CreateEntityFromFile(levelEntitiesFile);
            }
        }
        
        levelEntitiesFile.close();
    }
    else
    {
        m_Engine->m_KeepRunning = false;
    }
}

void EntityMgr::Tick(float dt){
    for(auto iter = m_Entities.begin(); iter != m_Entities.end(); iter++){
        if((*iter)->m_DeleteNextTick)
        {
            std::cout << "Entity: " << (*iter)->m_Name << " should be dying right now" << std::endl;
            auto tempPtr = *iter;
            iter = m_Entities.erase(iter);
            delete tempPtr;
            iter--; // iter was set to entity after erased entity. Must decrement so increment at end of loop does not skip new entity.
        }
        else
        {            
            (*iter)->Tick(dt);
        }
    }
}

void EntityMgr::Stop()
{
    
}


PlayerEntity381* EntityMgr::GetPlayerByName(std::string name)
{
    auto iter = m_Entities.begin();
    for(; iter != m_Entities.end(); iter++)
    {
        if((*iter)->m_Name == name)
        {
            return (PlayerEntity381*)*iter;
        }
    }
    
    return NULL;
}


void EntityMgr::CreateEntityFromFile(std::ifstream& entityFile)
{
    std::string line;
    std::string name;
    EntityTypes entType;
    Ogre::Vector3 pos;
    
    EntityRequirements required;
    
    while(getline(entityFile, line))
    {
        boost::algorithm::to_lower(line);
        if(line == "end")
        {
            break;
        }
        
        std::vector<std::string> tokens;
        boost::algorithm::split(tokens, line, boost::is_any_of(" "));
        
        if(tokens.size() >= 2 && tokens[0] == "entitytype")
        {
            auto iter = entityTypesMap.find(tokens[1]);
            entType = iter->second;
            required.hasType = true;
        }
        else if(tokens.size() >= 4 && tokens[0] == "coordinates")
        {
            pos = Ogre::Vector3(std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]));
            required.hasPos = true;
        }
        else if(tokens.size() >= 2 && tokens[0] == "name")
        {
            name = tokens[1];
            required.hasName = true;
        }
    }
    
    if(required.RequirementsMet())
    {
        CreateEntityOfTypeAtPosition(entType, pos, name);
    }
}

void EntityMgr::CreateEntityOfTypeAtPosition(EntityTypes entType, Ogre::Vector3 pos, std::string name){

	Entity381* ent;
    
    switch(entType)
    {
    case PLAYER_TYPE:
        ent = (Entity381*)(new PlayerEntity381(m_Engine, pos, name));
        break;

    case ASTEROID_TYPE:
    	ent = (Entity381*)(new AsteroidEntity381(m_Engine, pos, name));
    	break;
    }
    
    m_Count++;
    
    ent->Init();
    
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
	m_Entities.push_back(ent);

}
