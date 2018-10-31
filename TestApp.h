#pragma once
#include "BaseApp.h"
#include <iostream>

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

private:
	int mObj1XOld;
	int mObj1YOld;
	int mObj1X;
	int mObj1Y;

	int mObj2X;
	int mObj2Y;

	wstring tetromino[7];
	wstring tetrominoCurent;
	wstring tetrominoNext;

	int score;
	
	float generateNewFigureTime_ = 1000.0f;
	float fromLastGenerateNewFigureTime_ = 0.0f;

	float moveSpeed_ = 100.0f; //pix in sec

	bool mDirection;

public:
	TestApp();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	void rotate();
	void clearTetromino(int x, int y, wstring tetromino);
	void drawTetromino(int x, int y, wstring tetromino);
	void clearLines();
	void ShiftLine();
	bool isEmpty(int newX, int newY, wstring tetromino);
	void drawScoreLine();
	void GameOver();
	bool isTop();
};

