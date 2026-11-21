#include "Texts.h"


void texts::PrintTextByIndex(int& _PosY, int _index)
{
	PrintStringAt(CenterTextX(textList[_index], _PosY), textList[_index]);
	_PosY++;
}

void texts::PrintBigTextByIndex(int& _PosY, int _index)
{
	for (int i = 0; i < bigTextList[_index].size(); i++)
	{
		PrintStringAt(CenterTextX(bigTextList[_index][i], _PosY), bigTextList[_index][i]);
		_PosY++;
	}
}
