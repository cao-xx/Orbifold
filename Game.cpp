/*
 *  Game.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "GameState.h"
#include "MenuState.h"
#include "Game.h"
#include "Input.h"
#include "Utils.h"
#include <Ogre/OgreWindowEventUtilities.h>
#include <Ogre/Ogre.h>



namespace Orbifold {


  Game::Game() :
    running(false),
    ogre(0),
    window(0),
    input(0),
    state(0) {}

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


    //game->requestStateChange(PlayState::getSingleton());

    game->requestStateChange(MenuState::getSingleton());


    while(game->running) {
      game->input->capture();
      game->state->update();
      game->ogre->renderOneFrame();
      Ogre::WindowEventUtilities::messagePump();
    }

    game->shutdown();
    if(game->ogre) OGRE_DELETE game->ogre;
  }


  // Initialisation ///////////////////////////////////////////////////////

  void Game::initialise(){
    this->initOgreRoot();
    this->initPlugins();
    // RenderWindow has to be initialised before Materialscripts are parsed (in initOgreResources)!
    this->initRenderWindow();
    this->initOgreResources();
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

  void Game::initPlugins() {
    // necessary for TerrainManager
    this->ogre->loadPlugin("Plugin_OctreeSceneManager");

  }

  void Game::initRenderWindow() {
    if(!this->ogre)
      return;
    this->ogre->initialise(false);
    this->window = this->ogre->createRenderWindow("Prototyp", 800, 600, false, NULL);
    // register game to receive window events.
    Ogre::WindowEventUtilities::addWindowEventListener(this->window, this);
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
    cf.load(macBundlePath()+"/Contents/Resources/resources.cfg");
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

  void Game::initInput() {
    this->input = InputHandler::getSingleton();
    if(!this->window)
      return;
    this->input->initialise(this->window);
    this->input->addMouseListener(this, "Game");
    this->input->addKeyListener(this, "Game");
  }

  void Game::initState(){}

  
  // State Handling ///////////////////////////////////////////////////////
  
  GameState* Game::getCurrentState() {
    return this->state;
  }

  bool Game::requestStateChange(GameState* nstate) {
    Game* game = Game::getSingleton();
    GameState* pstate = game->state;

    if(pstate) {
      pstate->save();
      pstate->exit();
    }

    game->window->removeAllViewports();

    if(nstate) {
      nstate->restore();
      nstate->enter();
    }

    game->state = nstate;
    return true;
  }



  // Input Handling
  bool Game::keyPressed(const OIS::KeyEvent &evt) {
    //Call KeyPressed of CurrentState
    this->state->keyPressed(evt);
    return true;
  }

  bool Game::keyReleased(const OIS::KeyEvent &evt) {
    //Call keyReleased of CurrentState
    this->state->keyReleased(evt);
    return true;
  }

  bool Game::mouseMoved(const OIS::MouseEvent &evt) {
    // You get the picture
    this->state->mouseMoved(evt);
    return true;
  }

  bool Game::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    this->state->mousePressed(evt, id);
    return true;
  }

  bool Game::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
    this->state->mouseReleased(evt, id);
    return true;
  }

  OIS::Mouse* Game::getMouse() {
    return Game::getSingleton()->input->getMouse();
  }

  OIS::Keyboard* Game::getKeyboard() {
    return Game::getSingleton()->input->getKeyboard();
  }


  // Window Handling
  
  Ogre::RenderWindow* Game::getRenderWindow() {
    return Game::getSingleton()->window;
  }
  
  void Game::windowResized(Ogre::RenderWindow* rw) {
    //
    if (this->state)
      this->state->windowResized(rw);
    this->input->updateWindowDimensions(rw->getWidth(),rw->getHeight());
  }

  void Game::windowMoved(Ogre::RenderWindow* rw) {
    if (this->state)
      this->state->windowMoved(rw);
  }

  bool Game::windowClosing(Ogre::RenderWindow* rw) {
    this->running = false;
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

}
