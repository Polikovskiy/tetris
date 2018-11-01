#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

class Tetromino {
public:
	int row;
	int col;
	wstring tetrominoShape;

	Tetromino(){}

	Tetromino(int row, int col, wstring tetromino) {
		this->row = row;
		this->col = col;
		this->tetrominoShape = tetromino;
	}

	Tetromino rotateTetromino() {
		wstring tetrominoRotate;
		int last = col;
		for (int i = last; i > 0; i--) {
			for (int j = 0; j < row; j++) {				
				tetrominoRotate = tetrominoRotate + tetrominoShape[col * j + i - 1];
			}
		}
		return Tetromino(col, row, tetrominoRotate);
	}

};