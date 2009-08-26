/*
 *  play_state.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 26.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#pragma once

#include <OgreCamera.h>

#include "game_state.h"
#include "pause_state.h"

class PlayState : public GameState {
public:
	PlayState () {};
	~PlayState();
	
	void enter(Ogre::RenderWindow* window);
	void exit();
	
	void pause();
	void resume();
	void update();
	
	void keyPressed(const OIS::KeyEvent &evt);
	void keyReleased(const OIS::KeyEvent &evt);
	
	void mouseMoved(const OIS::MouseEvent &evt);
	void mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	void mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

private:
	Ogre::Root *mRoot;
	Ogre::Camera *mCamera;
	Ogre::SceneManager *mSceneManager;
	Ogre::RenderWindow *mRenderWindow;
	Ogre::Viewport *mViewport;
	Ogre::OverlayManager *mOverlayManager;
	// Overlays should be extended (need to integrate proper GUI anyway)
	Ogre::Overlay *mMouseOverlay;
	Ogre::OverlayElement *mMousePointer;
	
	void createOverlays();
	void hideOverlays();
	Ogre::Camera* createCamera(Ogre::SceneManager* sceneMgr, Ogre::RenderWindow* window);
	
};
