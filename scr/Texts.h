#pragma once
#include "Utility.h"
#include <windows.h>
#include <vector>
#include <string>

using namespace std;
using namespace utilities;

namespace texts
{
	const vector<vector<string>> bigTextList = { {		//0	
		"'||''''|                                                .   '||                 '||    ||'                          ", //ASCII Generator: "kban"
		" ||   .     ....    ....   ....   ... ...    ....     .||.   || ..     ....      |||  |||   ....   ......     ....  ",
		" || ''|    ||. '  .|   '' '' .||   ||'  || .|...||     ||    ||' ||  .|...||     |'|..'||  '' .||  '  . |'  .|...|| ",
		" ||        . '|.. ||      .|' ||   ||    | ||          ||    ||  ||  ||          | '|' ||  .|' ||   .|'     ||      ",
		".||.....|  |'..|'  '|...' '|..'|'  ||...'   '|...'     '|.' .||. ||.  '|...'    .|. | .||. '|..'|' ||....|   '|...' ",
		"                                   ||                                                                               ",
		"                                  ''''                                                                              "
	}, {												//1
		" ..|'''.|                                 ..|''||                            .|. ", //ASCII Genetaror: "kban"
		".|'     '   ....   .. .. ..     ....     .|'    ||  .... ...   ....  ... ..  ||| ",
		"||    .... '' .||   || || ||  .|...||    ||      ||  '|.  |  .|...||  ||' '' '|' ",
		"'|.    ||  .|' ||   || || ||  ||         '|.     ||   '|.|   ||       ||      |  ",
		" ''|...'|  '|..'|' .|| || ||.  '|...'     ''|...|'     '|     '|...' .||.     .  ",
		"                                                                             '|' "
	} };
	const vector<string> textList = {
		"Welcome Player!",								//0
		"Please enter the room width (10 - 30)",			//1
		"Please enter the room height (10 - 30)",		//2
		"Plese enter the number of keys (1 - 5)",		//3
		"Do you want to play in the dark? (y/n)",		//4
		"You have escaped!",							//5
		"Press any key to start over"					//6
	};

	void PrintTextByIndex(int& _PosY, int _index);
	void PrintBigTextByIndex(int& _PosY, int _index);
};