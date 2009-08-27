/*
 *  Input.h
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
public:

  void static initialise(Ogre::RenderWindow *window);
  void static shutdown();

  void capture();
  void updateWindowDimensions(int height, int width);

  //Mouse
 
  void addMouseListener(OIS::MouseListener *mouseListener, const std::string& instanceName);
  void removeMouseListener(const std::string& instanceName);
  void removeMouseListener(OIS::MouseListener *mouseListener);
  void removeAllMouseListeners();

  //Keyboard

  void addKeyListener(OIS::KeyListener *keyListener, const std::string& instanceName);
  void removeKeyListener(const std::string& instanceName);
  void removeKeyListener(OIS::KeyListener *keyListener);
  void removeAllKeyListeners();
  
  //

  void removeAllListeners();  
  
  //Callbacks

  bool mouseMoved(const OIS::MouseEvent &evt);
  bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
  bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);
  
  bool keyPressed(const OIS::KeyEvent &evt);
  bool keyReleased(const OIS::KeyEvent &evt);

  //

  OIS::Mouse* getMouse();
  OIS::Keyboard* getKeyboard();  

protected:

  static Input* instance;

  OIS::InputManager *inputsystem;
  OIS::Mouse *mouse;
  OIS::Keyboard *keyboard;

  std::map<std::string, OIS::KeyListener*> keyListeners;
  std::map<std::string, OIS::MouseListener*> mouseListeners;
  
  std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
  std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;

  std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
  std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;

private:

  InputHandler();
  ~InputHandler();

  unsigned long hWnd;

};
#endif
