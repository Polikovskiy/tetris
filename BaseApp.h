#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

class BaseApp
{
private:
	HANDLE mConsole;
	HANDLE mConsoleIn;

	CHAR_INFO* mChiBuffer;
	COORD mDwBufferSize;
	COORD mDwBufferCoord;
	SMALL_RECT mLpWriteRegion;

	void Render();

public:

	//ðàçìåðû îáëàñòè âûâîäà ïî ãîðèçîíòàëè è âåðòèêàëè â ñèìâîëàõ
	const int X_SIZE;
	const int Y_SIZE;
	bool start;

	//àðãóìåíòàìè ÿâëÿþòñÿ ðàçìåðû îáëàñòè âûâîäà ïî ãîðèçîíòàëè è âåðòèêàëè â ñèìâîëàõ
	BaseApp(int xSize = 100, int ySize = 80);
	virtual ~BaseApp();

	//çàïóñêàåò èãðîâîé öèêë
	void Run();

	//ìîæíî çàïîëíèòü x,y-ñèìâîë ýêðàíà îïðåäåëåííûì ñèìâîëîì, èëè ñ÷èòàòü åãî
	void SetChar(int x, int y, wchar_t c);
	wchar_t GetChar(int x, int y);

	/*ýòà ôóíêöèÿ âûçûâàåòñÿ êàæäóþ èãðîâóþ èòåðàöèþ, å¸ ìîæíî ïåðåîïðåäåëèòü, â íàñëåäíèêå êëàññà.
	â íå¸ ïðèõîäèò deltaTime - ðàçíèöà âî âðåìåíè ìåæäó ïðåäûäóùåé èòåðàöèåé è ýòîé, â ñåêóíäàõ*/
	virtual void UpdateF(float deltaTime) {}
	/*ýòà ôóíêöèÿ âûçûâàåòñÿ ïðè íàæàòèè êëàâèøè íà êëàâèàòóðå, â íå¸ ïðèõîäèò êîä êëàâèøè - btnCode.
	åñëè èñïîëüçîâàòü ñòðåëêè èëè ôóíêöèîíàëüíûå êëàâèøè, òî ïðèäåò îáùåå äëÿ íèõ ÷èñëî, íàïðèìåð 224, à ñëåäóþùåå çà íèì -
	áóäåò óæå íåïîñðåäñòâåííî êîä ñàìîé êëàâèøè, åãî ìîæíî ïîëó÷èòü, âûçâàâ ìåòîä getch().
	Ìåòîä KeyPressed òàê æå ìîæíî ïåðåîïðåäåëèòü â íàñëåäíèêå*/
	virtual void KeyPressed(int btnCode) {}
};