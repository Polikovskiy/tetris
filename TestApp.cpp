#include "TestApp.h"


TestApp::TestApp() : Parent(30, 20)
{
	mDirection = true;
	mObj1XOld = mObj1X = 10;                                   //координаты фигуры
	mObj1YOld = mObj1Y = 2;
	mObj2X = 10;
	mObj2Y = 12;

	tetromino[0].append(L"0   0   0   0   ");                  //  фигуры  4x4
	tetromino[1].append(L"0   00  0       ");
	tetromino[2].append(L"0   0   00      ");
	tetromino[3].append(L" 0   0  00      ");
	tetromino[4].append(L"0               ");
	tetromino[5].append(L"00  00          ");
	tetromino[6].append(L" 0  00  0       ");
	tetromino[7].append(L"0   00   0      ");

	tetrominoCurent = tetromino[rand() % 8];                         // текущая
	tetrominoNext = tetromino[rand() % 8];                           //следующая

	score = 0;

	for (int i = 0; i < Y_SIZE + 1; i++) {
		for (int j = 0; j < X_SIZE + 1; j++) {
			if (i == 0 || i == Y_SIZE - 1 || j == 0 || j == X_SIZE - X_SIZE / 3) {           //рисуем поле
				SetChar(j, i, L'#');
			}
			else {
				SetChar(j, i, L' ');
			}
		}
	}
	

}

void TestApp::KeyPressed(int btnCode)
{
	if (btnCode == 32) { //w
		clearTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);            // вращение
		rotate();
		mObj1Y--;
	} 
	else if (btnCode == 80) //s                                         // ускорение
		mObj1Y+=2;
	else if (btnCode == 75) {
		if (isEmpty(mObj1X-1, mObj1Y-1, tetrominoCurent)) {
			mObj1X--;
			mObj1Y--;
			                                                             // вправо влево
		}
	}
	else if (btnCode == 77) { //d
		if (isEmpty(mObj1X+1, mObj1Y-1, tetrominoCurent)) {
			mObj1X++;
			mObj1Y--;
		}
	}
	if (mObj1X < 1)
		mObj1X = 1;
	else if (mObj1X >= X_SIZE)
		mObj1X = X_SIZE - 1;

	if (mObj1Y < 1)
		mObj1Y = 1;
	else if (mObj1Y >= Y_SIZE)
		mObj1Y = Y_SIZE - 1;
}

void TestApp::UpdateF(float deltaTime)
{
	int tetromineNextY = Y_SIZE / 3;                                      //координаты следующей фигуры
	int tetromineNextX = X_SIZE - X_SIZE / 5;

	drawScoreLine();

	if (isEmpty(mObj1X, mObj1Y, tetrominoCurent)) {            //проверяем место
		

		clearTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);           //убираем прошлую итерацию
		drawTetromino(mObj1X, mObj1Y, tetrominoCurent);                   //рисуем новую итерацию
		drawTetromino(tetromineNextX, tetromineNextY, tetrominoNext);      //рисуем превью
		clearLines();                                                      // проверяем и очищаем заполненные линии и очки

		mObj1XOld = mObj1X;
		mObj1YOld = mObj1Y;

		mObj1Y++;
	}
	else {
		if (isTop()) {
			gameOver = true;
			GameOver();                                               // рисуем надпись GAME OVER
		}


		drawTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);
		clearTetromino(tetromineNextX, tetromineNextY, tetrominoNext);
		clearLines();

		mObj1XOld = mObj1X = 10;
		mObj1YOld = mObj1Y = 1;

		tetrominoCurent = tetrominoNext;
		tetrominoNext = tetromino[rand() % 8];

	}
}

void TestApp::rotate() {                                                     // вращение фигуры
	wstring tetrominoRotate;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			int last = 3;
			tetrominoRotate = tetrominoRotate + tetrominoCurent[4*j-i];
		}
	}
	tetrominoCurent = tetrominoRotate;
}

void TestApp::clearTetromino(int x, int y, wstring tetromino) {               //очистка места фигуры
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetromino[4 * i + j] == '0') {
				SetChar(x + j, y + i, L' ');
			}
		}
	}
}

void TestApp::drawTetromino(int x, int y, wstring tetromino) {                  //заполнение по шаблону
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetromino[4 * i + j] == '0') {
				SetChar(x + j, y + i, L'O');
			}
		}
	}
}

bool TestApp::isEmpty(int newX, int newY, wstring tetromino) {               // проверка на столкновение
	clearTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			wchar_t curent = GetChar(newX + j, newY + i);
			if (tetromino[4 * i + j] == '0' ) {
				if ( GetChar(newX + j, newY + i) == 'O'|| GetChar(newX + j, newY + i) == '#') {
					return false;
				}
			}
		}
	}
	drawTetromino(mObj1XOld, mObj1YOld, tetrominoCurent);
	return true;
}

void TestApp::clearLines() {                                                                      // проверка заполненных линий
	CHAR_INFO* mChiBufferNew = (CHAR_INFO*)malloc((X_SIZE + 1)*(Y_SIZE + 1) * sizeof(CHAR_INFO));
	for (int i = Y_SIZE; i > 0; i--) {
		for (int j = X_SIZE - X_SIZE / 3-1; j > 0; j--) {
			if (GetChar(j, i) != 'O') {
				break;
			}
			if (j == 1) {
				score += 100;
				ShiftLine();
			}
		}
	}
}

void TestApp::ShiftLine() {                                                      // сдвиг 
	for (int i = Y_SIZE - 2; i > 0; i--) {
		for (int j = 1; j < X_SIZE - X_SIZE / 3; j++) {
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
void TestApp::drawScoreLine() {                                                 // вывод score
	string scoreLine = "score: ";
	string scoreString = to_string(score);
	scoreLine += scoreString;
	int count = scoreLine.size();
	for (int i = 0; i < count; i++) {
		wchar_t curent = scoreLine[i];
		SetChar(3 + i, Y_SIZE, curent);
	}	
}

void TestApp::GameOver() {                                                    // вывод Game over
	string GameOverString = " G A M E   O V E R ! ! ! ";
	int count = GameOverString.size();
	for (int i = 0; i < count; i++) {
		wchar_t curent = GameOverString[i];
		SetChar(5 + i, Y_SIZE/2, curent);

	}
}
bool TestApp::isTop() {
	if (mObj1Y == 1) {
		return true;
	}
	return false;
}

