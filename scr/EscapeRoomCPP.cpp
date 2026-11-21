#include "Texts.h"
#include "GameLoop.h"
#include "Utility.h"
#include "Room.h"
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std; //Functions with NSM = Not Self-Made; and PSM = Partially Self-Made (Every other were self-made)

int main()
{
	bool firstRun = true;
	system("chcp 1252"); // Western European (Windows) chcp 1252 !!(gantt) -> Zeitdiagramm
	do
	{
		utilities::SetConsoleColor(LightGray, Black);
		utilities::SetCursorVisible(true);
		utilities::SetFontSize(15, 30);
		if (firstRun) utilities::SetToFullScreen();
		firstRun = false;

		system("cls");

		int textYPos = 10;

		texts::PrintBigTextByIndex(textYPos, 0);
		textYPos += 2;
		texts::PrintTextByIndex(textYPos, 0);
		GameLoop game = GameLoop();


		system("cls");
		utilities::SetFontSize(15, 30);
		utilities::SetCursorVisible(true);

		if (game.isOver == true)
		{
			textYPos = 10;
			texts::PrintBigTextByIndex(textYPos, 1);
			textYPos += 2;
			texts::PrintTextByIndex(textYPos, 5);
			texts::PrintTextByIndex(textYPos, 6);

			_getch();
		}
	} while (true);
}