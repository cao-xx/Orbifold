/*
 *  intro_state.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 26.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "IntroState.h"

IntroState* IntroState::mIntroState;

void IntroState::enter(){
	mRoot = Ogre::Root::getSingletonPtr();
	mOverlayManager = Ogre::OverlayManager::getSingletonPtr();
	mSceneManager = mRoot->getSceneManager("ST_GENERIC");
	mCamera = mSceneManager->createCamera("IntroCamera");
	mViewport = mRenderWindow->addViewport(mCamera);
	
	mIntroOverlay = mOverlayManager->getByName("Overlay/IntroState");
	mIntroOverlay->show();
}

void IntroState::exit() {
	mIntroOverlay->hide();
	mSceneManager->clearScene();
	mSceneManager->destroyAllCameras();
	mRenderWindow->removeAllViewports();
}

IntroState::~IntroState(){}
