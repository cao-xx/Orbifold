/*
 *  input.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#pragma once

#include "OISEvents.h"
#include "OISInputManager.h"
#include "OISMouse.h"
#include "OISKeyboard.h"

class Game;

class InputHandler :
	public OIS::MousListener,
	public OIS::Keylistener
{
	private :
		OIS::InputManager *m_ois;
		OIS::Mouse *mMouse;
		OIS::Keyboard *mKeyboard;
		unsigned long m_hWnd;
	public:
		InputHandler(Game *game; unsigned long hWnd);
		~InputHandler();

		void setWindowDimensions(int width, int height);
		void capture();

		// MouseListener
		bool mouseMoved(const OIS::MouseEvent &evt);
		bool mousePressed(const OIS::MouseEvent &evt);
		bool mousReleased(const OIS::MouseEvent &evt);

		//Keylistener
		bool keyPressed(const OIS::KeyEvent &evt);
		bool keyReleased(const OIS::KeyEvent &ev);
};
