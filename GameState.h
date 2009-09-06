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


#include <Ogre/OgreRoot.h>
#include <Ogre/OgreRenderWindow.h>
#include <Ogre/OgreOverlayElement.h>
#include <Ogre/OgreOverlayManager.h>
#include <Ogre/OgreStringConverter.h>

#include "Game.h"

namespace Orbifold {


class GameState {

public:
  virtual void enter(Game* game, Ogre::RenderWindow *window) = 0;
  virtual void exit() = 0;

  virtual void update() = 0;

  virtual bool keyPressed(const OIS::KeyEvent &evt) = 0;
  virtual bool keyReleased(const OIS::KeyEvent &evt) = 0;

  virtual bool mouseMoved(const OIS::MouseEvent &evt) = 0;
  virtual bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
  virtual bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;

  virtual void windowResized(Ogre::RenderWindow* rw) = 0;
  virtual void windowMoved(Ogre::RenderWindow* rw) = 0;
  virtual bool windowClosing(Ogre::RenderWindow* rw) = 0;
  virtual void windowClosed(Ogre::RenderWindow* rw) = 0;
  virtual void windowFocusChange(Ogre::RenderWindow* rw) = 0;
  
protected:
  GameState(){}
  ~GameState(){}
    
};
  
}
#endif
