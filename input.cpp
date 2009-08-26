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

InputHandler* mInputHandler;

InputHandler::InputHandler() : 
	mMouse(0),
	mKeyboard(0),
	mInputSystem(0) {
}

// InputHandler::initialise : Set up a buffered Mouse and Keyboard.
void InputHandler::initialise(Ogre::RenderWindow *window) {
	if (!mInputSystem) {
		// get window handle
		unsigned long hWnd;
		// TODO: Might be platform dependent
		window->getCustomAttribute("WINDOW", &hWnd);
		
		// we got the window handle, insert it into a parameter list.
		OIS::ParamList pl;
		pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
		m_hWnd = hWnd;
		// create the input system
		mInputSystem = OIS::InputManager::createInputSystem(pl);
		// if possible create a buffered mouse
		if ( mInputSystem->getNumberOfDevices(OIS::OISMouse) > 0) {
			mMouse = static_cast<OIS::Mouse*>(mInputSystem->createInputObject(OIS::OISMouse, true));
			mMouse->setEventCallback(this);
			
			// get window metrics and set initial mouse region
			unsigned int width, height, depth;
			int left, top;
			window->getMetrics(width, height, depth, left, top);
			
			this->setWindowDimensions(width, height);			
		}
		// and buffered keyboard
		if ( mInputSystem->getNumberOfDevices(OIS::OISKeyboard) > 0) {
			mKeyboard = static_cast<OIS::Keyboard*>(mInputSystem->createInputObject(OIS::OISKeyboard, true));
			mKeyboard->setEventCallback(this);
		}
	}
	//m_game = game;
}

InputHandler::~InputHandler() {
	if(mInputSystem) {
		if (mMouse)
			mInputSystem->destroyInputObject(mMouse);
		if (mKeyboard)
			mInputSystem->destroyInputObject(mKeyboard);
		
		OIS::InputManager::destroyInputSystem(mInputSystem);
		
		//clear listeners
		mKeyListeners.clear();
		mMouseListeners.clear();
	}
}

//TODO: Might need to check if present.
void InputHandler::capture() {
  mMouse->capture();
  mKeyboard->capture();
}

void InputHandler::setWindowDimensions(int width, int height){
  //TODO: Update if window resizes
  const OIS::MouseState &ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}


// Manage Listeners.
void InputHandler::addKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName) {
    if(mKeyboard) {
        // Check for duplicate items
        itKeyListener = mKeyListeners.find(instanceName);
        if(itKeyListener == mKeyListeners.end()) {
            mKeyListeners[instanceName] = keyListener;
        }
        else {
            // Duplicate Item
        }
    }
}

void InputHandler::addMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName) {
    if(mMouse) {
        // Check for duplicate items
        itMouseListener = mMouseListeners.find(instanceName);
        if(itMouseListener == mMouseListeners.end()) {
            mMouseListeners[instanceName] = mouseListener;
        }
        else {
            // Duplicate Item
        }
    }
}

void InputHandler::removeKeyListener(const std::string& instanceName) {
    // Check if item exists
    itKeyListener = mKeyListeners.find(instanceName);
    if( itKeyListener != mKeyListeners.end()) {
        mKeyListeners.erase(itKeyListener);
    }
    else {
        // Doesn't Exist
    }
}

void InputHandler::removeMouseListener( const std::string& instanceName ) {
    // Check if item exists
    itMouseListener = mMouseListeners.find(instanceName);
    if(itMouseListener != mMouseListeners.end()) {
        mMouseListeners.erase(itMouseListener);
    }
    else {
        // Doesn't Exist
    }
}

void InputHandler::removeKeyListener(OIS::KeyListener *keyListener) {
    itKeyListener    = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if( itKeyListener->second == keyListener ) {
            mKeyListeners.erase( itKeyListener );
            break;
        }
    }
}

void InputHandler::removeMouseListener(OIS::MouseListener *mouseListener) {
    itMouseListener    = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
        if(itMouseListener->second == mouseListener) {
            mMouseListeners.erase(itMouseListener);
            break;
        }
    }
}

void InputHandler::removeAllKeyListeners() {
    mKeyListeners.clear();
}

void InputHandler::removeAllMouseListeners() {
    mMouseListeners.clear();
}

void InputHandler::removeAllListeners() {
	this->removeAllKeyListeners();
	this->removeAllMouseListeners();
}

OIS::Mouse* InputHandler::getMouse() {
	return mMouse;
}

OIS::Keyboard* InputHandler::getKeyboard() {
	return mKeyboard;
}

bool InputHandler::keyPressed(const OIS::KeyEvent &e) {
    itKeyListener = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener) {
        if(!itKeyListener->second->keyPressed(e))
			break;
    }
	
    return true;
}

bool InputHandler::keyReleased(const OIS::KeyEvent &e) {
    itKeyListener = mKeyListeners.begin();
    itKeyListenerEnd = mKeyListeners.end();
    for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
        if(!itKeyListener->second->keyReleased(e))
			break;
    }
	
    return true;
}

bool InputHandler::mouseMoved(const OIS::MouseEvent &e) {
    itMouseListener = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
        if(!itMouseListener->second->mouseMoved(e))
			break;
    }
	
    return true;
}

bool InputHandler::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
    itMouseListener = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
        if(!itMouseListener->second->mousePressed(e, id))
			break;
    }
	
    return true;
}

bool InputHandler::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
    itMouseListener = mMouseListeners.begin();
    itMouseListenerEnd = mMouseListeners.end();
    for(; itMouseListener != itMouseListenerEnd; ++itMouseListener) {
        if(!itMouseListener->second->mouseReleased(e, id))
			break;
    }
	
    return true;
}

InputHandler* InputHandler::getSingletonPtr() {
	if(!mInputHandler)
		mInputHandler = new InputHandler();
	return mInputHandler;
}