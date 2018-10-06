#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;



//Global Variable
bool gameOver;
int x, y, fruitX, fruitY, score;

//Map Size
const int width = 16;
const int height = 16;

//Variables For Drawing Snake
int tailX[100], tailY[100]; 
int nTail;

//Enum For Movement
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};

//Snake Direction
eDirection snakeDir; 



void Setup()
{
	gameOver = false; 
	snakeDir = STOP;

	//Snake Spawn Location
	x = width / 2;
	y = height / 2;

	//Fruit Spawn Loaction
	fruitX = rand() % width;  //random number generated between 0 & width-1
	fruitY = rand() % height; //random number generated between 0 & height-1

	//Initialize Score
	score = 0;
}


//Function for drawing the map, snake, and fruit
void Draw() 
{
	//Clear Console
	system("cls"); 

	//Display Top Map Border
	for (int i = 0; i < width + 2; i++)
		cout << "-";
	cout << endl;

	//Print Map
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "-";
			}
			
			if (i == y && j == x)
			{
				cout << "0"; //Print head of snake
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "*"; //Print fruit
			}
			else
			{
				//Tail printing
				bool print = false; //initialize tail print to false
				
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				
				if (!print)
				{
					cout << " ";
				}
			}

			if (j == width - 1)
				cout << "-";
		}
		cout << endl;
	}

	//Display Bottom Map Border
	for (int i = 0; i < width + 1; i++)
		cout << "-";
	cout << endl;

	//Print Score
	cout << "Score:" << score << endl;
}


//Function for user input into movement and exitting
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if(snakeDir != RIGHT)
				snakeDir = LEFT;
			break;

		case 'd':
			if(snakeDir != LEFT)
				snakeDir = RIGHT;
			break;

		case 'w':
			if(snakeDir != DOWN)
				snakeDir = UP;
			break;

		case 's':
			if(snakeDir != UP)
				snakeDir = DOWN;
			break;

		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevTailX = tailX[0];
	int prevTailY = tailY[0];
	int prevTail2X, prevTail2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prevTail2X = tailX[i];
		prevTail2Y = tailY[i];

		tailX[i] = prevTailX;
		tailY[i] = prevTailY;

		prevTailX = prevTail2X;
		prevTailY = prevTail2Y;

	}
	
	switch (snakeDir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	//Exit if snake head exits map
	if (x > width || x < 0 || y > height || y < 0)
	{
		gameOver = true;
	}

	//Gameover if snake hits itself
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}

	//If fruit is eaten...
	if (x == fruitX && y == fruitY)
	{
		score += 10; //add to score

		fruitX = rand() % width; //random generate new fruit 
		fruitY = rand() % height; //randome generate new fruit

		nTail++; //increase snake tail by 1
	}
}



int main()
{
	Setup();
	while (!gameOver)
	{
		Input();
		Logic();
		Draw();
		Sleep(150); //Make snake move slower
	}
	return 0;
}