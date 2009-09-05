/*
 *  MenuState.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 05.09.09.
 *  Copyright 2009 Orbifold. All rights reserved.
 *
 */

#include "MenuState.h"
#include "Game.h"

namespace Orbifold {
  
  class Game;
  class SdkTrayManager;
  
  MenuState::MenuState() {
    this->ogre = 0;
    this->window = 0;
    this->scene = 0;
    this->game = 0;
    this->tray = 0;
  }
  
  MenuState::~MenuState() {
    if(this->instance) {
      delete this->instance;
    }
  }
  
  MenuState* MenuState::instance = 0;
  
  MenuState* MenuState::getSingleton() {
    if(!instance) {
      instance = new MenuState();
    }
    return instance;
  }
  
  void MenuState::enter(Game* game, Ogre::RenderWindow* window) {
    MenuState* state = MenuState::getSingleton();
    state->ogre = Ogre::Root::getSingletonPtr();
    state->window = window;
    state->game = game;
    
    locateResources();
    
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
    
    state->tray = new SdkTrayManager("BrowserControls", state->window, state->game->getMouse(), state);
    state->tray->showBackdrop("SdkTrays/Bands");
    state->tray->getTrayContainer(TL_NONE)->hide();
    
    createDummyScene();
    loadResources();
    
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    
    setupWidgets();
    windowResized(state->window);
  }
  

  void MenuState::setupWidgets() {
  this->tray->destroyAllWidgets();
  
  //create main navigation tray
  this->tray->showLogo(TL_RIGHT);
  this->tray->createSeparator(TL_RIGHT, "LogoSep");
  this->tray->createButton(TL_RIGHT, "StartStop", "Start Game");
  this->tray->createButton(TL_RIGHT, "Configure", "Configure");
  this->tray->createButton(TL_RIGHT, "Quit", "Quit");
  
  // create configuration screen button tray
  this->tray->createButton(TL_NONE, "Apply", "Apply Changes");
  this->tray->createButton(TL_NONE, "Back", "Go Back");
  
  // create configuration screen label and renderer menu
  this->tray->createLabel(TL_NONE, "ConfigLabel", "Configuration");
  this->rendererMenu = this->tray->createLongSelectMenu(TL_NONE, "RenderMenu", "Render System", 450, 240, 10);
  
  // populate render system names
  /* Ogre::StringVector rsNames;
  Ogre::RenderSystemList* rsList = this->ogre->getAvailableRenderers();
  for (unsigned int i = 0; i < rsList.size(); i++) {
    rsNames.push_back(rsList[i]->getName());
  }
  this->rendererMenu->setItems(rsNames);*/
}

  void MenuState::createDummyScene() {
  this->window->removeAllViewports();
  Ogre::SceneManager* sm = this->ogre->createSceneManager(Ogre::ST_GENERIC, "DummyScene");
  Ogre::Camera* cam = sm->createCamera("DummyCamera");
  Ogre::Viewport* vp = this->window->addViewport(cam);
}

  void MenuState::destroyDummyScene() {
  this->window->removeAllViewports();
  this->ogre->destroySceneManager(this->ogre->getSceneManager("DummyScene"));
}
  
  // Mouse / Keyboardhandling
  
  void MenuState::exit() {
    MenuState* state = MenuState::getSingleton();
    if (state->scene) state->scene->clearScene();
    if (contentSetup) state->cleanupContent();
    contentSetup = false;
    if (resourcesLoaded) state->unloadResources();
    resourcesLoaded = false;
    if (state->scene) state->ogre->destroySceneManager(state->scene);
    state->scene = 0;
  }
  
  void MenuState::setupContent(){}
  void MenuState::cleanupContent(){}
  
  void MenuState::locateResources(){}
  void MenuState::loadResources(){}
  void MenuState::unloadResources(){}
  
  // A lot of stubs.
  void MenuState::pause() {}
  void MenuState::resume() {}
  void MenuState::update() {this->tray->update();}
  
  
  
  void MenuState::keyPressed(const OIS::KeyEvent &evt) {}
  void MenuState::keyReleased(const OIS::KeyEvent &evt) {
    if (evt.key == OIS::KC_SPACE) {
      //mGame->requestStateChange(PAUSE);
    } else if(evt.key == OIS::KC_ESCAPE) {
      //this->game->requestStateChange(SHUTDOWN);
    }
  }
  
  void MenuState::mouseMoved(const OIS::MouseEvent &evt) {
    //const OIS::MouseState &mouseState = evt.state;
    // Update Mousepointer on Screen, might be smoother if moved by relative change.
    // mMousePointer->setTop(mouseState.Y.abs);
    // mMousePointer->setLeft(mouseState.X.abs);
  }
  
  void MenuState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
  void MenuState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {}
  
  
  void MenuState::windowResized(Ogre::RenderWindow* rw) {}
  void MenuState::windowMoved(Ogre::RenderWindow* rw) {}
  bool MenuState::windowClosing(Ogre::RenderWindow* rw) {return true;}
  void MenuState::windowClosed(Ogre::RenderWindow* rw) {}
  void MenuState::windowFocusChange(Ogre::RenderWindow* rw) {}
  
}
