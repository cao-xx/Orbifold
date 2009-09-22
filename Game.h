/*
 *  Game.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#ifndef GAME_H
#define GAME_H

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <Carbon/Carbon.h>
#endif

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

#include <Ogre/Ogre.h>
#include "Input.h"

namespace Orbifold {


class GameState;

class Game :
public Ogre::WindowEventListener,
	OIS::KeyListener,
	OIS::MouseListener
	{

public:

  void static start();
  void static stop();

  // Callbacks for Inputhandling
  bool mouseMoved(const OIS::MouseEvent &evt);
  bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
  bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

  bool keyPressed(const OIS::KeyEvent &evt);
  bool keyReleased(const OIS::KeyEvent &evt);
	  
  static OIS::Mouse* getMouse();
  static OIS::Keyboard* getKeyboard();

  // Window handling
  static Ogre::RenderWindow* getRenderWindow();
	  
  void windowResized(Ogre::RenderWindow* rw);
  void windowMoved(Ogre::RenderWindow* rw);
  bool windowClosing(Ogre::RenderWindow* rw);
  void windowClosed(Ogre::RenderWindow* rw);
  void windowFocusChange(Ogre::RenderWindow* rw);

  // State handling
  GameState* getCurrentState();
  static bool requestStateChange(GameState* s);

protected:

  static Game* instance;

  bool running;

  Ogre::Root* ogre;
  Ogre::RenderWindow* window;
  InputHandler* input;
  GameState* state;

  static Game* getSingleton();

  void initialise();
  void initOgreRoot();
  void initPlugins();
  void initRenderWindow();
  void initOgreResources();
  
  void initInput();
  void initState();

  void locateResources();
  void loadResources();

  //void reconfigure(const Ogre::String& renderer, Ogre::NameValuePairList& options);

  void shutdown();
  void shutdownInput();


 private:
   Game();
  ~Game();

};
	
}
#endif
