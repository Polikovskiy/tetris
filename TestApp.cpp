#include "TestApp.h"


TestApp::TestApp() : Parent(30, 20)
{
	mObj1XOld = mObj1X = 7;                                             // ��������� ���������� ������
	mObj1YOld = mObj1Y = 1;

	tetrominoList.push_back(Tetromino(3, 2, L"101110"));                  //  ������ ���������   4x4
	tetrominoList.push_back(Tetromino(4, 1, L"1111"));
	tetrominoList.push_back(Tetromino(2, 2, L"1111"));
	tetrominoList.push_back(Tetromino(1, 1, L"1"));
	tetrominoList.push_back(Tetromino(3, 2, L"011110"));
	tetrominoList.push_back(Tetromino(3, 2, L"101101"));
	tetrominoList.push_back(Tetromino(2, 1, L"11"));

	tetrominoCurent = tetrominoList[rand() % tetrominoList.size()-1];       //������� ������
	tetrominoNext = tetrominoList[rand() % tetrominoList.size()-1];         // ��������� ������

	drawFrame();
}

void TestApp::KeyPressed(int btnCode)
{
	if (btnCode == 32) {                             // ��������
		rotate();
		mObj1Y--;
	}
	else if (btnCode == 80) 						       // ���������
		speedUp();

	else if (btnCode == 75) {
		if (isEmpty(mObj1X-1, mObj1Y, tetrominoCurent)) {
			mObj1X--;			                                    // ������ �����
		}
	}
	else if (btnCode == 77) { 
		if (isEmpty(mObj1X+1, mObj1Y, tetrominoCurent)) {
			mObj1X++;
		}
	}
	if (mObj1X < 1)
		mObj1X = 1;
	else if (mObj1X >= borderFieldX)
		mObj1X = borderFieldX - 1;

	if (mObj1Y < 1)
		mObj1Y = 1;
	else if (mObj1Y >= borderFieldY)
		mObj1Y = borderFieldY - 1;
}

void TestApp::UpdateF(float deltaTime)
{
	int tetromineNextY = Y_SIZE / 3;                                      //���������� ��������� ������
	int tetromineNextX = X_SIZE - X_SIZE / 5;

	drawScoreLine();

	generateNewFigureTime += deltaTime;


	if (generateNewFigureTime >= gameStep) {
		if (isEmpty(mObj1X, mObj1Y, tetrominoCurent)) {                      //��������� �����

			generateNewFigureTime = 0;

			clearTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);           //������� ������� ��������

			drawTetromino(mObj1X, mObj1Y, tetrominoCurent);                   //������ ����� ��������

			drawTetromino(tetromineNextX, tetromineNextY, tetrominoNext);      //������ ������

			mObj1XOld = mObj1X;
			mObj1YOld = mObj1Y;

			mObj1Y++;
		}
		else {
			if (isTop()) {
				GameOver();                                                    // ������ ������� GAME OVER
			}

			clearTetromino(tetromineNextX, tetromineNextY, tetrominoNext);
			clearLines();                                                      // ��������� � ������� ����������� ����� � ����

			mObj1XOld = mObj1X = 7;
			mObj1YOld = mObj1Y = 1;

			tetrominoCurent = tetrominoNext;
			tetrominoNext = tetrominoList[rand() % 7];

			gameStep = 0.5;

		}
	}

	
}

void TestApp::speedUp() {                                                   
	gameStep = 0.1;
}

void TestApp::clearTetromino(int x, int y, Tetromino tetromino) {               //������� ����� ������
	for (int i = 0; i < tetromino.row; i++) {
		for (int j = 0; j < tetromino.col; j++) {
			if (tetromino.tetrominoShape[tetromino.col * i + j] == '1') {
				SetChar(x + j, y + i, L' ');
			}
		}
	}
}

void TestApp::drawTetromino(int x, int y, Tetromino tetromino) {                  //��������� ������ �� �������
	for (int i = 0; i < tetromino.row; i++) {
		for (int j = 0; j < tetromino.col; j++) {
			if (tetromino.tetrominoShape[tetromino.col * i + j] == '1') {
				SetChar(x + j, y + i, L'O');
			}
		}
	}
}

bool TestApp::isEmpty(int newX, int newY, Tetromino tetromino) {               // �������� �� ������������
	clearTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);
	for (int i = 0; i < tetromino.row; i++) {
		for (int j = 0; j < tetromino.col; j++) {
			wchar_t curent = GetChar(newX + j, newY + i);
			if (tetromino.tetrominoShape[tetromino.col * i + j] == '1' ) {
				if ( GetChar(newX + j, newY + i) == 'O'|| GetChar(newX + j, newY + i) == '#') {
					drawTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);
					return false;
				}
			}
		}
	}
	drawTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);
	return true;
}

void TestApp::clearLines() {                                                   // �������� ����������� �����
	for (int i = borderFieldY; i > 0; i--) {
		for (int j = borderFieldX-1; j > 0; j--) {
			if (GetChar(j, i) != 'O') {
				break;
			}
			if (j == 1) {
				score += 100;
				ShiftLine(i);
				i++;
			}
		}
	}
}

void TestApp::ShiftLine(int line) {                                                      // ����� 
	for (int i = line; i > 0; i--) {
		for (int j = 1; j < borderFieldX; j++) {
			if (i == 1) {
				SetChar(j, i, ' ');
			}
			else {
				wchar_t curent = GetChar(j, i - 1);
				SetChar(j, i, curent);
				
			}
			
		}
	}
}

void TestApp::drawScoreLine() {                                                 // ����� score
	string scoreLine = "score: ";
	string scoreString = to_string(score);
	scoreLine += scoreString;
	int count = scoreLine.size();
	for (int i = 0; i < count; i++) {
		wchar_t curent = scoreLine[i];
		SetChar(3 + i, Y_SIZE, curent);
	}	
}

void TestApp::GameOver() {                                                    // ����� Game over
	system("cls");
	std::cout << "Game over!\nYour score: " << score << endl;
	cin.ignore();
	exit(0);
}

bool TestApp::isTop() {                                                  //����������� ����
	if (mObj1Y == 2) {
		return true;
	}
	return false;
}

void TestApp::rotate() {												// �������� ������
	Tetromino tetrominoRotate = tetrominoCurent.rotateTetromino();

	if (isEmpty(mObj1X, mObj1Y, tetrominoRotate)) {
		clearTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);
		tetrominoCurent = tetrominoRotate;
	}
}

void TestApp::drawFrame() {
	for (int i = 0; i < Y_SIZE + 1; i++) {
		for (int j = 0; j < X_SIZE + 1; j++) {
			if (i == 0 || i == borderFieldY || j == 0 || j == borderFieldX) {           //������ ����
				SetChar(j, i, L'#');
			}
			else {
				SetChar(j, i, L' ');
			}
		}
	}

}

