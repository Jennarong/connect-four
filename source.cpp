#include <iostream>
#include <stdlib.h>
#include <time.h> 
using namespace std;

void init(int grid[6][7])
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			grid[i][j] = 0;
		}
	}
}
void display(int grid[6][7])
{
	cout << "---+---+---+---+---+---+---" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << " ";
		for (int j = 0; j < 7; j++)
		{
			if (grid[i][j] == 0)
			{
				cout << " ";
			}
			if (grid[i][j] == 1)
			{
				cout << "X";
			}
			if (grid[i][j] == 2)
			{
				cout << "O";
			}
			if (j < 7)
			{
				cout << " | ";
			}
		}
		cout << endl;
		if (i<6)
		{
			cout << "---+---+---+---+---+---+---" << endl;
		}
	}

}
void update(int grid[6][7],int pick, int player)
{
	int x = pick;

	if (x < 7 && x > -1)
	{
		if (grid[6][x] == 0)
		{
			grid[6][x] = player;
		}
		else if (grid[5][x] == 0)
		{
			grid[5][x] = player;
		}
		else if (grid[4][x] == 0)
		{
			grid[4][x] = player;
		}
		else if (grid[3][x] == 0)
		{
			grid[3][x] = player;
		}
		else if (grid[2][x] == 0)
		{
			grid[2][x] = player;
		}
		else if (grid[1][x] == 0)
		{
			grid[1][x] = player;
		}
		else if (grid[0][x] == 0)
		{
			grid[0][x] = player;
		}
	}
}
void Ai(int grid[6][7], int player)
{
	srand(time(NULL));
	bool isCheck = false;
	int x;
	int box;

	for (int i = 0; i <7; i++)
	{
		for (box = 0; box < 3; box++)
		{
			if (grid[i][box] == 1 && grid[i - 1][box] == 1 && grid[i - 2][box] == 1 && grid[i][box] == 1 && grid[i][box + 1] == 1 && grid[i - 3][box] == 0 && grid[i][box] != 0)
			{
				x = box;
				while (grid[0][x] != 0)
					x = box + 1;
				cout << "choose -> " << x + 1 << endl;
				update(grid, x, player);
				isCheck = true;
				break;
			}
			//นอน
			if (grid[i][box] == 1 && grid[i][box + 1] == 1 && grid[i][box + 2] == 0 && grid[i][box] != 0)
			{
				x = box + 2;
				while (grid[0][x] != 0)
					x = box + 3;
				cout << "choose -> " << x + 1 << endl;
				update(grid, x, player);
				isCheck = true;
				break;
			}
			//ตั้ง
			if (grid[i][box] == 1 && grid[i - 1][box]  == 1 && grid[i - 2][box] == 1 && grid[i - 3][box] == 0 && grid[i][box] != 0)
			{
				x = box ;
				while (grid[0][x] != 0)
					x = box + 1;
				cout << "choose -> " << x + 1 << endl;
				update(grid, x, player);
				isCheck = true;
				break;
			}
			//เฉียง
			if (grid[i][box] == 1 && grid[i - 1][box + 1] == 1 && grid[i - 2][box + 2] == 1 && grid[i - 3][box + 3] == 0 && grid[i][box] != 0)
			{
				x = box + 3;
				while (grid[0][x] != 0)
					x = box + 4;
				cout << "choose -> " << x + 1 << endl;
				update(grid, x, player);
				isCheck = true;
				break;
			}
		}
	}
	if (isCheck == false)
	{
		x = rand() % 7 + 1;
		while (grid[0][x - 1] != 0)
			x = rand() % 7 + 1;

		cout << "choise -> "<< x << endl;
		update(grid, x - 1, player);
		isCheck = false;
	}

}
void Player(int grid[6][7],int player,int pick)
{
	int x = pick - 1;
	while (grid[0][x] != 0)
	{
		cout << "!!!!!!!  Full !!!!!!!" << endl;
		if (player == 1)
		{
			cout << "Enter your choice again(1 - 7) : " << endl;
			cin >> pick;
		}
		x = pick - 1;
	}
	update(grid,x,player);

}
void turn(int grid[6][7], int player)
{
	bool check;
	int space = 0;
	int pick;
	if (player == 1)
	{
		cout << "Player's turn" <<endl;
		cout << "Enter your choice(1 - 7) : ";
		cin >> pick;
		while (pick > 7 || pick == 0)
		{
			cout << "Not Correct !!" << endl;
			cout << "Enter your choice again !! (1 - 7) : ";
			cin >> pick;
		}
		Player(grid,player,pick);
	}

	else if (player == 2)
	{
		cout << "Intelligent Computer's turn"<<endl;
		Ai(grid, player);
	}
}

int checkWin(int grid[6][7])
{
	int box = 0;
	//แนวนอน
	for (int i = 0; i < 6; i++)
	{
		for (box = 0; box <= 3; box++)
		{
			if ((grid[i][box] == grid[i][box + 1] && grid[i][box + 1] == grid[i][box + 2] && grid[i][box + 2] == grid[i][box + 3]) && (grid[i][box] != 0))
			{
				return 1;
			}
		}
	}
	//แนวตั้ง
	for (int i = 0; i < 7; i++)
	{
		for (box = 0; box <= 2; box++)
		{
			if ((grid[box][i] == grid[box + 1][i] && grid[box + 1][i] == grid[box + 2][i] && grid[box + 2][i] == grid[box + 3][i]) && (grid[box][i] != 0))
			{
				return 1;
			}
		}
	}
	//เฉียงลง
	for (int i = 3; i < 6; i++){
		for (box = 0; box <= 3; box++){
			if ((grid[i][box] == grid[i - 1][box + 1] && grid[i - 1][box + 1] == grid[i - 2][box + 2] && grid[i - 2][box + 2] == grid[i - 3][box + 3]) && (grid[i][box] != 0)){
				return 1;
			}
		}
	}
	//เฉียงขึ้น
	for (int i = 0; i < 3; i++)
	{
		for (box = 0; box <= 4; box++){
			if ((grid[i][box] == grid[i + 1][box + 1] && grid[i + 1][box + 1] == grid[i + 2][box + 2] && grid[i + 2][box + 2] == grid[i + 3][box + 3]) && (grid[i][box] != 0)){
				return 1;
			}
		}
	}

}
void show_win(int grid[6][7] , int player)
{
	if (checkWin(grid) == 1)
	{
		if (player == 2)
		{
			cout << "			!!!!  GAMEOVER  !!!!" << endl;
			cout << "			!!! player's WIN !!! " << endl;
		}
		else
		{
			cout << "			!!!!  GAMEOVER  !!!!" << endl;
			cout << "			!!! Computer WIN !!! " << endl;
		}
	}
}
void main()
{
	int grid[6][7];
	init(grid);
	int player = 1;

	display(grid);

	while (checkWin(grid) != 1)
	{
		turn(grid, player);
		if (player == 1)
		{
			player = 2;
		}
		else
		{
			player = 1;
		}
		
		display(grid);
		cout << endl;

		show_win(grid,player);
		
	}
}
