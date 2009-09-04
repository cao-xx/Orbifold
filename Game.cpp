/*
 *  Game.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "GameState.h"
#include "PlayState.h"
//#include "IntroState.h"
//#include "PauseState.h"
#include "Game.h"
#include "Input.h"
#include "Utils.h"
#include <Ogre/OgreWindowEventUtilities.h>
#include <Ogre/Ogre.h>






Game::Game() {
  this->running = false;

  this->ogre = 0;
  this->window = 0;
  this->input = 0;
  this->state = 0;
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

  Ogre::SceneManager* scene = game->ogre->createSceneManager(Ogre::ST_GENERIC, "ST_GENERIC");

  game->state = PlayState::getSingleton();
  game->state->enter(game, game->window);

  int running = 1000;
  while(running--) {
    game->input->capture();
    game->state->update();
    game->ogre->renderOneFrame();
    Ogre::WindowEventUtilities::messagePump();
  }

  game->shutdown();
  if(game->ogre) OGRE_DELETE game->ogre;
}


// Initialisation

void Game::initialise(){
  this->initOgreRoot();
  this->initOgreResources();
  this->initRenderWindow();
  this->initInput();
  this->initState();
}

void Game::initOgreRoot() {
  Ogre::String workDir = Ogre::StringUtil::BLANK;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
  workDir = macBundlePath() + "/Contents/Resources/";
#endif

  //this->ogre = OGRE_NEW Ogre::Root(workDir + "plugins.cfg", workDir + "Ogre.cfg", workDir + "Ogre.log");
  this->ogre = OGRE_NEW Ogre::Root();
#ifdef _DEBUG
  this->ogre->loadPlugin("RenderSystem_GL_d");
#else
  this->ogre->loadPlugin("RenderSystem_GL");
#endif
  Ogre::RenderSystemList *rs = NULL;
  Ogre::RenderSystemList::iterator r_it;

  rs = this->ogre->getAvailableRenderers();
  r_it = rs->begin();

  if(rs && rs->size() && rs->at(0)->getName().compare("RenderSystem_GL")){
    Ogre::RenderSystem *r=rs->at(0);
    ogre->setRenderSystem(r);
  }else{
    exit(1);
  }
}

void Game::initOgreResources() {
  if(!this->ogre)
    return;
  this->locateResources();
  this->loadResources();
}

void Game::locateResources() {
  Ogre::ConfigFile cf;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
  cf.load(macBundlePath()+"/Contents/Resources/Resources.cfg");
#else
  cf.load("resources.cfg");
#endif

  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  Ogre::String sec, type, arch;


  while (seci.hasMoreElements()) {
    sec = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); i++) {
      type = i->first;
      arch = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
      if (!Ogre::StringUtil::startsWith(arch, "/", false)) {
	arch = Ogre::String(macBundlePath() + "/" + arch);
      }
#endif
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch,type,sec);
    }
  }
}

void Game::loadResources() {
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Game::initRenderWindow() {
  if(!this->ogre)
    return;
  this->ogre->initialise(false);
  this->window = this->ogre->createRenderWindow("Prototyp", 800, 600, false, NULL);
}

void Game::initInput() {
  this->input = InputHandler::getSingleton();
  if(!this->window)
    return;
  this->input->initialise(this->window);
  this->input->addMouseListener(this, "Game");
  this->input->addKeyListener(this, "Game");
}


void Game::initState(){}

// State Handling
GameState* Game::getCurrentState() {
  return this->state;
}

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


bool Game::requestStateChange(GameState* nstate) {

  GameState* pstate = this->state;

  if(pstate) {
    pstate->exit();
  }

  // this is done by exit(), too but just in case
  this->window->removeAllViewports();

  if(nstate) {
    nstate->enter(this, this->window);
  }

  this->state = nstate;
  return true;
}



// Input Handling
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


// Window Handling
void Game::windowResized(Ogre::RenderWindow* rw) {
  //
  if (this->state)
    this->state->windowResized(rw);
  this->input->updateWindowDimensions(rw->getWidth(),rw->getHeight());
  //this does nothing more then:
  //const OIS::MouseState& ms = this->input->mouse->getMouseState();
  //ms.width = rw->getWidth();
  //ms.height = rw->getHeight();
}

void Game::windowMoved(Ogre::RenderWindow* rw) {
  if (this->state)
    this->state->windowMoved(rw);
}

bool Game::windowClosing(Ogre::RenderWindow* rw) {
  if (state)
    return state->windowClosing(rw);
  return true;
}

void Game::windowClosed(Ogre::RenderWindow* rw) {
  if (state)
    state->windowClosed(rw);
}

void Game::windowFocusChange(Ogre::RenderWindow* rw) {
  if (state)
    state->windowFocusChange(rw);
}


void Game::shutdown(){}
void Game::stop() {
  Game* game = Game::getSingleton();
  game->running = false;
}
