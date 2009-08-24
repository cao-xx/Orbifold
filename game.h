/*
 *  game.h
 *  Prototyp
 *
 *  Created by Christian Pehle on 24.08.09.
 *  Copyright 2009 Universität Heidelberg. All rights reserved.
 *
 */

#pragma once

#include <vector>
#include <map>

typedef enum {
	STARTUP,
	GUI,
	LOADING,
	CANCEL_LOADING,
	GAME,
	SHUTDOWN
} GameState;

class Game {

public:
	Game();
	virtual ~Game();

public:
	bool requestStateChange(GameState state);
	bool lockState();
	bool unlockState();
	GameState getCurrentState();

	void setFrameTime(float ms);
	inline float getFrameTime() {return m_frame_time;};

protected:
	GameState m_state;
	bool m_locked;
	float m_frame_time;
};
