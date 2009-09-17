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

#include "RTSCamera.h"

#include "GameState.h"
//#include "PauseState.h"

namespace Orbifold {

class Game;

class PlayState : public GameState {

public:

  void enter();
  void exit();

  void save();
  void restore();
  
  void initialise();
  void shutdown();
  
  // Update
  void update();

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
  RTSCamera *camera;
  
  Ogre::Timer* timer;
  
  Ogre::Vector3 velocity;
  Ogre::Radian spin;

  
  
  bool contentSetup;
  bool resourcesLoaded;
		
  void setupContent();
  void cleanupContent();
  
  void initialiseContent();
	
  void locateResources();
  void loadResources();
  void unloadResources();
	
  void createSceneManager();
	
  void setupView();
  
  void initialiseView();
	

  void createOverlays();
  void hideOverlays();
  //Ogre::Camera* createCamera(Ogre::SceneManager* sceneMgr, Ogre::RenderWindow* window);
	


private:
  bool initialised;

  PlayState();
  ~PlayState();

};
  
}
#endif
