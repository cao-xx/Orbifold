/*
 *  game.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	#include <Carbon/Carbon.h>
#endif

#include "game_state.h"
#include "play_state.h"
#include "intro_state.h"
#include "pause_state.h"

#include "game.h"

#include <Ogre.h>
#include "OgreStringConverter.h"
#include <OgreWindowEventUtilities.h>

Game* Game::mGame;

Game::Game() :
	mRoot(0),
	mInput(0),
//	mIntroState(0),
//	mPlayState(0),
//	mPauseState(0),
	bShutdown(false) {
}


Game::~Game() {
	/*while (!mStates.empty()) {
		mStates.back()->exit();
		mStates.pop_back();
	} */
	
	if(mInput)
		delete mInput;
//	if(mIntroState)
//		delete mIntroState;
//	if(mPlayState)
//		delete mPlayState;
//	if(mPauseState)
//		delete mPauseState;
	if(mRoot)
		delete mRoot;
}

//void Game::startGame(GameState* gameState) {
void Game::startGame(){
	// Initialise Ogre and any Resources.
	mRoot = this->initOgre();
	
	if(!this->configureGame()) {
		throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR,
							  "Error -- Couldn't Configure RenderWindow",
							  "Prototyp -- Error");
		return;
	}
	
	//Setup states
//	mIntroState = IntroState::getSingletonPtr();
//	mPlayState = PlayState::getSingletonPtr();
//	mPauseState = PauseState::getSingletonPtr();
	
	//Setup input
	mInput = InputHandler::getSingletonPtr();
	mInput->initialise(mRenderWindow);
	mInput->addKeyListener(this, "Game");
	mInput->addMouseListener(this, "Game");
	
	// change to first state
	// m_state = STARTUP;
	// this->requestStateChange(STARTUP);
	int running = 1000;
	while (running--) {
		// Update InputHandler
		mInput->capture();
		// Update current state
		// mCurrentState->update();
		// Render next frame
		mRoot->renderOneFrame();
		// make Windows happy
		Ogre::WindowEventUtilities::messagePump();		
	}
	
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

State Game::getCurrentState() {
	return m_state;
}

bool Game::lockState() {
	if (m_locked == false)
		return m_locked = true;
	else
		return false;
	return false;
}

//this is kind of a hack
GameState* Game::getState(State state) {
	// I didn't implement all State classes yet.
	switch (state) {
		case STARTUP:
			return mIntroState;
			break;
		case GUI:
			return mIntroState;
			break;
		case LOADING:
			return mIntroState;
			break;
		case CANCEL_LOADING:
			return mIntroState;
			break;
		case GAME:
			return mPlayState;
			break;
		case SHUTDOWN:
			return mPauseState;
			break;
		default:
			return mCurrentState;
			break;
	}
	// paranoid compiler
	return mCurrentState;
}


bool Game::requestStateChange(State newState) {
	if (m_state == STARTUP) {
		m_locked = false;
		m_state = newState;
		mCurrentState = this->getState(newState);

		return true;
	}

	// this state cannot be changed once initiated
	if (m_state == SHUTDOWN) {
		return false;
	}

	if ((m_state == GUI || m_state == GAME || m_state == LOADING || m_state == CANCEL_LOADING) &&
		(newState != STARTUP) && (newState != m_state)) {
		m_state = newState;
		mCurrentState = this->getState(newState);
		return true;
	}
	else
		return false;
}

void Game::setFrameTime(float ms) {
	flFrameTime = ms;
}

/* Another variant would be to give the InputHandler a Reference to the Game Object
 and let the CurrentState be public (maybe protected by a Mutex) so that the InputHandler
 can call the CurrentState directly.
 */
bool Game::keyPressed(const OIS::KeyEvent &evt) {
	//Call KeyPressed of CurrentState
	mCurrentState->keyPressed(evt);
	return true;
}

bool Game::keyReleased(const OIS::KeyEvent &evt) {
	//Call keyReleased of CurrentState
	mCurrentState->keyReleased(evt);
	return true;
}

bool Game::mouseMoved(const OIS::MouseEvent &evt) {
	// You get the picture
	mCurrentState->mouseMoved(evt);
	return true;
}

bool Game::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	mCurrentState->mousePressed(evt, id);
	return true;
}

bool Game::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	mCurrentState->mousePressed(evt, id);
	return true;
}

Game* Game::getSingletonPtr(){
	if (!mGame) {
		mGame = new Game();
	}
	return mGame;
}

