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

#if WIN32
#elif LINUX
#else
#include <Carbon/Carbon.h>
#endif

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>

#include "Input.h"

typedef enum {
	STARTUP,
	GUI,
	LOADING,
	PAUSE,
	CANCEL_LOADING,
	GAME,
	SHUTDOWN
} State;

class GameState;

class Game :
  public OIS::KeyListener,
  public OIS::MouseListener {
  
public:
  
  void static start();
  
  void static stop();
  
protected:
  
  static Game* instance;
	  
  bool running;

  State state;
  
  Ogre::Root* ogre;
  Ogre::RenderWindow* window;

  static Game* getSingleton();

  void initOgreRoot();

  void initOgreResources();

private:
  Game();
  ~Game();

  GameState* getState(State state);



	/* Inputhandling */

	InputHandler *mInput;

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);

	// are we shutting down?
	bool bShutdown;
	// time since last frame
	float flFrameTime;



public:
	bool requestStateChange(State state);
	bool lockState();
	bool unlockState();
	State getCurrentState();

	void setFrameTime(float ms);
	inline float getFrameTime() {return flFrameTime;};

};
#endif
