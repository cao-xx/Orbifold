/*
 *  Game.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

//#include "GameState.h"
//#include "PlayState.h"
//#include "IntroState.h"
//#include "PauseState.h"
#include "Game.h"
#include "Input.h"
#include <OgreWindowEventUtilities.h>
#include <Ogre.h>



Game::Game() {
  this->running = false;
  
  this->ogre = 0;
  this->window = 0;
  this->input = 0;
  //this->state = 0;
}

Game::~Game() {
  if(this->instance) {
    if(this->running)
      Game::stop();
  delete this->instance;
  }
  if(this->ogre)
    delete this->ogre;
}

Game* Game::instance = 0;

Game* Game::getSingleton() {
  if (!instance) {
    instance = new Game();
  }
  return instance;
}

void Game::start(){

  Game* game = Game::getSingleton();
  
  game->initialise();
  game->running = true;

  Ogre::SceneManager* scene = game->ogre->createSceneManager(Ogre::ST_GENERIC);
  Ogre::Camera *cam = game->createCamera(scene,game->window);
  scene->getRootSceneNode()->createChildSceneNode()->attachObject(cam);

  int running = 1000;
  while(running--) {
    game->input->capture();
    //game->state->update();
    game->ogre->renderOneFrame();
    Ogre::WindowEventUtilities::messagePump();
  }	
}


void Game::initialise(){
  this->initOgreRoot();
  this->initOgreResources();
  this->initRenderWindow();
  this->initInput();
  //this->initState();
}

void Game::initInput() {
  this->input = InputHandler::getSingleton();
  if(!this->window)
    return;
  this->input->initialise(this->window);
  this->input->addMouseListener(this, "Game");
  this->input->addKeyListener(this,"Game");
}

void Game::initOgreResources() {
  if(!this->ogre)
    return;

  Ogre::ResourceGroupManager &resources = Ogre::ResourceGroupManager::getSingleton();
  
  resources.addResourceLocation("data","FileSystem");
  resources.initialiseAllResourceGroups();
}


void Game::initRenderWindow() {
  if(!this->ogre)
    return;
  this->ogre->initialise(false);
  this->window = this->ogre->createRenderWindow("Prototyp", 800, 600, false, NULL); 
}


void Game::initOgreRoot() {
  this->ogre = new Ogre::Root();

#ifdef _DEBUG
  ogre->loadPlugin("RenderSystem_GL_d");
#else
  ogre->loadPlugin("RenderSystem_GL");
#endif
  Ogre::RenderSystemList *rs = NULL;
  Ogre::RenderSystemList::iterator r_it;

  rs = ogre->getAvailableRenderers();
  r_it = rs->begin();

  if(rs && rs->size() && rs->at(0)->getName().compare("RenderSystem_GL")){
    Ogre::RenderSystem *r=rs->at(0);
    ogre->setRenderSystem(r);
  }else{
    exit(1);
  }
}



Ogre::Camera* Game::createCamera(Ogre::SceneManager *sceneMgr, Ogre::RenderWindow *window) {
	Ogre::Camera* cam = sceneMgr->createCamera("SimpleCamera"); 
	cam->setPosition(Ogre::Vector3(0.0f,0.0f,500.0f)); 
	cam->lookAt(Ogre::Vector3(0.0f,0.0f,0.0f)); 
	cam->setNearClipDistance(5.0f); 
	cam->setFarClipDistance(5000.0f); 
	
	Ogre::Viewport* v = window->addViewport(cam); 
	v->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5)); 
	
	cam->setAspectRatio(Ogre::Real(v->getActualWidth())/v->getActualHeight()); 
	
	return cam; 
}




// State Game::getCurrentState() {
// 	return m_state;
// }

// bool Game::lockState() {
// 	if (m_locked == false)
// 		return m_locked = true;
// 	else
// 		return false;
// 	return false;
// }

// //this is kind of a hack
// GameState* Game::getState(State state) {
// 	// I didn't implement all State classes yet.
// 	switch (state) {
// 		case STARTUP:
// 			return mIntroState;
// 			break;
// 		case GUI:
// 			return mIntroState;
// 			break;
// 		case LOADING:
// 			return mIntroState;
// 			break;
// 		case CANCEL_LOADING:
// 			return mIntroState;
// 			break;
// 		case GAME:
// 			return mPlayState;
// 			break;
// 		case SHUTDOWN:
// 			return mPauseState;
// 			break;
// 		default:
// 			return mCurrentState;
// 			break;
// 	}
// 	// paranoid compiler
// 	return mCurrentState;
// }


// bool Game::requestStateChange(State newState) {
// 	if (m_state == STARTUP) {
// 		m_locked = false;
// 		m_state = newState;
// 		mCurrentState = this->getState(newState);

// 		return true;
// 	}

// 	// this state cannot be changed once initiated
// 	if (m_state == SHUTDOWN) {
// 		return false;
// 	}

// 	if ((m_state == GUI || m_state == GAME || m_state == LOADING || m_state == CANCEL_LOADING) &&
// 		(newState != STARTUP) && (newState != m_state)) {
// 		m_state = newState;
// 		mCurrentState = this->getState(newState);
// 		return true;
// 	}
// 	else
// 		return false;
// }

// void Game::setFrameTime(float ms) {
//   flFrameTime = ms;
// }


/* Another variant would be to give the InputHandler a Reference to the Game Object
 * and let the current state be public (maybe protected by a Mutex) so that the 
 * InputHandler can call the current state directly.
 */
bool Game::keyPressed(const OIS::KeyEvent &evt) {
  //Call KeyPressed of CurrentState
  //this->state->keyPressed(evt);
  return true;
}

bool Game::keyReleased(const OIS::KeyEvent &evt) {
  //Call keyReleased of CurrentState
  //this->state->keyReleased(evt);
  return true;
}

bool Game::mouseMoved(const OIS::MouseEvent &evt) {
  // You get the picture
  //this->state->mouseMoved(evt);
  return true;
}

bool Game::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
  //this->state->mousePressed(evt, id);
  return true;
}

bool Game::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
  //this->state->mousePressed(evt, id);
  return true;
}


void Game::stop() {
	Game* game = Game::getSingleton();
	game->running = false;
}
