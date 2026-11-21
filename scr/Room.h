#pragma once
#include "Utility.h"
#include "Texts.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>

using namespace std;

class Room
{
public:
	enum gameChars {
		player = '¤',
		key = '¶',
		wall = '#',
		doorClosed = 'X',
		doorOpen = '*',
		empty = ' ',
		defaultC = '1'
	};
	int consoleWidth;
	int consoleHeight;
	COORD playerPos;
	COORD roomPos;
	COORD doorPos;
	int height = 0;
	int width = 0;
	int numberOfKeys = 0;
	bool darkMode = false;
	vector<vector<char>*>* map;

	void PutRoomTogether();
	void OpenDoor();
	void GetRoomSize();
	void Print();
	void PrintTakenKey(int _numKeysTaken);
	void CheckCharColor(char _toCheck); 
	void ResetRoom(int* _KeysTaken);
	void DeleteMap();

private:
	COORD playerStartPos;
	vector<COORD> keyStartPos;

	void SpawnInsideRoom(char _toSpawn, int* _PosX, int* _PosY, vector<char> _dontDrawOn = {});
	void SpawnOnWall(char _toSpawn, char _drawOnlyOn);
	int GetRandomValue(int _min, int _max, bool _maxExclusive = true);
	bool CharIsInArray(char _toCheck, vector<char> _charList);
	bool GetValidInteger(string _input, int* _ToCheck, COORD _minMaxNumber);
	bool GetValidBool(string _input, bool* _ToCheck);
	void GenerateMaze();
	bool isValid(int x, int y);
};

