#pragma once
#include "Room.h"
#include "Utility.h"
#include "Texts.h"
#include <vector>
#include <iostream>
#include <sstream>

class GameLoop
{
public:
	GameLoop();
	bool isOver;

private:
	enum lightStatus {
		dark = 0,
		light = 1
	};
	enum inputCodes {
		Escape = 27,
		UpArrow = 72,
		DownArrow = 80,
		RightArrow = 77,
		LeftArrow = 75,
	};
	int rWidth;
	int rHeight;
	int flashLightRadius;
	bool hasKey;
	bool firstMove;
	COORD pPos;
	Room room;

	void CheckInput();
	void UpdateChars(const COORD& newPlayerPos, int _direction);
	void UpdateFlashlight(lightStatus _id);
	bool InLightRadius(int _x, int _y);
};

