/*
 *  GameState.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 26.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */
#ifndef GameState_H
#define GameState_H

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreStringConverter.h>


class GameState {

public:
	static virtual void enter(Ogre::RenderWindow *window) = 0;
	static virtual void exit() = 0;
		
	static virtual void update() = 0;
		
	virtual void keyPressed(const OIS::KeyEvent &evt) = 0;
	virtual void keyReleased(const OIS::KeyEvent &evt) = 0;
	
	virtual void mouseMoved(const OIS::MouseEvent &evt) = 0;
	virtual void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
	virtual void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;

private:
	GameState();
	~GameState();
};
#endif
