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

class GameState;

class Game : 
	public OIS::KeyListener,
	public OIS::MouseListener {
	
private:
	Game();
	/*Different Game States, probably should be replaced
	 by something more flexible.
	 */
	GameState *mIntroState;
	GameState *mPlayState;
	GameState *mPauseState;
	GameState *mCurrentState;
	
	GameState* getState(State state);
	
	// state variables
	State m_state;
	bool m_locked;
		

	
	static Game *mGame;
	
	/* Directly Ogre related */
	Ogre::Root *mRoot;
	Ogre::RenderWindow *mRenderWindow;
		
	Ogre::Root* initOgre();
	bool configureGame();
	void initResources();
	
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
	virtual ~Game();
	
	void startGame(GameState *State);
	
	bool requestStateChange(State state);
	bool lockState();
	bool unlockState();
	State getCurrentState();

	void setFrameTime(float ms);
	inline float getFrameTime() {return flFrameTime;};
		
	static Game* getSingeltonPtr();
};
