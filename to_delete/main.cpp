#include <iostream>
#include <string>
#include <time.h>
#include <stdint.h>
#include <windows.h>
#include <conio.h>

using namespace std;

const int WIDTH = 70;
const int HEIGHT = 40;
char world[WIDTH][HEIGHT];
char tempWorld[WIDTH][HEIGHT];

const char populated = 254;//ascii block
const char unpopulated = 250;//ascii dot
const char QUIT_KEY = 27;
const char RESTART_KEY = 114;
const char TICK_INCREASE_KEY = 119;
const char TICK_DECREASE_KEY = 115;

//to move to header file
int tempTickCount = 0;
int generationCount = 0;
bool toContinue = true;
int TICKS_PER_SECOND = 10;
int TIME_BETWEEN_FRAMES = 1000 / TICKS_PER_SECOND;

void temp();
void temp2();

bool toGenerate()
{    
	//return rand() % 2;//generates random number to see if we fill the relevant 2D array position with something
	int upperLimt = 93;

	int temp = rand() % 100;
	if(temp < upperLimt){
		return false;
	}
	else if(temp > upperLimt){
		return true;
	}
}
int generateRandomValue(){
	//return rand() % 25 + 97;//This is for lowercase ASCII a-z
	//return rand() % 25 + 65;//This is for Uppercase ASCII A-Z
	return 0;
}
void cls()
{
	//this 'clears' the screen by reseting the cursor position.
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position;

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void printWorld()
{
	cls();
	cout << endl << endl;
	cout << "Tick rate: " << tempTickCount << " (TICKS_PER_SECOND: " << TICKS_PER_SECOND  << ")" << endl;
	cout << "Generation: " << generationCount << endl;
	cout << endl << "Printing world..." << endl << endl;

	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			cout << tempWorld[x][y];
		}
		cout << endl;
	}
	cout << endl << "Press 'r' to restart" << endl;
	cout << "Press 'esc' to quit" << endl;
	cout << "Press " << "'" << TICK_INCREASE_KEY << "'" << " to increase simulation rate (max: 90)" << endl;
	cout << "Press " << "'" << TICK_DECREASE_KEY << "'" << " to decrease simulation rate (min: 10)" << endl;

}
void generate()
{
	cout << "Generating cells...";

	//first fill the array with unpopulated cells
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			world[x][y] = unpopulated;
			tempWorld[x][y] = unpopulated;
		}
	}

	//for each live single cell, we randomly generate 8 cells around it
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			if(toGenerate()){
				world[x][y] = populated;
				for(int row = -1; row <= 1; row ++){
					for(int col = -1; col <= 1; col ++){

						int currentX = x + col;
						int currentY = y + row;

						if(currentX == x && currentY == y){
						}else if(currentX >= 0 && currentX < WIDTH && currentY >= 0 && currentY < HEIGHT){
							if(toGenerate()){
								world[currentX][currentY] = populated;
							}else{
								world[currentX][currentY] = unpopulated;
							}
						}//else if
					}//nested x loop
				}//nested y loop
			}//if toGenerate center cell
		}//for x
	}//for y

	cout << "done" << endl;

	//now we fill the 2D array with random live cells.
	//for(int y = 0; y < arraySize; y++){
	//	for(int x = 0; x < arraySize; x++){
	//		if(toGenerate()){
	//			world[x][y] = "A";//A for alive
	//		}
	//	}
	//}

	/*world[2][10] = populated;
	world[3][10] = populated;
	world[4][10] = populated;
	world[5][10] = populated;
	world[6][10] = populated;
	world[7][10] = populated;
	world[8][10] = populated;
	world[9][10] = populated;
	world[10][10] = populated;
	world[11][10] = populated;*/

	//world[4][2] = populated;
	//world[5][3] = populated;
	//world[5][4] = populated;
	//world[5][4] = populated;
	//world[4][4] = populated;
	//world[3][4] = populated;

	//world[4+4][2+4] = populated;
	//world[5+4][3+4] = populated;
	//world[5+4][4+4] = populated;
	//world[5+4][4+4] = populated;
	//world[4+4][4+4] = populated;
	//world[3+4][4+4] = populated;

	/*world[2][10] = populated;
	world[3][10] = populated;
	world[4][10] = populated;
	world[5][10] = populated;
	world[6][10] = populated;
	world[7][10] = populated;
	world[8][10] = populated;
	world[9][10] = populated;
	world[10][10] = populated;
	world[11][10] = populated;*/
}
void allRules(int *x, int *y)
{
	//basic box blue algorithm
	uint8_t count = 0;
	for(int row = -1; row <= 1; row++){
		for(int col = -1; col <= 1; col++){

			int currentX = *x + col;
			int currentY = *y + row;

			if(currentX == *x && currentY == *y){
			}else if(currentX >= 0 && currentX < WIDTH && currentY >= 0 && currentY < HEIGHT){
				if(world[currentX][currentY] == populated){
					count++;
				}
			}//else if
		}//x loop
	}//y loop

	if(world[*x][*y] == populated){
		if(count < 2){
			tempWorld[*x][*y] = unpopulated;
		}else if((count == 2) || (count == 3)){
			tempWorld[*x][*y] = populated;
		}else if(count > 3){
			tempWorld[*x][*y] = unpopulated;
		}
	}else if(tempWorld[*x][*y] == unpopulated){
		if(count == 3){
			tempWorld[*x][*y] = populated;
		}
	}
}
void initialiseGameOfLife()
{
	system("cls");
	generationCount = 0;
	generate();
}
void initialiseConsoleWindow()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	r.bottom = 800;
	r.top = r.bottom - 100;

	MoveWindow(console, 339, 125, r.bottom, r.top, TRUE);
}
void clearUp()
{
	//this was/is used to return the console back to the default configuration if changes made in this program are permanent
}
void ruleCheck()
{
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			allRules(&x, &y);
		}
	}

	generationCount++;
	//memcpy(destionation, source)
	memcpy(world, tempWorld, sizeof(world));
}
void gameUpdate()
{
	ruleCheck();
}
void keyPress()
{
	if (kbhit())
	{
		int keypressed = getch();

		switch (keypressed)
		{
		case QUIT_KEY://ascii esc
			toContinue = false;
			break;
		case RESTART_KEY://ascii r
			initialiseGameOfLife();
			break;
		case TICK_INCREASE_KEY://ascii w
			temp2();
			break;
		case TICK_DECREASE_KEY://ascii s
			temp();
			break;
		default:
			break;
		}
	}
}
void temp2()
{
	int temp1 = TICKS_PER_SECOND + 10;

	if(temp1 <= 10){
		TICKS_PER_SECOND = 10;
	}else if(temp1 >= 90){
		TICKS_PER_SECOND = 90;
	}else{
		TICKS_PER_SECOND += 10;
	}
}
void temp()
{
	int temp1 = TICKS_PER_SECOND - 10;

	if(temp1 <= 10){
		TICKS_PER_SECOND = 10;
	}else{
		TICKS_PER_SECOND -= 10;
	}
}
int main()
{

	srand(time(NULL));

	DWORD lastUpdateTime = GetTickCount();
	int lastSecondTime = (lastUpdateTime / 1000);
	int tickCount = 0;

	initialiseConsoleWindow();
	initialiseGameOfLife();

	//while(!keyPress()){
	while(toContinue)
	{
		TIME_BETWEEN_FRAMES = 1000 / TICKS_PER_SECOND;

		while(GetTickCount() - lastUpdateTime > TIME_BETWEEN_FRAMES)
		{
			keyPress();
			gameUpdate();

			lastUpdateTime += TIME_BETWEEN_FRAMES;
			tickCount++;

		}//while getTickCount()

		int thisSecond = (lastUpdateTime / 1000);
		//cout << "thisSecond: " << thisSecond << " lastSecondTime: " << lastSecondTime << endl;
		if (thisSecond > lastSecondTime)
		{
			//cout << "New Second: " << thisSecond << " tickCount: " << tickCount << endl;
			tempTickCount = tickCount;
			tickCount = 0;
			lastSecondTime = thisSecond;
		}
		printWorld();

	}//while gameIsRunning

	system("pause");
	return 0;
}