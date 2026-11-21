#include "GameLoop.h"

GameLoop::GameLoop()
{
	room = Room();
	room.GetRoomSize();

	system("cls");
	utilities::SetFontSize(30, 30);
	utilities::SetCursorVisible(false);

	room.Print();

	CheckInput();
	room.DeleteMap();
}

void GameLoop::CheckInput()
{
	firstMove = true;
	COORD newPlayerPos;
	COORD textPos = room.roomPos;
	int playerKeys = 0;
	pPos = room.playerPos;
	textPos.Y += room.height + 3;

	char input = 0;
	do
	{
		newPlayerPos = pPos;

		input = _getch();

		int dir;
		switch (input)
		{
		case 'w': // Up
		case 'W':
		case UpArrow:
			newPlayerPos.Y--;
			dir = 0;
			break;

		case 'a': // Left
		case 'A':
		case LeftArrow:
			newPlayerPos.X--;
			dir = 1;
			break;

		case 's': // Down
		case 'S':
		case DownArrow:
			newPlayerPos.Y++;
			dir = 2;
			break;

		case 'd': // Right
		case 'D':
		case RightArrow:
			newPlayerPos.X++;
			dir = 3;
			break;
		case 'r': // Reset
		case 'R':
			room.playerPos = pPos;
			room.ResetRoom(&playerKeys);
			CheckInput();
			break;
		case Escape: // Restart
			return;
		default:
			continue;
		}

		if (room.map->at(newPlayerPos.X)->at(newPlayerPos.Y) == room.wall || (room.map->at(newPlayerPos.X)->
			at(newPlayerPos.Y) == room.doorClosed))
		{
			continue;
		}
		if (room.map->at(newPlayerPos.X)->at(newPlayerPos.Y) == room.key)
		{
			playerKeys++;
			room.PrintTakenKey(playerKeys);
			if (playerKeys == room.numberOfKeys) room.OpenDoor();
		}
		else if (room.map->at(newPlayerPos.X)->at(newPlayerPos.Y) == room.doorOpen)
		{
			isOver = true;
		}

		UpdateChars(newPlayerPos, dir);
	} while (isOver == false);

	utilities::SetConsoleColor(LightGray, Black);
}

void GameLoop::UpdateChars(const COORD& _NewPlayerPos, int _direction)
{
	COORD position = pPos;								//pPos = COORD in Room
	utilities::TranslatePos(position, room.roomPos);	//position = COORD in Console

	room.map->at(pPos.X)->at(pPos.Y) = room.empty;

	UpdateFlashlight(dark);

	pPos = _NewPlayerPos;
	COORD newPosition = _NewPlayerPos;					//_NewPlayerPos = COORD in Room
	utilities::TranslatePos(newPosition, room.roomPos);	//newPosition = COORD in Conmsole

	room.map->at(pPos.X)->at(pPos.Y) = room.player;

	UpdateFlashlight(light);
}

bool GameLoop::InLightRadius(int _x, int _y)
{
	return ((_y == pPos.Y - 2 || _y == pPos.Y + 2) && (_x >= pPos.X - 1 && _x <= pPos.X + 1)) || // Upper and bottom line
		((_y >= pPos.Y - 1 && _y <= pPos.Y + 1) && (_x >= pPos.X - 2 && _x <= pPos.X + 2));		 // Middle lines
}

void GameLoop::UpdateFlashlight(lightStatus _id)
{
	COORD pos = room.roomPos;
	for (short y = 0; y < room.height; y++)
	{
		pos.X = room.roomPos.X;
		for (short x = 0; x < room.width; x++)
		{
			if (InLightRadius(x, y))
			{
				char currentChar = room.map->at(x)->at(y);
				switch (_id)
				{
				case light:
					room.CheckCharColor(currentChar);
					utilities::PrintCharAt(pos, currentChar);
					break;

				case dark && !firstMove && room.darkMode:
					if (room.darkMode)
					{
						utilities::SetConsoleColor(Black, Black);
						utilities::PrintCharAt(pos, '&');
					}
					break;

				default:
					break;
				}

				pos.X++;
				continue;
			}

			if (firstMove && room.darkMode)
			{
				utilities::SetConsoleColor(Black, Black);
				utilities::PrintCharAt(pos, '&');
			}

			pos.X++;
		}
		pos.Y++;
	}
	if (firstMove) firstMove = false;
}