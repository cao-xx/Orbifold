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

#include <OgreCamera.h>

#include "GameState.h"
#include "PauseState.h"


class PlayState : public GameState {
public:
  //~PlayState();

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

	static PlayState* getSingletonPtr();
private:
	PlayState() {}
	static PlayState *mPlayState;

	Ogre::Root *mRoot;
	Ogre::Camera *mCamera;
	Ogre::SceneManager *mSceneManager;
	Ogre::RenderWindow *mRenderWindow;
	Ogre::Viewport *mViewport;
	Ogre::OverlayManager *mOverlayManager;
	// There will be more Overlays.
	Ogre::Overlay *mMouseOverlay;
	Ogre::OverlayElement *mMousePointer;

	Game *mGame;

	void createOverlays();
	void hideOverlays();
	Ogre::Camera* createCamera(Ogre::SceneManager* sceneMgr, Ogre::RenderWindow* window);

};
#endif
