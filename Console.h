/*
 *  Console.h
 *  Prototyp
 *
 *
 *  Taken mostly from the Ogre Wiki.
 */

#ifndef Console_H
#define Console_H

namespace Orbifold {
#include <Ogre/Ogre.h>
#include <OIS/OIS.h>

//#include <list>
//#include <vector>

  using namespace std;
  using namespace Ogre;
  
  class Console:
                 public Ogre::LogListener,
                 public OIS::KeyListener
  {
  public:
    Console();
    ~Console();
    
    void initialise(Ogre::Root *ogre);
    void shutdown();
    
    void setVisible(bool visible);
    bool isVisible(){return visible;}
    
    void print(const String &text);
    
    void update();
    
    static Console* getSingleton();
    
    bool keyPressed(const OIS::KeyEvent &evt);
    bool keyReleased(const OIS::KeyEvent &evt);
    
    //void onKeyPressed(const OIS::KeyEvent &arg);
    
    void addCommand(const String &command, void (*)(vector<String>&));
    void removeCommand(const String &command);
    
    //log
    void messageLogged( const String& message, LogMessageLevel lml, bool maskDebug, const String &logName ) {print(logName+": "+message);}
  private:
    bool            visible;
    bool            initialized;
    Ogre::Root         *ogre;
    Ogre::SceneManager   *scene;
    Ogre::Rectangle2D   *rect;
    Ogre::SceneNode      *node;
    Ogre::OverlayElement *textbox;
    Ogre::Overlay      *overlay;
    
    float            height;
    bool            update_overlay;
    int               start_line;
    list<Ogre::String>      lines;
    String            prompt;
    map<String,void (*)(vector<String>&)>  commands;
  };


}
#endif