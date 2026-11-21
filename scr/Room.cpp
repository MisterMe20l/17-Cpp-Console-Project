#include "Room.h"

void Room::GetRoomSize()
{
	string widthString;
	string heightString;
	string numKeysString;
	string optionString;
	int textYPos;
	int textIdYPos = 20;

	vector<int>* consoleSize = utilities::GetConsoleSize();
	consoleWidth = consoleSize->at(0);
	consoleHeight = consoleSize->at(1);

	do
	{
		textYPos = textIdYPos;
		texts::PrintTextByIndex(textYPos, 1);
		utilities::ClearConsoleLine(textYPos);
		widthString = utilities::ReadCenteredInput(textYPos, consoleWidth);
	} while (!GetValidInteger(widthString, (&this->width), { 10, 30 }));

	textIdYPos += 2;
	do
	{
		textYPos = textIdYPos;
		texts::PrintTextByIndex(textYPos, 2);
		utilities::ClearConsoleLine(textYPos);
		heightString = utilities::ReadCenteredInput(textYPos, consoleWidth);
	} while (!GetValidInteger(heightString, (&this->height), { 10, 30 }));

	textIdYPos += 2;
	do
	{
		textYPos = textIdYPos;
		texts::PrintTextByIndex(textYPos, 3);
		utilities::ClearConsoleLine(textYPos);
		numKeysString = utilities::ReadCenteredInput(textYPos, consoleWidth);
	} while (!GetValidInteger(numKeysString, (&this->numberOfKeys), { 1, 5 }));

	textIdYPos += 2;
	do
	{
		textYPos = textIdYPos;
		texts::PrintTextByIndex(textYPos, 4);
		utilities::ClearConsoleLine(textYPos);
		optionString = utilities::ReadCenteredInput(textYPos, consoleWidth);
	} while (!GetValidBool(optionString, (&this->darkMode)));

	if (width % 2 == 0) width++;
	if (height % 2 == 0) height++;

	roomPos.X = ((consoleWidth / 4) - (width / 2));
	roomPos.Y = (consoleHeight / 2) - (height / 2);

	PutRoomTogether();

	if (utilities::GetConsoleSize()) delete utilities::GetConsoleSize();
	if (consoleSize) delete consoleSize;
	consoleSize = nullptr;

}

void Room::PutRoomTogether()
{
	GenerateMaze();

	srand(time(NULL));
	int xSpawn = 0;
	int ySpawn = 0;
	int keysSpawned = 0;
	int id = 0;
	do
	{
		keysSpawned++;
		SpawnInsideRoom(key, &xSpawn, &ySpawn, { wall, key });
		keyStartPos.push_back({ (short)xSpawn, (short)ySpawn });
	} while (keysSpawned < numberOfKeys);

	SpawnInsideRoom(player, &xSpawn, &ySpawn, { key, wall });
	playerPos.X = playerStartPos.X = xSpawn;
	playerPos.Y = playerStartPos.Y = ySpawn;

	SpawnOnWall(doorClosed, wall);
}

void Room::OpenDoor()
{
	map->at(doorPos.X)->at(doorPos.Y) = doorOpen;
	if (!darkMode)
	{
		COORD doorPosition = doorPos;
		utilities::TranslatePos(doorPosition, roomPos);
		CheckCharColor(doorOpen);
		utilities::PrintCharAt(doorPosition, doorOpen);
	}
}

bool Room::isValid(int x, int y)
{
	return x > 0 && x < width - 1 && y > 0 && y < height - 1 && map->at(x)->at(y) == wall;
}

struct Cell
{
	int x, y;
};

void Room::GenerateMaze() //PSM
{
	map = new vector<vector<char>*>();

	for (int x = 0; x < width; x++)
	{
		map->push_back(new vector<char>());

		for (int y = 0; y < height; y++)
		{
			map->at(x)->push_back(wall);
		}
	}

	int dx[] = { 0, 0, -2, 2 };
	int dy[] = { -2, 2, 0, 0 };

	stack<Cell> s;
	s.push({ 1, 1 });
	map->at(1)->at(1) = empty;

	srand(time(0));

	while (!s.empty())
	{
		Cell current = s.top();
		vector<int> dirs = { 0, 1, 2, 3 };
		random_shuffle(dirs.begin(), dirs.end());
		bool moved = false;

		for (int i = 0; i < 4; ++i)
		{
			int nx = current.x + dx[dirs[i]];
			int ny = current.y + dy[dirs[i]];

			if (isValid(nx, ny))
			{
				map->at(nx)->at(ny) = empty;
				map->at(current.x + dx[dirs[i]] / 2)->at(current.y + dy[dirs[i]] / 2) = empty;
				s.push({ nx, ny });
				moved = true;
				break;
			}
		}

		if (!moved)
		{
			s.pop();
		}
	}
}

