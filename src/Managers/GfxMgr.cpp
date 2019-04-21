/*
 * GfxMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */

#include <iostream>

#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
#include <OgrePlane.h>
#include <OgreMeshManager.h>

#include <Engine.h>
#include <Managers/GfxMgr.h>
#include <Managers/EntityMgr.h>
#include <Managers/SoundMgr.h>
#include <Managers/InputMgr.h>
#include <Managers/GameMgr.h>

GfxMgr::GfxMgr(Engine *engine)
        : Mgr(engine), m_OceanSurface(Ogre::Vector3::UNIT_Y, 0)
{

    m_Root = 0;
    m_ResourcesCfg = Ogre::StringUtil::BLANK;
    m_PluginsCfg = Ogre::StringUtil::BLANK;
    m_Window = 0;
    m_SceneMgr = 0;
    m_Camera = 0;
    m_FirstPerson = false;
    m_OceanHeight = 0;
    //oceanSurface(Ogre::Vector3::UNIT_Y, 0);
}

GfxMgr::~GfxMgr()
{

    Ogre::WindowEventUtilities::removeWindowEventListener(m_Window, this);
    windowClosed(m_Window);
    delete m_Root;
}



void GfxMgr::Init()
{
#ifdef _DEBUG
    m_ResourcesCfg = "resources_d.cfg";
    m_PluginsCfg = "plugins_d.cfg";
#else
    m_ResourcesCfg = "resources.cfg";
    m_PluginsCfg = "plugins.cfg";
#endif

    m_Root = new Ogre::Root(m_PluginsCfg);

    Ogre::ConfigFile cf;
    cf.load(m_ResourcesCfg);

    Ogre::String name, locType;
    Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

    while(secIt.hasMoreElements())
    {
        Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator it;

        for(it = settings->begin(); it != settings->end(); ++it)
        {
            locType = it->first;
            name = it->second;

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
        }
    }

    if(!(m_Root->restoreConfig() || m_Root->showConfigDialog()))
        std::cerr << "Could not find Config File and could not show Config Dialog" << std::endl;

    m_Window = m_Root->initialise(true, "CS381 Game Engine Version 1.0");

    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    m_SceneMgr = m_Root->createSceneManager(Ogre::ST_GENERIC);

    m_Camera = m_SceneMgr->createCamera("MainCam");
    m_Camera->setPosition(0, 0, 80);
    m_Camera->lookAt(0, 0, -300);
    m_Camera->setNearClipDistance(5);

    Ogre::Viewport* vp = m_Window->addViewport(m_Camera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    m_Camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    //-----------------------------------------------------------------------
    Ogre::WindowEventUtilities::addWindowEventListener(m_Window, this);
    //mRoot->addFrameListener(this);
    //mRoot->startRendering();

}

void GfxMgr::LoadLevel(std::string levelLocation)
{

}

void GfxMgr::Tick(float dt)
{
    m_Root->renderOneFrame(dt);
    Ogre::WindowEventUtilities::messagePump();
}

void GfxMgr::Stop()
{
    
}



void GfxMgr::MakeSky()
{
    m_Engine->m_GfxMgr->m_SceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}

void GfxMgr::MakeGround()
{

    //Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    //oceanSurface(Ogre::Vector3::UNIT_Y, 0);
    //oceanSurface = plane;
    //oceanSurface.normal = Ogre::Vector3::UNIT_Y;
    //oceanSurface.d = 0;
    Ogre::MeshManager::getSingleton().createPlane("ocean", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    //plane,
            m_OceanSurface, 15000, 15000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

    Ogre::Entity* groundEntity = m_Engine->m_GfxMgr->m_SceneMgr->createEntity("ocean");
    m_Engine->m_GfxMgr->m_SceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    //groundEntity->setMaterialName("Ocean2_HLSL_GLSL");
    //groundEntity->setMaterialName("OceanHLSL_GLSL");
    groundEntity->setMaterialName("Ocean2_Cg");
    //groundEntity->setMaterialName("NavyCg");
}

void GfxMgr::windowClosed(Ogre::RenderWindow *rw)
{
    m_Root->shutdown();
    m_Engine->m_KeepRunning = false;
}

bool GfxMgr::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
    if(m_Window->isClosed())
        return false;
    return true;
}
