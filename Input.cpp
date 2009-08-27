/*
 *  Input.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "Input.h"
#include "OgreStringConverter.h"
#include "Game.h"



InputHandler::InputHandler() {
  this->inputsystem = 0;
  this->mouse = 0;
  this->keyboard = 0;
}

InputHandler::~InputHandler() {
  if(this->instance) {
    delete this->instance;
  }
  if(this->inputsystem) {
    if(this->mouse)
      this->inputsystem->destroyInputObject(this->mouse);
    if(this->keyboard)
      this->inputsystem->destroyInputObject(this->keyboard);
  }

  this->keyListeners.clear();
  this->mouseListeners.clear();
}

InputHandler* InputHandler::instance = 0;

InputHandler* InputHandler::getSingletonPtr() {
  if(!instance)
    instance = new InputHandler();
  return instance;
}

// InputHandler::initialise : Set up a buffered Mouse and Keyboard.
void InputHandler::initialise(Ogre::RenderWindow *window) {

  InputHandler* hdl = InputHandler::getSingletonPtr();

  // get window handle

  unsigned long hWnd;
  window->getCustomAttribute("WINDOW", &hWnd);

  // we got the window handle, insert it into a parameter list

  OIS::ParamList pl;
  pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

  // create the input system

  hdl->inputsystem = OIS::InputManager::createInputSystem(pl);

  // if possible create a buffered mouse

  if (hdl->inputsystem->getNumberOfDevices(OIS::OISMouse) > 0) {
    hdl->mouse = static_cast<OIS::Mouse*>(mInputSystem->createInputObject(OIS::OISMouse, true));
    hdl->mouse->setEventCallback(this);

    // get window metrics and set initial mouse region

    unsigned int width, height, depth;
    int left, top;
    window->getMetrics(width, height, depth, left, top);

    hdl->updateWindowDimensions(width, height);
  }

  // and create a buffered keyboard

  if ( mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0) {
    hdl->keyboard = static_cast<OIS::Keyboard*>(mInputSystem->createInputObject(OIS::OISKeyboard, true));
    mKeyboard->setEventCallback(this);
  }
}


void InputHandler::capture() {
  this->mouse->capture();
  this->keyboard->capture();
}

void InputHandler::updateWindowDimensions(int width, int height){
  const OIS::MouseState &ms = this->mouse->getMouseState();
  ms.width = width;
  ms.height = height;
}


// Manage Listeners.
void InputHandler::addKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName) {
    if(this->keyboard) {
        // Check for duplicate items
        itKeyListener = keyListeners.find(instanceName);
        if(itKeyListener == keyListeners.end()) {
            keyListeners[instanceName] = keyListener;
        }
        else {
            // Duplicate Item
        }
    }
}

void InputHandler::addMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName) {
    if(this->mouse) {
        // Check for duplicate items
        itMouseListener = mouseListeners.find(instanceName);
        if(itMouseListener == mouseListeners.end()) {
            mouseListeners[instanceName] = mouseListener;
        }
        else {
            // Duplicate Item
        }
    }
}

void InputHandler::removeKeyListener(const std::string& instanceName) {
    // Check if item exists
    itKeyListener = keyListeners.find(instanceName);
    if( itKeyListener != keyListeners.end()) {
        keyListeners.erase(itKeyListener);
    }
    else {
        // Doesn't Exist
    }
}

void InputHandler::removeMouseListener( const std::string& instanceName ) {
    // Check if item exists
    itMouseListener = mouseListeners.find(instanceName);
    if(itMouseListener != mouseListeners.end()) {
      mouseListeners.erase(itMouseListener);
    }
    else {
        // Doesn't Exist
    }
}

void InputHandler::removeKeyListener(OIS::KeyListener *keyListener) {
    itKeyListener    = keyListeners.begin();
    itKeyListenerEnd = keyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if( itKeyListener->second == keyListener ) {
            keyListeners.erase( itKeyListener );
            break;
        }
    }
}

void InputHandler::removeMouseListener(OIS::MouseListener *mouseListener) {
    itMouseListener    = mouseListeners.begin();
    itMouseListenerEnd = mouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
        if(itMouseListener->second == mouseListener) {
            mouseListeners.erase(itMouseListener);
            break;
        }
    }
}

void InputHandler::removeAllKeyListeners() {
    keyListeners.clear();
}

void InputHandler::removeAllMouseListeners() {
    mouseListeners.clear();
}

void InputHandler::removeAllListeners() {
	this->removeAllKeyListeners();
	this->removeAllMouseListeners();
}

OIS::Mouse* InputHandler::getMouse() {
	return this->mouse;
}

OIS::Keyboard* InputHandler::getKeyboard() {
	return this->keyboard;
}

bool InputHandler::keyPressed(const OIS::KeyEvent &e) {
    itKeyListener = keyListeners.begin();
    itKeyListenerEnd = keyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener) {
        if(!itKeyListener->second->keyPressed(e))
			break;
    }

    return true;
}

bool InputHandler::keyReleased(const OIS::KeyEvent &e) {
    itKeyListener = keyListeners.begin();
    itKeyListenerEnd = keyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyReleased(e))
			break;
    }

    return true;
}

bool InputHandler::mouseMoved(const OIS::MouseEvent &e) {
    itMouseListener = mouseListeners.begin();
    itMouseListenerEnd = mouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
        if(!itMouseListener->second->mouseMoved(e))
			break;
    }

    return true;
}

bool InputHandler::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
    itMouseListener = mouseListeners.begin();
    itMouseListenerEnd = mouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
        if(!itMouseListener->second->mousePressed(e, id))
			break;
    }

    return true;
}

bool InputHandler::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
    itMouseListener = mouseListeners.begin();
    itMouseListenerEnd = mouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
        if(!itMouseListener->second->mouseReleased(e, id))
			break;
    }

    return true;
}

