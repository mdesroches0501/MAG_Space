/*
 * Mgr.h
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#ifndef MGR_H_
#define MGR_H_

#include <string>

class Engine;

class Mgr
{
public:
    Mgr(Engine *engine);
    virtual ~Mgr();

    Engine *m_Engine;

    virtual void Init();
    virtual void LoadLevel(std::string levelLocation);
    virtual void Tick(float dt);
    virtual void Stop();

};

#endif /* MGR_H_ */
