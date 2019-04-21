#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>

#include <Managers/Mgr.h>
#include <Entities/Entity381.h>
#include <Entities/FlyingEntity381.h>
#include <Utilities/Types381.h>

class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  void CreateEntityOfTypeAtPosition(EntityTypes type, Ogre::Vector3 pos);

  void Tick(float dt);

private:
  void CreateEntity(std::string meshfilename, Ogre::Vector3 pos);

  std::vector<Entity381*> m_Entities;
  int m_Count;

};

#endif // #ifndef __EntityMgr_h_
