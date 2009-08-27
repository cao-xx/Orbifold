/*
 *  PlayState.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 26.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */
#ifndef PlayState_H
#define PlayState_H

#include <OgreCamera.h>

#include "GameState.h"
//#include "PauseState.h"

class Game;

class PlayState : public GameState {

public:

  void enter(Game* game, Ogre::RenderWindow* window);
  void exit();

  void pause();
  void resume();

  // Update
  void update();
  void update(float ms);

  static PlayState* getSingleton();

  // 	
  void keyPressed(const OIS::KeyEvent &evt);
  void keyReleased(const OIS::KeyEvent &evt);

  void mouseMoved(const OIS::MouseEvent &evt);
  void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
  void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

protected:

  static PlayState* instance;

  Ogre::Root *ogre;
  Ogre::RenderWindow *window;
  Ogre::SceneManager *scene;
  Ogre::Camera *camera;
  Ogre::OverlayManager *overlayMgr;
  Ogre::Overlay *mouseOverlay;
  Ogre::OverlayElement *mousePointer;

  Game *game;
	
  void createOverlays();
  void hideOverlays();
  Ogre::Camera* createCamera(Ogre::SceneManager* sceneMgr, Ogre::RenderWindow* window);

private:

  PlayState();
  ~PlayState();

};
#endif