void Room::Print()
{
	COORD position = roomPos;
	char toPrint;
	for (int y = 0; y < height; y++)
	{
		position.X = roomPos.X;
		for (int x = 0; x < width; x++)
		{
			toPrint = map->at(x)->at(y);
			if (toPrint == empty)
			{
				if (x - 1 == playerPos.X && y == playerPos.Y) toPrint = '›';
				else if (x + 1 == playerPos.X && y == playerPos.Y) toPrint = '‹';
				else if (x == playerPos.X && y - 1 == playerPos.Y) toPrint = 'v';
				else if (x == playerPos.X && y + 1 == playerPos.Y) toPrint = '^';
			}
			CheckCharColor(map->at(x)->at(y));
			utilities::PrintCharAt(position, toPrint);

			position.X++;
		}
		position.Y++;
	}

	COORD pos = roomPos;
	pos.Y += (width / 2);
	pos.X -= 2;
	for (int i = 0; i < numberOfKeys; i++)
	{
		CheckCharColor(wall); //Empty key slot
		utilities::PrintCharAt(pos, key);
		pos.X--;
	}
}

void Room::PrintTakenKey(int _numKeysTaken)
{
	COORD pos = roomPos;
	pos.X -= 1 + _numKeysTaken;
	pos.Y += (width / 2);

	CheckCharColor(key);
	utilities::PrintCharAt(pos, key);
}

void Room::CheckCharColor(char _toCheck)
{
	switch (_toCheck)
	{
	case empty:
		utilities::SetConsoleColor(LightGreen, LightYellow);
		break;
	case wall:
		utilities::SetConsoleColor(Black, Gray);
		break;
	case player:
		utilities::SetConsoleColor(Aqua, LightYellow);
		break;
	case doorClosed:
		utilities::SetConsoleColor(Red, LightRed);
		break;
	case doorOpen:
		utilities::SetConsoleColor(LightGreen, LightGreen);
		break;
	case key:
		utilities::SetConsoleColor(Purple, LightYellow);
		break;
	default:
		utilities::SetConsoleColor(LightGray, Black);
		break;
	}
}

void Room::SpawnInsideRoom(char _toSpawn, int* _PosX, int* _PosY, vector<char> _dontDrawOn)
{
	int randomX;
	int randomY;

	do
	{
		randomX = GetRandomValue(1, width - 2);
		randomY = GetRandomValue(1, height - 2);
	} while (CharIsInArray(map->at(randomX)->at(randomY), _dontDrawOn));

	*_PosX = randomX;
	*_PosY = randomY;
	map->at(randomX)->at(randomY) = _toSpawn;

	_PosX = nullptr;
	_PosY = nullptr;
}

void Room::SpawnOnWall(char toSpawn, char drawOnlyOn)
{
	int rndX;
	int rndY;
	int direction;
	bool toRepeat;

	do
	{
		toRepeat = false;
		rndX = GetRandomValue(1, width - 2);
		rndY = GetRandomValue(1, height - 2);
		direction = rand() % 4;

		switch (direction)
		{
		case 0://Left wall
			rndX = 0;
			if (map->at(rndX + 1)->at(rndY) == wall) toRepeat = true;
			break;

		case 1://Upper wall
			rndY = 0;
			if (map->at(rndX)->at(rndY + 1) == wall) toRepeat = true;
			break;

		case 2://Right wall
			rndX = width - 1;
			if (map->at(rndX - 1)->at(rndY) == wall) toRepeat = true;
			break;

		case 3://Lower wall
			rndY = height - 1;
			if (map->at(rndX)->at(rndY - 1) == wall) toRepeat = true;
			break;

		default:
			break;
		}
	} while (!CharIsInArray(map->at(rndX)->at(rndY), { drawOnlyOn }) || toRepeat);

	doorPos.X = rndX;
	doorPos.Y = rndY;
	map->at(doorPos.X)->at(doorPos.Y) = doorClosed;
}

int Room::GetRandomValue(int _min, int _max, bool _maxExclusive)
{
	if (!_maxExclusive) ++_max;
	return (rand() % (_max)) + _min;
}

bool Room::CharIsInArray(char _toCheck, vector<char> _charList)
{
	for (char character : _charList)
	{
		if (character == _toCheck) return true;
	}
	return false;
}

bool Room::GetValidInteger(string _input, int* _ToCheck, COORD _minMaxNumber)
{
	stringstream ss{ _input };
	ss >> (*_ToCheck);

	// Trim leading/trailing whitespace 
	_input.erase(0, _input.find_first_not_of(" \t"));
	_input.erase(_input.find_last_not_of(" \t") + 1);
	return ((!ss.fail() || ss.eof()) && (*_ToCheck >= _minMaxNumber.X && *_ToCheck <= _minMaxNumber.Y) && !_input.empty());
}

bool Room::GetValidBool(string _input, bool* _ToCheck)
{
	if (_input == "y" || _input == "Y") *_ToCheck = true;
	else if (_input == "n" || _input == "N") *_ToCheck = false;
	else return false;
	return true;
}

void Room::ResetRoom(int* _KeysTaken)
{
	_KeysTaken = 0;
	map->at(playerPos.X)->at(playerPos.Y) = empty;
	playerPos = playerStartPos;
	map->at(playerPos.X)->at(playerPos.Y) = player;
	map->at(doorPos.X)->at(doorPos.Y) = doorClosed;

	for (int i = 0; i < keyStartPos.size(); i++)
	{
		map->at(keyStartPos[i].X)->at(keyStartPos[i].Y) = key;
	}

	Print();
	delete _KeysTaken;
	_KeysTaken = nullptr;
}

void Room::DeleteMap()
{
	if (map) delete map;
	map = nullptr;
}
