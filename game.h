/*
 *  game.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#pragma once

//#include <vector>
//#include <map>

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

#include "input.h"


typedef enum {
	STARTUP,
	GUI,
	LOADING,
	CANCEL_LOADING,
	GAME,
	SHUTDOWN
} State;

 
class Game : 
	OIS::KeyListener,
	OIS::MouseListener
{

public:	
	virtual ~Game();
	
	void startGame(State *State);
	
	bool requestStateChange(State state);
	bool lockState();
	bool unlockState();
	State getCurrentState();

	void setFrameTime(float ms);
	inline float getFrameTime() {return flFrameTime;};	
	static Game* getSingeltonPtr();

protected:
	Game();
	
	Ogre::Root* initOgre();
	bool configureGame();
	void initResources();
	
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	
	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);
	
	Ogre::Root *mRoot;
	Ogre::RenderWindow *mRenderWindow;
	InputHandler *mInput;
	
	
	GameState *mIntroState;
	GameState *mPlaystate;
	GameState *mPauseState;
	GameState *mCurrentState;

	bool bShutdown;
	
	float flFrameTime;
	
	static Game *mGame;
};
