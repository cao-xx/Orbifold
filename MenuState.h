/*
 *  MenuState.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 05.09.09.
 *  Copyright 2009 Orbifold. All rights reserved.
 *
 */

#ifndef MenuState_H
#define MenuState_H

#include <Ogre/OgreCamera.h>

#include "GameState.h"
#include "Trays.h"
#include "Game.h"

namespace Orbifold {

class Game;


class MenuState : public GameState, public SdkTrayListener {
  
public:
  
  void enter(Game* game, Ogre::RenderWindow* window);
  void exit();
  
  void pause();
  void resume();
  
  // Update
  void update();
  void update(float ms);
  
  static MenuState* getSingleton();
  
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
  
  //
  virtual void yesNoDialogClosed(const Ogre::DisplayString& question, bool yesHit);
  virtual void buttonHit(SdkButton* b);
  virtual void itemSelected(SelectMenu* menu);
  virtual void sliderMoved(Slider* slider);
  
protected:
  
  static MenuState* instance;
  
  Ogre::Root *ogre;
  Ogre::RenderWindow *window;
  Ogre::SceneManager *scene;
  Ogre::Camera *camera;
  
  SdkTrayManager* tray;
  SelectMenu* rendererMenu;
  
  
  Game *game;
  
  bool contentSetup;
  bool resourcesLoaded;
  
  void setupContent();
  void cleanupContent();
	
  void locateResources();
  void loadResources();
  void unloadResources();
	
  void createDummyScene();
  void destroyDummyScene();
	
  void setupWidgets();


private:
  
  MenuState();
  ~MenuState();
  
};

}
#endif
