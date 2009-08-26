/*
 *  game_state.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 26.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */
#pragma once

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreStringConverter.h>

#include "game.h"
#include "input.h"

class GameState {
public:
	~GameState(){}
		
	virtual void enter(Ogre::RenderWindow *window) = 0;
	virtual void exit() = 0;
		
	virtual void update() = 0;
		
	virtual void keyPressed(const OIS::KeyEvent &evt) = 0;
	virtual void keyReleased(const OIS::KeyEvent &evt) = 0;
	
	virtual void mouseMoved(const OIS::MouseEvent &evt) = 0;
	virtual void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
	virtual void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
protected:
	GameState() {};
};