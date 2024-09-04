//*************************************************************************//
//                                                                         //
//                                 snake                                   //
//                                                                         //
//*************************************************************************//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

enum sDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
sDirection dir;
const int width = 20;
const int height = 20;
int x, y, _fruitX, _fruitY, score = 0, tailX[100], tailY[100];
bool gameOver;

void setup();
void clearScrean();
void draw();
void randFruit();
void input();
void logic();

int main()
{
	setup();
	while (!gameOver)
	{
		draw();
		input();
		logic();
		Sleep(100);
	}
  return 0;
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'r':
			dir = STOP;
			break;
		default:
			break;
		}
	}
}

void logic()
{
	tailX[0] = x;
	tailY[0] = y;
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	for (int i = 1; i < score; ++i)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case UP:
		--y;
		break;
	case DOWN:
		++y;
		break;
	case RIGHT:
		++x;
		break;
	case LEFT:
		--x;
		break;
	default:
		break;
	}
	if (x == _fruitX && y == _fruitY)
	{
		randFruit();
		++score;
	}
	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
		clearScrean();
		std::cout << "GAME OVER! your score: " << score;
	}
	for (int i = 0; i < score; ++i)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			gameOver = true;
			clearScrean();
			std::cout << "GAME OVER! your score: " << score;
		}
	}
}

void draw()
{
	clearScrean();
	for (int i = 0; i < width; ++i)
	{
		std::cout << '#';
	}
	std::cout << std::endl;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (j == 0 || j == width - 1)
			{
				std::cout << '#';
			}
			else if (j == _fruitX && i == _fruitY)
			{
				std::cout << 'Q';
			}
			else if (j == x && i == y)
			{
				std::cout << 'O';
			}
			else {
				bool print = false;
				for (int k = 0; k < score && !print; ++k)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						std::cout << 'o';
					}
				}
				if(!print)
					std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < width; ++i)
	{
		std::cout << '#';
	}
	std::cout << std::endl << "score: " << score;
}

void setup()
{
	gameOver = false;
	x = width / 2;
	y = height / 2;
	randFruit();
}

void randFruit()
{
	bool flag = false;
	srand(time(0));
	while (!flag)
	{
		_fruitX = 1 + (rand() % (width - 1));
		_fruitY = 1 + (rand() % (height - 1));
		flag = true;
		for (int i = 1; i < score; ++i)
		{
			if (tailX[i] == _fruitX && tailY[i] == _fruitY)
				flag = false;
		}
	}
}

void clearScrean()
{
#ifdef _WIN32
	system("cls");

#else
	system("clear");
	
#endif
}
