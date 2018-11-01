#pragma once
#include "BaseApp.h"
#include <iostream>
#include "Tetromino.cpp"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

private:
	int mObj1XOld;
	int mObj1YOld;
	int mObj1X;
	int mObj1Y;

	int borderFieldX = 15;
	int borderFieldY = Y_SIZE - 1;

	int score = 0;
	
	float generateNewFigureTime = 0;

	float gameStep = 0.5; 

	Tetromino tetrominoCurent;
	Tetromino tetrominoNext;

	vector <Tetromino> tetrominoList;

public:
	TestApp();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	void drawFrame();
	void rotate();
	void clearTetromino(int x, int y, Tetromino tetromino);
	void drawTetromino(int x, int y, Tetromino tetromino);
	void clearLines();
	void ShiftLine(int line);
	void drawScoreLine();
	void GameOver();
	void speedUp();
	bool isEmpty(int newX, int newY, Tetromino tetromino);
	bool isTop();
};

