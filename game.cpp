/*
 *  game.cpp
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#include "game.h"
#include "OgreStringConverter.h"

Game::Game() {
	m_state = STARTUP;
}

Game::~Game(){}

GameState Game::getCurrentState() {
	return m_state;
}

bool Game::lockState() {
	if (m_locked == false)
		return m_locked = true;
	else
		return false;
}

bool Game::requestStateChange(GameState newState) {
	if (m_state == STARTUP) {
		m_locked = false;
		m_state = newState;

		return true;
	}

	// this state cannot be changed once initiated
	if (m_state == SHUTDOWN) {
		return false;
	}

	if ((m_state == GUI || m_state == GAME || m_state == LOADING || m_state == CANCEL_LOADING) &&
		(newState != STARTUP) && (newState != m_state)) {
		m_state = newState;
		return true;
	}
	else
		return false;
}

void Game::setFrameTime(float ms) {
	m_frame_time = ms;
}

