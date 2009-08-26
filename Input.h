/*
 *  input.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#ifndef InputManager_H
#define InputManager_H

#include <OIS/OISInputManager.h>
#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

#include <OgreRenderWindow.h>

class Game;

class InputHandler :
	public OIS::MouseListener,
	public OIS::KeyListener
{
	private :
		InputHandler();

		OIS::InputManager *mInputSystem;
		OIS::Mouse *mMouse;
		OIS::Keyboard *mKeyboard;

		static InputHandler *mInputHandler;

		unsigned long m_hWnd;
		//Game *m_game;

		std::map<std::string, OIS::KeyListener*> mKeyListeners;
		std::map<std::string, OIS::MouseListener*> mMouseListeners;

		std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
		std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;

		std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
		std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;

	public:
		~InputHandler();

		//void initialise(Game *game, Ogre::RenderWindow *window);
		void initialise(Ogre::RenderWindow *window);
		void setWindowDimensions(int width, int height);
		void capture();

		// Listeners

		// MouseListener
		void addMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName);
		void removeMouseListener(const std::string& instanceName);
		void removeMouseListener(OIS::MouseListener *mouseListener);
		void removeAllMouseListeners();

		bool mouseMoved(const OIS::MouseEvent &evt);
		bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
		bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);

		//Keylistener
		void addKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName);
		void removeKeyListener(const std::string& instanceName);
		void removeKeyListener(OIS::KeyListener *keyListener);
		void removeAllKeyListeners();

		bool keyPressed(const OIS::KeyEvent &evt);
		bool keyReleased(const OIS::KeyEvent &evt);

		//

		void removeAllListeners();

		//

		OIS::Mouse* getMouse();
		OIS::Keyboard* getKeyboard();

		static InputHandler* getSingletonPtr();
};
#endif
