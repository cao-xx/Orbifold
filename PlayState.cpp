/*
 *  PlayState.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 26.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "PlayState.h"
#include "MenuState.h"
#include "Game.h"
#include <Ogre/OgreTextureUnitState.h>
#include "RTSCamera.h"

namespace Orbifold {
  
class Game;

  PlayState::PlayState() :
  ogre(0),
  window(0),
  //camRaySceneQuery(0),
  initialised(false)
  {}

PlayState::~PlayState() {
  if(this->instance) {
    delete this->instance;
  }
}


PlayState* PlayState::instance = 0;


PlayState* PlayState::getSingleton() {
  if(!instance) {
    instance = new PlayState();
  }
  return instance;
}

void PlayState::enter() {
  PlayState* state = PlayState::getSingleton();
  if (state->initialised) {
    state->restore();
  } else {
    state->initialise();
  }
}
  
void PlayState::exit() {
  PlayState* state = PlayState::getSingleton();
  state->save();
  if (state->scene) state->scene->clearScene();
}


void PlayState::save() {
    if (camera) camera->save(); 
}  
  

void PlayState::restore() {
  PlayState* state = PlayState::getSingleton();
  state->setupView();
  state->setupContent();
  state->camera->restore(); 
}  


void PlayState::shutdown() {
	PlayState* state = PlayState::getSingleton();
	if (state->scene) state->scene->clearScene();
	if (contentSetup) state->cleanupContent();
	contentSetup = false;
	if (resourcesLoaded) state->unloadResources();
	resourcesLoaded = false;
	if (state->scene) state->ogre->destroySceneManager(state->scene);
	state->scene = 0;
}

  
  
  
  
void PlayState::initialise() {
    PlayState* state = PlayState::getSingleton();
    state->ogre = Ogre::Root::getSingletonPtr();
    state->window = Game::getRenderWindow();
    state->timer = new Ogre::Timer();
    //state->velocity = Ogre::Vector3(0,0,0);
    this->initialiseView();
    this->initialiseContent();
    this->setupView();
    this->setupContent();
    // has to be called after the content is setup,
    // because its rayscenequery depends on an actual world being present
    this->camera->initialise();
    initialised = true;
}
  
  void PlayState::initialiseView() {
    this->scene = this->ogre->createSceneManager("TerrainSceneManager");
    RTSCamera* rtscam = new RTSCamera("PlayerCamera", this->scene);  
    this->camera = rtscam;
    //this->camera->initialise();
  }
  
  void PlayState::setupView() {
    Ogre::Camera* cam = camera->getCamera();
    Ogre::Viewport* v = this->window->addViewport(cam);
    //v->setBackgroundColour(Ogre::ColourValue(0.5,0.0,0.5));
    cam->setAspectRatio(Ogre::Real(v->getActualWidth())/v->getActualHeight());
  }
  
  void PlayState::initialiseContent() {
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Scene");    
  }
  
  
void PlayState::setupContent(){
  
  Ogre::Plane waterPlane;
  
  // Set ambient light
  this->scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

  // create light
  Ogre::Light* l = this->scene->createLight("MainLight");
  
  l->setPosition(20,80,50);
  
  Ogre::ColourValue fadeColour(0.93, 0.86, 0.76);
  this->scene->setFog(Ogre::FOG_LINEAR, fadeColour, .001, 500, 1000);
  this->window->getViewport(0)->setBackgroundColour(fadeColour);  

  std::string terrain_config("terrain.cfg");
  this->scene->setWorldGeometry(terrain_config);
  
  // Define the required skyplane
  Ogre::Plane plane;
  plane.d = 5000;
  plane.normal = -Ogre::Vector3::UNIT_Y;
 }
  
void PlayState::cleanupContent(){}

void PlayState::locateResources(){}
void PlayState::loadResources(){}
void PlayState::unloadResources(){}

// A lot of stubs.
void PlayState::update() {
  // get time since last Update
  unsigned long tslu = this->timer->getMilliseconds();
  this->timer->reset();
  this->camera->update(tslu);
}



  bool PlayState::keyPressed(const OIS::KeyEvent &evt) {
    return true;
  }
  bool PlayState::keyReleased(const OIS::KeyEvent &evt) {
    return true;
  }

  bool PlayState::mouseMoved(const OIS::MouseEvent &evt) {
  //const OIS::MouseState &mouseState = evt.state;
  // Update Mousepointer on Screen, might be smoother if moved by relative change.
  // mMousePointer->setTop(mouseState.Y.abs);
  // mMousePointer->setLeft(mouseState.X.abs);
    return true;
  }

  bool PlayState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    Game::requestStateChange(MenuState::getSingleton());
    return true;
  }
  bool PlayState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {return true;}


  void PlayState::windowResized(Ogre::RenderWindow* rw) {}
  void PlayState::windowMoved(Ogre::RenderWindow* rw) {}
  bool PlayState::windowClosing(Ogre::RenderWindow* rw) {return true;}
  void PlayState::windowClosed(Ogre::RenderWindow* rw) {}
  void PlayState::windowFocusChange(Ogre::RenderWindow* rw) {}

}

