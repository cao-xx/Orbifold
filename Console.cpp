/*
 *  Console.cpp
 *  Prototyp
 *
 *  Taken mostly from the Ogre Wiki.
 *
 */

#include "Console.h"
#include "Input.h"


namespace Orbifold {
  


#define CONSOLE_LINE_LENGTH 85
#define CONSOLE_LINE_COUNT 15
Console::Console(){
  start_line=0;
}

Console::~Console(){
  
}
  
Console* Console::instance = 0;

  Console* Console::getSingleton() {
    if(!instance) {
      instance = new Console();
    }
    return instance;
  }
  
  
  
void Console::initialise(Ogre::Root *ogre){
  if(!ogre->getSceneManagerIterator().hasMoreElements())
    OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "No scene manager found!", "init" );
  
  this->ogre = ogre;
  scene = ogre->getSceneManagerIterator().getNext();
  
  height = 1;
  
  // Create background rectangle covering the whole screen
  rect = new Rectangle2D(true);
  rect->setCorners(-1, 1, 1, 1-height);
  rect->setMaterial("console/background");
  rect->setRenderQueueGroup(RENDER_QUEUE_OVERLAY);
  rect->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE));
  node = scene->getRootSceneNode()->createChildSceneNode("#Console");
  node->attachObject(rect);
  
  textbox=OverlayManager::getSingleton().createOverlayElement("TextArea","ConsoleText");
  textbox->setCaption("hello");
  textbox->setMetricsMode(GMM_RELATIVE);
  textbox->setPosition(0,0);
  textbox->setParameter("font_name","Console");
  textbox->setParameter("colour_top","1 1 1");
  textbox->setParameter("colour_bottom","1 1 1");
  textbox->setParameter("char_height","0.03");
  
  overlay=OverlayManager::getSingleton().create("Console");   
  overlay->add2D((OverlayContainer*)textbox);
  overlay->show();
  LogManager::getSingleton().getDefaultLog()->addListener(this);
  InputHandler::getSingleton()->addKeyListener(this);
}

void Console::shutdown(){
  if(!initialized)
    return;
  delete rect;
  delete node;
  delete textbox;
  delete overlay;
}
void Console::keyPressed(const OIS::KeyEvent &arg){
  if(!visible)
    return;
  if (arg.key == OIS::KC_RETURN)
  {
    //split the parameter list
    const char *str=prompt.c_str();
    vector<String> params;
    String param="";
    for(int c=0;c<prompt.length();c++){
      if(str[c]==' '){
        if(param.length())
          params.push_back(param);
        param="";
      }
      else
        param+=str[c];
    }
    if(param.length())
      params.push_back(param);
    
    //try to execute the command
    map<String,void(*)(vector<String>&)>::iterator i;
    for(i=commands.begin();i!=commands.end();i++){
      if((*i).first==params[0]){
        if((*i).second)
          (*i).second(params);
        break;
      }
    }
    
    print(prompt);
    prompt="";
  }
  if (arg.key == OIS::KC_BACK)
    prompt=prompt.substr(0,prompt.length()-1);
  if (arg.key == OIS::KC_PGUP)
  {
    if(start_line>0)
      start_line--;
  }
  if (arg.key == OIS::KC_PGDOWN)
  {
    if(start_line<lines.size())
      start_line++;
  }
  else
  {
    char legalchars[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890+!\"#%&/()=?[]\\*-_.:,; ";
    for(int c=0;c<sizeof(legalchars);c++){
      if(legalchars[c]==arg.text){
        prompt+=arg.text;
        break;
      }
    }
  }
  update_overlay=true;
}
bool Console::update(){
  if(visible&&height<1){
    textbox->show();
    if(height>=1){
      height=1;
    }
  }
  else if(!visible&&height>0){
    //height-=evt.timeSinceLastFrame*2;
    if(height<=0){
      height=0;
      textbox->hide();
    }
  }
  
  textbox->setPosition(0,(height-1)*0.5);
  rect->setCorners(-1,1+height,1,1-height);
  
  if(update_overlay){
    String text;
    list<String>::iterator i,start,end;
    
    //make sure is in range
    if(start_line>lines.size())
      start_line=lines.size();
    
    int lcount=0;
    start=lines.begin();
    for(int c=0;c<start_line;c++)
      start++;
    end=start;
    for(int c=0;c<CONSOLE_LINE_COUNT;c++){
      if(end==lines.end())
        break;
      end++;
    }
    for(i=start;i!=end;i++)
      text+=(*i)+"\n";
    
    //add the prompt
    text+="] "+prompt;
    
    textbox->setCaption(text);
    update_overlay=false;
  }
  return true;
}

void Console::print(const String &text){
  //subdivide it into lines
  const char *str=text.c_str();
  int start=0,count=0;
  int len=text.length();
  String line;
  for(int c=0;c<len;c++){
    if(str[c]=='\n'||line.length()>=CONSOLE_LINE_LENGTH){
      lines.push_back(line);
      line="";
    }
    if(str[c]!='\n')
      line+=str[c];
  }
  if(line.length())
    lines.push_back(line);
  if(lines.size()>CONSOLE_LINE_COUNT)
    start_line=lines.size()-CONSOLE_LINE_COUNT;
  else
    start_line=0;
  update_overlay=true;
}

void Console::setVisible(bool visible){
  this->visible=visible;
}

void Console::addCommand(const String &command, void (*func)(vector<String>&)){
  commands[command]=func;
}

void Console::removeCommand(const String &command){
  commands.erase(commands.find(command));
}

}