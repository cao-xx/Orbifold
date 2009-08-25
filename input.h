/*
 *  input.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#pragma once

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

class Game;

class InputHandler :
	public OIS::MouseListener,
	public OIS::KeyListener
{
	private :
		OIS::InputManager *m_ois;
		OIS::Mouse *mMouse;
		OIS::Keyboard *mKeyboard;
		unsigned long m_hWnd;
		Game *m_game;	
	public:
		InputHandler(Game *game, unsigned long hWnd);
		~InputHandler();

		void setWindowDimensions(int width, int height);
		void capture();

		// MouseListener
		bool mouseMoved(const OIS::MouseEvent &evt);
		bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
		bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);

		//Keylistener
		bool keyPressed(const OIS::KeyEvent &evt);
		bool keyReleased(const OIS::KeyEvent &ev);
};
