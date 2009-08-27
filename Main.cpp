/*
Author: Christian Pehle
*/


#include "Game.h"


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT){
#else
int main(int argc, char **argv){
#endif


	Game *game = Game::getSingletonPtr();
	game->startGame();

	delete game;
	return 0;
}

