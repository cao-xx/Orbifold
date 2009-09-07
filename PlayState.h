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

#include <Ogre/OgreCamera.h>

#include "GameState.h"
//#include "PauseState.h"

namespace Orbifold {

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
  bool keyPressed(const OIS::KeyEvent &evt);
  bool keyReleased(const OIS::KeyEvent &evt);

  bool mouseMoved(const OIS::MouseEvent &evt);
  bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

  //
  void windowResized(Ogre::RenderWindow* rw);
  void windowMoved(Ogre::RenderWindow* rw);
  bool windowClosing(Ogre::RenderWindow* rw);
  void windowClosed(Ogre::RenderWindow* rw);
  void windowFocusChange(Ogre::RenderWindow* rw);

protected:

  static PlayState* instance;

  Ogre::Root *ogre;
  Ogre::RenderWindow *window;
  Ogre::SceneManager *scene;
  Ogre::Camera *camera;
  
  Ogre::Vector3 velocity;
  Ogre::Radian spin;

  Ogre::RaySceneQuery *camRaySceneQuery;
  

  Game *game;

  bool contentSetup;
  bool resourcesLoaded;
		
  void setupContent();
  void cleanupContent();
	
  void locateResources();
  void loadResources();
  void unloadResources();
	
  void createSceneManager();
	
  void setupView();
	

  void createOverlays();
  void hideOverlays();
  //Ogre::Camera* createCamera(Ogre::SceneManager* sceneMgr, Ogre::RenderWindow* window);
	


private:

  PlayState();
  ~PlayState();

};
  
}
#endif
