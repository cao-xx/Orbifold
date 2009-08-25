/*
 *  input.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "input.h"
#include "OgreStringConverter.h"
#include "game.h"

InputHandler::InputHandler(Game *game, unsigned long hWnd) {
	
	OIS::ParamList pl;
	pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

	m_hWnd = hWnd;
	m_ois = OIS::InputManager::createInputSystem(pl);
	mMouse = static_cast<OIS::Mouse*>(m_ois->createInputObject(OIS::OISMouse, true));
	mKeyboard = static_cast<OIS::Keyboard*>(m_ois->createInputObject(OIS::OISKeyboard, true));
	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	m_game = game;
}

InputHandler::~InputHandler() {
  if (mMouse)
    m_ois->destroyInputObject(mMouse);
  if (mKeyboard)
    m_ois->destroyInputObject(mKeyboard);

  OIS::InputManager::destroyInputSystem(m_ois);
}

void InputHandler::capture() {
  mMouse->capture();
  mKeyboard->capture();
}

void::InputHandler::setWindowDimensions(int width, int height){
  //TODO: Update if window resizes
  const OIS::MouseState &ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

//MouseListener: Just a stub for now.
bool InputHandler::mouseMoved(const OIS::MouseEvent &evt) {
  return true;
}

bool InputHandler::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID bid) {
  return true;
}

bool InputHandler::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID bid) {
  return true;
}

//Keylistener: Just a stub for now.
bool InputHandler::keyPressed(const OIS::KeyEvent &evt) {
  return true;
}

bool InputHandler::keyReleased(const OIS::KeyEvent &evt) {
  if (evt.key == OIS::KC_ESCAPE)
    m_game->requestStateChange(SHUTDOWN);
  return true;
}

