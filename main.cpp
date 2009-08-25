/*
Author: Christian Pehle
*/


#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	#include <Carbon/Carbon.h>
#endif

#include "input.h"
#include "game.h"

#include <Ogre.h>
#include "OgreWindowEventUtilities.h"


#define MANUALLY_CREATE_WINDOW 1

void initResources(){
	Ogre::ResourceGroupManager &resources=Ogre::ResourceGroupManager::getSingleton();
	resources.addResourceLocation("data","FileSystem");
	resources.initialiseAllResourceGroups();
}


Ogre::Root* initOgre(){

Ogre::Root* ogre = new Ogre::Root;

#if defined(_DEBUG)
	ogre->loadPlugin("RenderSystem_GL_d");
#else
	ogre->loadPlugin("RenderSystem_GL");
#endif
	Ogre::RenderSystemList *rs = NULL;
	Ogre::RenderSystemList::iterator r_it;

	rs = ogre->getAvailableRenderers();
	r_it = rs->begin();

	if(rs && rs->size() && rs->at(0)->getName().compare("RenderSystem_GL")){
		Ogre::RenderSystem * r=rs->at(0);
		ogre->setRenderSystem(r);
	}else{
		exit(1);
	}

	initResources();

	return ogre;
}


Ogre::Camera* createCamera(Ogre::SceneManager *sceneMgr, Ogre::RenderWindow *window) {
	Ogre::Camera* cam = sceneMgr->createCamera("SimpleCamera");
	cam->setPosition(Ogre::Vector3(0.0f,0.0f,500.0f));
	cam->lookAt(Ogre::Vector3(0.0f,0.0f,0.0f));
	cam->setNearClipDistance(5.0f);
	cam->setFarClipDistance(5000.0f);

	Ogre::Viewport* v = window->addViewport(cam);
	v->setBackgroundColour(Ogre::ColourValue(0.5,0.5,0.5));

	cam->setAspectRatio(Ogre::Real(v->getActualWidth())/v->getActualHeight());

	return cam;
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT){
#else
int main(int argc, char **argv){
#endif

	Ogre::Root *ogre=initOgre();

#if MANUALLY_CREATE_WINDOW
	ogre->initialise(false);
	Ogre::RenderWindow* window = ogre->createRenderWindow("Simple Ogre App", 800, 600, false, NULL);
#else
	ogre->getRenderSystem()->setConfigOption("Full Screen", "No");
	ogre->getRenderSystem()->setConfigOption("Video Mode","800 x 600 @ 16-bit colour");
	Ogre::RenderWindow* window = ogre->initialise(true, "Simple Ogre App");
#endif
		
		
	Ogre::SceneManager* sceneMgr = ogre->createSceneManager(Ogre::ST_GENERIC);

	Ogre::Camera *cam=createCamera(sceneMgr,window);
	sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(cam);

	// Input Handler	
	unsigned long hWnd;
	window->getCustomAttribute("WINDOW", &hWnd);
	
	// set up input handler
		
	Game *game = new Game();
	InputHandler *handler = new InputHandler(game, hWnd);
	game->requestStateChange(GAME);
		
	int running=1000;
	while(running--)
	{
		//Ogre::WindowEventUtilities::messagePump();
		ogre->renderOneFrame();
		printf("%d\n",running);
	}

	
	delete handler;
	delete game;
	delete ogre;
	return 0;
}

