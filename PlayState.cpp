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

namespace Orbifold {
  
class Game;

PlayState::PlayState() {
  this->ogre = 0;
  this->window = 0;
  this->scene = 0;
  this->game = 0;
  this->camRaySceneQuery = 0;
}

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


void PlayState::enter(Game* game, Ogre::RenderWindow* window) {
	
  PlayState* state = PlayState::getSingleton();
  state->ogre = Ogre::Root::getSingletonPtr();
  state->window = window;
  state->game = game;

  this->velocity = Ogre::Vector3(0,0,0);
  //state->createSceneManager();
  state->setupView();
  state->setupContent();
}


void PlayState::exit() {
	PlayState* state = PlayState::getSingleton();
	if (state->scene) state->scene->clearScene();
	if (contentSetup) state->cleanupContent();
	contentSetup = false;
	if (resourcesLoaded) state->unloadResources();
	resourcesLoaded = false;
	if (state->scene) state->ogre->destroySceneManager(state->scene);
	state->scene = 0;
}

void PlayState::setupContent(){
  
  Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Scene");  
  
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
  if (this->ogre->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE)) {
    this->camera->setFarClipDistance(0);
  }
  
  // Define the required skyplane
  Ogre::Plane plane;
  plane.d = 5000;
  plane.normal = -Ogre::Vector3::UNIT_Y;
  
  this->camera->setPosition(707,2500,528);
  this->camera->setOrientation(Ogre::Quaternion(-0.3486, 0.0122, 0.9365, 0.0329));
  
  camRaySceneQuery = this->scene->createRayQuery(Ogre::Ray(this->camera->getPosition(), -Ogre::Vector3::UNIT_Y));
}
void PlayState::cleanupContent(){}

void PlayState::locateResources(){}
void PlayState::loadResources(){}
void PlayState::unloadResources(){}

// A lot of stubs.
void PlayState::pause() {}
void PlayState::resume() {}
void PlayState::update() {
  
  // get time since last Update
  unsigned long tslu = this->game->timer->getMilliseconds();
  
  this->camera->moveRelative(tslu*this->velocity);
  this->camera->yaw(tslu*this->spin);
  static Ogre::Ray updateRay;
  updateRay.setOrigin(this->camera->getPosition());
  updateRay.setDirection(-Ogre::Vector3::UNIT_Y);
  camRaySceneQuery->setRay(updateRay);
  Ogre::RaySceneQueryResult& qryResult = camRaySceneQuery->execute();
  Ogre::RaySceneQueryResult::iterator i = qryResult.begin();
  if (i != qryResult.end() && i->worldFragment) {
    this->camera->setPosition(this->camera->getPosition().x,
                              i->worldFragment->singleIntersection.y + 10,
                              this->camera->getPosition().z);
    }
  
}



  bool PlayState::keyPressed(const OIS::KeyEvent &evt) {
    if (evt.key == OIS::KC_RIGHT) {
      this->velocity.x -= 0.1;
    } else if(evt.key == OIS::KC_LEFT) {
      this->velocity.x += 0.1;
    } else if (evt.key == OIS::KC_UP) {
      this->velocity.z -= 0.1;
    } else if (evt.key == OIS::KC_DOWN) {
      this->velocity.z += 0.1;
    } else if (evt.key == OIS::KC_A) {
      this->spin += Ogre::Radian(0.005);
    } else if (evt.key == OIS::KC_D) {
      this->spin -= Ogre::Radian(0.005);
    }
    
    return true;
  }
  bool PlayState::keyReleased(const OIS::KeyEvent &evt) {
    if (evt.key == OIS::KC_SPACE) {
      //mGame->requestStateChange(PAUSE);
    } else if(evt.key == OIS::KC_ESCAPE) {
      //this->game->requestStateChange(SHUTDOWN);
    } else if (evt.key == OIS::KC_RIGHT) {
      this->velocity.x += 0.1;
    } else if(evt.key == OIS::KC_LEFT) {
      this->velocity.x -= 0.1;
    } else if (evt.key == OIS::KC_UP) {
      this->velocity.z += 0.1;
    } else if (evt.key == OIS::KC_DOWN) {
      this->velocity.z -= 0.1;
    } else if (evt.key == OIS::KC_A) {
      this->spin -= Ogre::Radian(0.005);
    } else if (evt.key == OIS::KC_D) {
      this->spin += Ogre::Radian(0.005);
    } 
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
    this->game->requestStateChange(MenuState::getSingleton());
    return true;
  }
  bool PlayState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {return true;}


  void PlayState::windowResized(Ogre::RenderWindow* rw) {}
  void PlayState::windowMoved(Ogre::RenderWindow* rw) {}
  bool PlayState::windowClosing(Ogre::RenderWindow* rw) {return true;}
  void PlayState::windowClosed(Ogre::RenderWindow* rw) {}
  void PlayState::windowFocusChange(Ogre::RenderWindow* rw) {}


//void createOverlays() {}
//void hideOverlays() {}


void PlayState::setupView() {
  
  this->scene = this->ogre->createSceneManager("TerrainSceneManager");
	Ogre::Camera* cam = this->scene->createCamera("PlayerCamera");
	
  cam->setPosition(Ogre::Vector3(128,25,128));
	cam->lookAt(Ogre::Vector3(0,0,-300));
	
  cam->setNearClipDistance(1);
	cam->setFarClipDistance(1000);
	
	Ogre::Viewport* v = this->window->addViewport(cam);
	//v->setBackgroundColour(Ogre::ColourValue(0.5,0.0,0.5));
	cam->setAspectRatio(Ogre::Real(v->getActualWidth())/v->getActualHeight());
  this->camera = cam;
}

}

