/*
 *  game.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "game.h"
#include "OgreStringConverter.h"

Game* Game::mGame;

Game::Game() :
	mRoot(0),
	mInput(0),
	mIntroState(0),
	mPlayState(0),
	mPauseState(0),
	bShutdown(false) {
}


Game::~Game() {
	while (!mStates.empty()) {
		mStates.back()->exit();
		mStates.pop_back();
	}
	
	if(mInput)
		delete mInput;
	if(mIntroState)
		delete mIntroState;
	if(mPlayState)
		delete mPlayState;
	if(mPauseState)
		delete mPauseState;
	if(mRoot)
		delete mRoot;
}

void Game::startGame(GameState *gameState) {
	// Initialise Ogre and any Resources.
	mRoot = this->initOgre();
	
	if(!this->configureGame()) {
		throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
							  "Error -- Couldn't Configure RenderWindow",
							  "Prototyp -- Error");
		return;
	}
	
	//Setup states
	mIntroState = IntroState::getSingletonPtr();
	mPlayState = PlayState::getSingletonPtr();
	mPauseState = PauseState::getSingletonPtr();
	
	//Setup input
	mInput = InputHandler::getSingletonPtr();
	
	
}

void Game::initResources(){
	Ogre::ResourceGroupManager &resources=Ogre::ResourceGroupManager::getSingleton();
	resources.addResourceLocation("data","FileSystem");
	resources.initialiseAllResourceGroups();
}

Ogre::Root* Game::initOgre(){	
	Ogre::Root* ogre = new Ogre::Root();
	
#if defined(_DEBUG)
	ogre->loadPlugin("RenderSystem_GL_d");
#else
	ogre->loadPlugin("RenderSystem_GL");
#endif
	Ogre::RenderSystemList *rs = NULL;
	Ogre::RenderSystemList::iterator r_it;
	
	rs = ogre->getAvailableRenderers();
	r_it = rs->begin();
	
	if(rs && rs->size() && rs->at(0)->getName().compare("RenderSystem_GL")){
		Ogre::RenderSystem * r=rs->at(0);
		ogre->setRenderSystem(r);
	}else{
		exit(1);
	}
	
	this->initResources();	
	return ogre;
}

bool Game::configureGame() {
	mRoot->initialise(false);
	mRenderWindow = mRoot->createRenderWindow("Prototyp", 800, 600, false, NULL);	
	return true;
}

GameState Game::getCurrentState() {
	return m_state;
}

bool Game::lockState() {
	if (m_locked == false)
		return m_locked = true;
	else
		return false;
}

bool Game::requestStateChange(GameState newState) {
	if (m_state == STARTUP) {
		m_locked = false;
		m_state = newState;

		return true;
	}

	// this state cannot be changed once initiated
	if (m_state == SHUTDOWN) {
		return false;
	}

	if ((m_state == GUI || m_state == GAME || m_state == LOADING || m_state == CANCEL_LOADING) &&
		(newState != STARTUP) && (newState != m_state)) {
		m_state = newState;
		return true;
	}
	else
		return false;
}

void Game::setFrameTime(float ms) {
	m_frame_time = ms;
}

/*Game* Game::getSingletonPtr( void ){
	if (!mGame) {
		mGame = new Game();
	}
	return mGame;
}
*/
