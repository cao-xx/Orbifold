/*
 *  PlayState.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 26.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "PlayState.h"
#include "Game.h"
#include <Ogre/OgreTextureUnitState.h>

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

  state->scene = state->ogre->getSceneManager("ST_GENERIC");

  state->camera = state->createCamera(state->scene, state->window);

}


void PlayState::exit() {
  PlayState* state = PlayState::getSingleton();
  //this->hideOverlays();
  state->scene->clearScene();
  state->scene->destroyAllCameras();
  state->window->removeAllViewports();
}

// A lot of stubs.
void PlayState::pause() {}
void PlayState::resume() {}
void PlayState::update() {}



void PlayState::keyPressed(const OIS::KeyEvent &evt) {}
void PlayState::keyReleased(const OIS::KeyEvent &evt) {
  if (evt.key == OIS::KC_SPACE) {
    //mGame->requestStateChange(PAUSE);
  } else if(evt.key == OIS::KC_ESCAPE) {
    //this->game->requestStateChange(SHUTDOWN);
  }
}

void PlayState::mouseMoved(const OIS::MouseEvent &evt) {
  //const OIS::MouseState &mouseState = evt.state;
  // Update Mousepointer on Screen, might be smoother if moved by relative change.
  // mMousePointer->setTop(mouseState.Y.abs);
  // mMousePointer->setLeft(mouseState.X.abs);
}

void PlayState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
void PlayState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}


void PlayState::windowResized(Ogre::RenderWindow* rw) {}
void PlayState::windowMoved(Ogre::RenderWindow* rw) {}
bool PlayState::windowClosing(Ogre::RenderWindow* rw) {return true;}
void PlayState::windowClosed(Ogre::RenderWindow* rw) {}
void PlayState::windowFocusChange(Ogre::RenderWindow* rw) {}


//void createOverlays() {}
//void hideOverlays() {}

Ogre::Camera* PlayState::createCamera(Ogre::SceneManager *sceneMgr, Ogre::RenderWindow *window) {
  Ogre::Camera* cam = sceneMgr->createCamera("SimpleCamera");
  cam->setPosition(Ogre::Vector3(0.0f,0.0f,500.0f));
  cam->lookAt(Ogre::Vector3(0.0f,0.0f,0.0f));
  cam->setNearClipDistance(5.0f);
  cam->setFarClipDistance(5000.0f);

  Ogre::Viewport* v = window->addViewport(cam);
  v->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5));

  cam->setAspectRatio(Ogre::Real(v->getActualWidth())/v->getActualHeight());

  return cam;
}
