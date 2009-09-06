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
  this->overlayMgr = 0;
  this->mouseOverlay = 0;
  this->mousePointer = 0;
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

  state->overlayMgr = Ogre::OverlayManager::getSingletonPtr();
  state->createSceneManager();
  state->setupView();
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

void PlayState::setupContent(){}
void PlayState::cleanupContent(){}

void PlayState::locateResources(){}
void PlayState::loadResources(){}
void PlayState::unloadResources(){}

// A lot of stubs.
void PlayState::pause() {}
void PlayState::resume() {}
void PlayState::update() {}



  bool PlayState::keyPressed(const OIS::KeyEvent &evt) {return true;}
  bool PlayState::keyReleased(const OIS::KeyEvent &evt) {
    if (evt.key == OIS::KC_SPACE) {
      //mGame->requestStateChange(PAUSE);
    } else if(evt.key == OIS::KC_ESCAPE) {
      //this->game->requestStateChange(SHUTDOWN);
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

void PlayState::createSceneManager() {
	this->scene = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC);
}

void PlayState::setupView() {
	Ogre::Camera* cam = this->scene->createCamera("SimpleCamera");
	cam->setPosition(Ogre::Vector3(0.0f,0.0f,500.0f));
	cam->lookAt(Ogre::Vector3(0.0f,0.0f,0.0f));
	cam->setNearClipDistance(5.0f);
	cam->setFarClipDistance(5000.0f);
	
	Ogre::Viewport* v = this->window->addViewport(cam);
	v->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5));
	cam->setAspectRatio(Ogre::Real(v->getActualWidth())/v->getActualHeight());
}

}

