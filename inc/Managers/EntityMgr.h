#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <Managers/Mgr.h>
#include <Entities/Entity381.h>
#include <Entities/FlyingEntity381.h>
#include <Entities/PlayerEntity381.h>
//#include <Entities/EnemyEntity381.h>
#include <Utilities/Types381.h>
#include <Entities/AsteroidEntity381.h>


struct EntityRequirements
{
    bool hasType = false;
    bool hasPos = false;
    bool hasName = false;
    
    bool RequirementsMet()
    {
        return hasType && hasPos && hasName;
    }
};


class EntityMgr : public Mgr
{
public:
    EntityMgr(Engine *engine);
    virtual ~EntityMgr();

    void Init();
    void LoadLevel(std::string levelLocation);
    void Tick(float dt);
    void Stop();
    
    PlayerEntity381* GetPlayerByName(std::string name);

    void CreateEntityFromFile(std::ifstream& entityFile);
    void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos, std::string name);

    std::vector<Entity381*> m_Entities;

private:
    void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);
    
    std::map<std::string, EntityTypes> entityTypesMap;
    
    int m_Count;

};

#endif // #ifndef __EntityMgr_h_
