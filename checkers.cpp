#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <Windows.h>
#include "MMSystem.h"
#include <mciapi.h>

using namespace std;

class checkerGame
{
public:
	void playGame(void);

private:
	bool gameOverFlag;
	char gameTable[8][8];
	string winner;
	ofstream outFile;
	string player1Name;
	string player2Name;

	int win = 0;
	int player1Jump = 0;
	int player2Jump = 0;
	int player1KingJump = 0;
	int player2KingJump = 0;

	//piece variables
	int rowPiece = 0, colPiece = 0;
	int row2Piece = 0, col2Piece = 0;

	//move variables
	int row1 = 0;
	int col1 = 0;
	int row2 = 0;
	int col2 = 0;

	//jump variables
	int rowJump = 0;
	int colJump = 0;
	int row2Jump = 0;
	int col2Jump = 0;
	int jumped = 0;
	int jumpedTwo = 0;
	int start = 0;

	int played = 0;

	//file variables
	int beforeRow = 0;
	int beforeCol = 0;
	int beforeRow2 = 0;
	int beforeCol2 = 0;
	int fileRow1= 0;
	int fileCol1 = 0;
	int fileRow2 = 0;
	int fileCol2 = 0;

	//check for kings
	bool isPlayer1King = false;
	bool isPlayer2King = false;

	void initialization(void);
	void process(void);
	void eoj(void);

	void player1Piece(void);
	void player2Piece(void);
	void player1Move(void);
	void player2Move(void);

	void checkForJumpPlayer1();
	void jumpForPlayer1();
	void checkForJumpPlayer2();
	void jumpForPlayer2();

	void setPlayer1King(void);
	void setPlayer2King(void);

	void loadBoard(void);
	void displayBoard(void);
	void checkForWinner(void);
	void showWinner(void);

	void systemTime(void);
	void player1File(void);
	void player2File(void);
	void playMusic(void);

	void getName(void);
};

void main(void)
{
	checkerGame checkers;

	checkers.playGame();

	//system("cls");

	system("pause");
	return;
}

void checkerGame::playGame(void)
{
	initialization();
	process();
	eoj();
}

void checkerGame::initialization(void)
{
	loadBoard();
	displayBoard();
}


void checkerGame::loadBoard(void)
{
	int row = 0;
	int col = 0;

	while (row < 8)
	{
		while (col < 8)
		{
			gameTable[row][col] = ' ';

			if (col % 2 != 0 && row == 0 || col % 2 == 0 && row == 1 || col % 2 != 0 && row == 2)
			{
				gameTable[row][col] = '2';
			}
			else if (col % 2 == 0 && row == 7 || col % 2 != 0 && row == 6 || col % 2 == 0 && row == 5)
			{
				gameTable[row][col] = '1';
			}

			col = col + 1;
		}
		col = 0;
		row = row + 1;
	}
	//gameTable[3][2] = '2';

}

void checkerGame::displayBoard(void)
{
	int row = 0;
	int col = 0;

	while (row < 8)
	{
		if (col < 8)
		{
			cout << row + 1 << "|";
		}
		else
		{
			cout << "|" << row << endl;
		}
		while (col < 8)
		{
			cout << gameTable[row][col];
			col = col + 1;

			if (col < 8)
			{
				cout << "|";
			}
			else
			{
				cout << "|" << endl;
			}
		}
		col = 0;
		//row = row + 1
		row++;
		if (row < 8)
		{
			cout << " |---------------|" << endl;
		}
		else
		{
			cout << " |---------------|" << endl;
			cout << "  1 2 3 4 5 6 7 8 " << endl;
		}


	}


}

void checkerGame::process(void)
{
	playMusic();
	getName();
	while (win == 0)
	{
		checkForJumpPlayer1();
		checkForWinner();
		if (win == 1 || win == 2)
		{
			system("cls");
			displayBoard();
			break;
		}
		checkForJumpPlayer2();
		checkForWinner();
		if (win == 1 || win == 2)
		{
			system("cls");
			displayBoard();
			break;
		}
		player1Piece();
		if (win == 1 || win == 2)
		{
			system("cls");
			displayBoard();
			break;
		}
		player1Move();
		if (win == 1 || win == 2)
		{
			system("cls");
			displayBoard();
			break;
		}
		checkForWinner();
		if (win == 1 || win == 2)
		{
			system("cls");
			displayBoard();
			break;
		}
		player2Piece();
		if (win == 1 || win == 2)
		{
			system("cls");
			displayBoard();
			break;
		}
		player2Move();
		if (win == 1 || win == 2)
		{
			system("cls");
			displayBoard();
			break;
		}
		checkForWinner();
		if (win == 1 || win == 2)
		{
			system("cls");
			displayBoard();
			break;
		}
	}
}
void checkerGame::eoj(void)
{
	playMusic();
	showWinner();
}

//obtain the names of the players
void checkerGame::getName(void) {

	cout << "Enter player 1 name: " << endl;
	cin >> player1Name;

	cout << "Enter player 2 name: " << endl;
	cin >> player2Name;

	system("cls");
	displayBoard();
}


void checkerGame::player1Piece(void)
{
	system("cls");

	displayBoard();

	cout << "-------------" << endl;
	cout << "PLAYER 1 TURN" << endl;
	cout << "-------------" << endl;

	checkForJumpPlayer1();

	if (player1Jump == 0) {

		jumped = 0;

		cout << "Enter the row of the piece you want to move: " << endl;
		cin >> rowPiece;


		cout << "Enter the column of the piece you want to move: " << endl;
		cin >> colPiece;


		//input validation

		while ((gameTable[rowPiece - 1][colPiece - 1] != '1' && gameTable[rowPiece - 1][colPiece - 1] != '!')
			|| (gameTable[rowPiece][colPiece] == '1' //parameters for pieces with nowhere to go
				&& gameTable[rowPiece][colPiece - 2] == '1'
				&& gameTable[rowPiece - 2][colPiece - 2] == '1'
				&& gameTable[rowPiece - 2][colPiece] == '1')
			)
		{

			cout << "THIS IS AN INVALID LOCATION!" << endl;
			cout << endl;
			cout << "TRY AGAIN!" << endl;
			cout << endl;

			cout << "Enter the row of the piece you want to move: " << endl;
			cin >> rowPiece;


			cout << "Enter the column of the piece you want to move: " << endl;
			cin >> colPiece;

		}

		//gameTable[rowPiece - 1][colPiece - 1] = ' ';



	}
	else if (player1Jump == 1)
	{
		//makes the player jump
		jumpForPlayer1();
		checkForWinner();
		player1File();
		checkForJumpPlayer1();

		//allows for multiple jumps
		while (player1Jump == 1)
		{
			jumpForPlayer1();
			player1File();
			checkForJumpPlayer1();
		}


		jumped = 1;
		player1Jump = 0;
	}
}


//movement for player 1
void checkerGame::player1Move(void)
{


	if (jumped == 0) {

		cout << "Enter the row you want to move to: " << endl;
		cin >> row1;

		cout << "Enter the column you want to move to: " << endl;
		cin >> col1;

		if (gameTable[rowPiece - 1][colPiece - 1] == '1')
		{

			//input validation may need tweaking
			while (rowPiece <= row1 || colPiece == col1
				|| rowPiece - row1 != 1 || colPiece - col1 != 1 && colPiece - col1 != -1
				|| gameTable[row1 - 1][col1 - 1] == '1'
				|| row1> 8 || col1 > 8 || row1 < 0 || col1  < 0)// 6 3 5 2 // 3 6 4 5 //6 5 5 4 //3 4 4 5 //2  //6 7 5 6 //2 // 3847//2536//7463//1625//3827//3241//2716//1827
			{

				cout << "THIS IS AN INVALID LOCATION!" << endl;
				cout << endl;
				cout << "TRY AGAIN!" << endl;
				cout << endl;

				cout << "Enter the row you want to move to: " << endl;
				cin >> row1;

				cout << "Enter the column you want to move to: " << endl;
				cin >> col1;
			}
		}
		else if (gameTable[rowPiece - 1][colPiece - 1] == '!')
		{
			while (rowPiece == row1 || colPiece == col1
				|| abs(rowPiece - row1) != 1 && abs(colPiece - col1) != 1
				|| gameTable[row1 - 1][col1 - 1] == '1'
				|| gameTable[row1 - 1][col1 - 1] == '!'
				|| row1 > 8 || col1 > 8 || row1 < 0 || col1 < 0)
			{
				cout << "THIS IS AN INVALID LOCATION!" << endl;
				cout << endl;
				cout << "TRY AGAIN!" << endl;
				cout << endl;

				cout << "Enter the row you want to move to: " << endl;
				cin >> row1;

				cout << "Enter the column you want to move to: " << endl;
				cin >> col1;
			}
		}
		if (player1Jump == 0)
		{
			//gameTable[rowPiece - 1][colPiece - 1] = ' ';
			if (gameTable[rowPiece - 1][colPiece - 1] == '1')
			{
				gameTable[rowPiece - 1][colPiece - 1] = ' ';
				gameTable[row1 - 1][col1 - 1] = '1';
				player1File();
			}
			else if (gameTable[rowPiece - 1][colPiece - 1] == '!')
			{
				gameTable[rowPiece - 1][colPiece - 1] = ' ';
				gameTable[row1 - 1][col1 - 1] = '!';
				player1File();
			}
		}

		//system("cls");
		setPlayer1King();
		checkForJumpPlayer1();


		displayBoard();
		checkForWinner();
	}
	if (jumped == 1)
	{
		//system("cls");

		jumped = 0;
		checkForJumpPlayer1();
		displayBoard();
		checkForWinner();

	}
}


//checks for player 1 jump
void checkerGame::checkForJumpPlayer1()
{
	player1Jump = 0;
	//6352//3847//5243//1
	// 6 3 5 2 // 3 6 4 5 //6 5 5 4 //3 4 4 5 //2  //6 7 5 6 //2 // 3847//2536//7463//1625//3827//3241//2716//1827
	for (int row1 = 0; row1 <= 8; row1++)
	{
		for (int col1 = 0; col1 <= 8; col1++)
		{
			if ((gameTable[row1 - 2][col1] == '2' && gameTable[row1 - 3][col1 + 1] != '2'  && gameTable[row1 - 3][col1 + 1] != '1' && gameTable[row1 - 3][col1 + 1] != '@'
				&& gameTable[row1 - 3][col1 + 1] != '!' && gameTable[row1 - 1][col1 - 1] == '1')
				&& (row1 - 3 <= 8 && col1 + 1 <= 8 && row1 - 3 >= 0 && col1 + 1 >= 0)

				|| (gameTable[row1 - 2][col1 - 2] == '2' && gameTable[row1 - 3][col1 - 3] != '2' && gameTable[row1 - 3][col1 - 3] != '1' && gameTable[row1 - 3][col1 - 3] != '@'
					&& gameTable[row1 - 3][col1 - 3] != '!' && gameTable[row1 - 1][col1 - 1] == '1')
				&& (row1 - 3 <= 8 && col1 - 3 <= 8 && row1 - 3 >= 0 && col1 - 3 >= 0))
			{
				player1Jump = 1;
			}
			else if ((
				(gameTable[row1 - 2][col1] == '2' || gameTable[row1 - 2][col1] == '@')
				&& gameTable[row1 - 3][col1 + 1] != '2'  && gameTable[row1 - 3][col1 + 1] != '1' && gameTable[row1 - 3][col1 + 1] != '@'//upper right 
				&& gameTable[row1 - 3][col1 + 1] != '!' && gameTable[row1 - 1][col1 - 1] == '!')
				&& (row1 - 3 <= 8 && col1 + 1 <= 8 && row1 - 3 >= 0 && col1 + 1 >= 0)

				|| (
				(gameTable[row1 - 2][col1 - 2] == '2' || gameTable[row1 - 2][col1 - 2] == '@')
					&& gameTable[row1 - 3][col1 - 3] != '2' && gameTable[row1 - 3][col1 - 3] != '1' && gameTable[row1 - 3][col1 - 3] != '@'//upper left
					&& gameTable[row1 - 3][col1 - 3] != '!' && gameTable[row1 - 1][col1 - 1] == '!')
				&& (row1 - 3 <= 8 && col1 - 3 <= 8 && row1 - 3 >= 0 && col1 - 3 >= 0)

				//new parameters
				|| (
				(gameTable[row1][col1] == '2' || gameTable[row1][col1] == '@')
					&& gameTable[row1 + 1][col1 + 1] != '2' && gameTable[row1 + 1][col1 + 1] != '1' && gameTable[row1 + 1][col1 + 1] != '@'//lower right
					&& gameTable[row1 + 1][col1 + 1] != '!' && gameTable[row1 - 1][col1 - 1] == '!')
				&& (row1 + 1 <= 8 && col1 + 1 <= 8 && row1 + 1 >= 0 && col1 + 1 >= 0)
				//new parameters
				|| (
				(gameTable[row1][col1 - 2] == '2' || gameTable[row1][col1 - 2] == '@')
					&& gameTable[row1 + 1][col1 - 3] != '2' && gameTable[row1 + 1][col1 - 3] != '1' && gameTable[row1 + 1][col1 - 3] != '@' //lower left
					&& gameTable[row1 + 1][col1 - 3] != '!' && gameTable[row1 - 1][col1 - 1] == '!')
				&& (row1 + 1 <= 8 && col1 - 3 <= 8 && row1 + 1 >= 0 && col1 - 3 >= 0))
			{
				player1Jump = 1;
			}

		}
	}
}

//jumps for player 1
void checkerGame::jumpForPlayer1()
{
	int unitJump = 0;
	int rowOne = 0;
	int colOne = 0;

	int rowTwo = 0;
	int colTwo = 0;

	int isKing = 0;
	int isKingUp = 0;

	for (int row1 = 0; row1 <= 8; row1++)
	{
		for (int col1 = 0; col1 <= 8; col1++)
		{
			//added an extra parameter so the piece doesn't go out of the board

			if ((gameTable[row1 - 2][col1] == '2' || gameTable[row1 - 2][col1] == '@') //checks if there is a checker piece to jump over
				&& gameTable[row1 - 3][col1 + 1] == ' '//checks if there is a space to jump
				&& (gameTable[row1 - 1][col1 - 1] == '1' || gameTable[row1 - 1][col1 - 1] == '!') // checks if the player's piece is theirs
				&& (row1 - 3 <= 8 && col1 + 1 <= 8 && row1 - 3 >= 0 && col1 + 1 >= 0))//checks if the jump goes over the board
			{
				rowOne = row1;
				colOne = col1;
				if (gameTable[row1 - 1][col1 - 1] == '!')
				{
					isKingUp = isKingUp + 1;
				}
			}
			else if ((gameTable[row1 - 2][col1 - 2] == '2' || gameTable[row1 - 2][col1 - 2] == '@')
				&& gameTable[row1 - 3][col1 - 3] == ' '
				&& (gameTable[row1 - 1][col1 - 1] == '1' || gameTable[row1 - 1][col1 - 1] == '!')
				&& (row1 - 3 <= 8 && col1 - 3 <= 8 && row1 - 3 >= 0 && col1 - 3 >= 0))
			{
				rowTwo = row1;
				colTwo = col1;
				if (gameTable[row1 - 1][col1 - 1] == '!')
				{
					isKingUp = isKingUp + 1;
				}
			}
			//kingme // 6 3 5 2 // 3 6 4 5 //6 5 5 4 //3 4 4 5 //2  //6 7 5 6 //2 // 3847//2536//7463//1625//3827//3241//2716 //1827
			//for the king
			else if ((gameTable[row1][col1] == '2' || gameTable[row1][col1] == '@')
				&& gameTable[row1 + 1][col1 + 1] == ' '
				&& gameTable[row1 - 1][col1 - 1] == '!'
				&& (row1 + 1 <= 8 && col1 + 1 <= 8 && row1 + 1 >= 0 && col1 + 1 >= 0))
			{

				rowOne = row1;
				colOne = col1;
				isKing = isKing + 1;

				if ((gameTable[row1][col1 - 2] == '2' || gameTable[row1][col1 - 2] == '@')
					&& gameTable[row1 + 1][col1 - 3] == ' '
					&& gameTable[row1 - 1][col1 - 1] == '!'
					&& (row1 + 1 <= 8 && col1 - 3 <= 8 && row1 + 1 >= 0 && col1 - 3 >= 0))
				{
					rowTwo = row1;
					colTwo = col1;
					isKing = isKing + 1;
				}
			}
			else if ((gameTable[row1][col1 - 2] == '2' || gameTable[row1][col1 - 2] == '@')
				&& gameTable[row1 + 1][col1 - 3] == ' '
				&& gameTable[row1 - 1][col1 - 1] == '!'
				&& (row1 + 1 <= 8 && col1 - 3 <= 8 && row1 + 1 >= 0 && col1 - 3 >= 0))
			{
				rowTwo = row1;
				colTwo = col1;
				isKing = isKing + 1;

				if ((gameTable[row1][col1] == '2' || gameTable[row1][col1] == '@')
					&& gameTable[row1 + 1][col1 + 1] == ' '
					&& gameTable[row1 - 1][col1 - 1] == '!'
					&& (row1 + 1 <= 8 && col1 + 1 <= 8 && row1 + 1 >= 0 && col1 + 1 >= 0))
				{

					rowOne = row1;
					colOne = col1;
					isKing = isKing + 1;
				}
			}

			//lower jump for king
			else if ((row1 == 8 && col1 == 8) && rowOne > 0 && isKing == 1)//single king jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;

				gameTable[rowOne + 1][colOne + 1] = '!';
				gameTable[rowOne - 1][colOne - 1] = ' ';
				gameTable[rowOne][colOne] = ' ';

				fileRow1 = rowOne + 2;
				fileCol1 = colOne + 2;

				beforeRow = rowOne;
				beforeCol = colOne;
			}
			else if ((row1 == 8 && col1 == 8) && rowTwo > 0 && isKing == 1)//single king jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;
				gameTable[rowTwo + 1][colTwo - 3] = '!';
				gameTable[rowTwo][colTwo - 2] = ' ';
				gameTable[rowTwo - 1][colTwo - 1] = ' ';

				fileRow1 = rowTwo + 2;
				fileCol1 = colTwo - 2;

				beforeRow = rowTwo;
				beforeCol = colTwo;
			}
			else if ((row1 == 8 && col1 == 8) && rowOne > 0 && rowTwo > 0 && isKing == 2)//pick a king jump
			{
				cout << "YOU MUST JUMP!" << endl;
				cout << "Pick a unit to jump over: " << endl;
				cout << "Unit 1: " << rowOne + 1 << "," << colOne - 1 << endl; //1 6
				cout << "Unit 2: " << rowTwo + 1 << "," << colTwo + 1 << endl;
				cin >> unitJump;

				if (unitJump == 1)
				{	//lower left
					cout << "You have jumped!" << endl;
					cout << endl;
					gameTable[rowOne + 1][colOne - 3] = '!';
					gameTable[rowOne][colOne - 2] = ' ';
					gameTable[rowOne - 1][colOne - 1] = ' ';

					fileRow1 = rowOne + 2;
					fileCol1 = colOne - 2;

					beforeRow = rowOne;
					beforeCol = colOne;

				}
				else if (unitJump == 2)
				{	//lower right
					cout << "You have jumped!" << endl;
					cout << endl;

					gameTable[rowTwo + 1][colTwo + 1] = '!';
					gameTable[rowTwo - 1][colTwo - 1] = ' ';
					gameTable[rowTwo][colTwo] = ' ';

					fileRow1 = rowTwo + 2;
					fileCol1 = colTwo + 2;

					beforeRow = rowTwo;
					beforeCol = colTwo;

				}
			}
			//upper jump for king
			else if ((row1 == 8 && col1 == 8) && rowOne > 0 && rowTwo == 0 && isKingUp == 1)//single king jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;							// Input for jumping: needs to be fixed
				gameTable[rowOne - 3][colOne + 1] = '!';    // 6 1 5 2 //3241//5243//
				gameTable[rowOne - 1][colOne - 1] = ' ';    // 3 4 4 3
				gameTable[rowOne - 2][colOne] = ' ';

				fileRow1 = rowOne - 2;
				fileCol1 = colOne + 2;

				beforeRow = rowOne;
				beforeCol = colOne;
			}
			else if ((row1 == 8 && col1 == 8) && rowOne == 0 && rowTwo > 0 && isKingUp == 1)//single king jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;
				gameTable[rowTwo - 3][colTwo - 3] = '!';
				gameTable[rowTwo - 1][colTwo - 1] = ' ';
				gameTable[rowTwo - 2][colTwo - 2] = ' ';

				fileRow1 = rowTwo - 2;
				fileCol1 = colTwo - 2;

				beforeRow = rowTwo;
				beforeCol = colTwo;
			}

			else if ((row1 == 8 && col1 == 8) && rowOne > 0 && rowTwo > 0 && isKingUp == 2)//ask user to choose which piece to jump
			{
				cout << "YOU MUST JUMP!" << endl;
				cout << "Pick a unit to jump with: " << endl;
				cout << "Unit 1: " << rowOne << "," << colOne << endl;
				cout << "Unit 2: " << rowTwo << "," << colTwo << endl;
				cin >> unitJump;


				if (unitJump == 1)
				{
					cout << "You have jumped!" << endl;
					cout << endl;							// Input for jumping: needs to be fixed
					gameTable[rowOne - 3][colOne + 1] = '!';    // 6 1 5 2
					gameTable[rowOne - 1][colOne - 1] = ' ';    // 3 4 4 3
					gameTable[rowOne - 2][colOne] = ' ';

					fileRow1 = rowOne - 2;
					fileCol1 = colOne + 2;

					beforeRow = rowOne;
					beforeCol = colOne;
				}
				else if (unitJump == 2)
				{
					cout << "You have jumped!" << endl;
					cout << endl;
					gameTable[rowTwo - 3][colTwo - 3] = '!';
					gameTable[rowTwo - 1][colTwo - 1] = ' ';
					gameTable[rowTwo - 2][colTwo - 2] = ' ';


					fileRow1 = rowTwo - 2;
					fileCol1 = colTwo - 2;

					beforeRow = rowTwo;
					beforeCol = colTwo;
				}

			}

			//regular jumps
			else if ((row1 == 8 && col1 == 8) && rowOne > 0 && rowTwo == 0)//single jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;							// Input for jumping: needs to be fixed
				gameTable[rowOne - 3][colOne + 1] = '1';    // 6 1 5 2 //3241//5243//
				gameTable[rowOne - 1][colOne - 1] = ' ';    // 3 4 4 3
				gameTable[rowOne - 2][colOne] = ' ';

				fileRow1 = rowOne - 2;
				fileCol1 = colOne + 2 ;

				beforeRow = rowOne;
				beforeCol = colOne;
			}
			else if ((row1 == 8 && col1 == 8) && rowOne == 0 && rowTwo > 0)//single jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;
				gameTable[rowTwo - 3][colTwo - 3] = '1';
				gameTable[rowTwo - 1][colTwo - 1] = ' ';
				gameTable[rowTwo - 2][colTwo - 2] = ' ';

				fileRow1 = rowTwo - 2;
				fileCol1 = colTwo - 2;

				beforeRow = rowTwo;
				beforeCol = colTwo;
			}
			else if ((row1 == 8 && col1 == 8) && rowOne > 0 && rowTwo > 0)//ask user to choose which piece to jump
			{
				cout << "YOU MUST JUMP!" << endl;
				cout << "Pick a unit to jump with: " << endl;
				cout << "Unit 1: " << rowOne << "," << colOne << endl;
				cout << "Unit 2: " << rowTwo << "," << colTwo << endl;
				cin >> unitJump;


				if (unitJump == 1)
				{
					cout << "You have jumped!" << endl;
					cout << endl;							// Input for jumping: needs to be fixed
					gameTable[rowOne - 3][colOne + 1] = '1';    // 6 1 5 2
					gameTable[rowOne - 1][colOne - 1] = ' ';    // 3 4 4 3
					gameTable[rowOne - 2][colOne] = ' ';

					fileRow1 = rowOne - 2;
					fileCol1 = colOne + 2;

					beforeRow = rowOne;
					beforeCol = colOne;

				}
				else if (unitJump == 2)
				{
					cout << "You have jumped!" << endl;
					cout << endl;
					gameTable[rowTwo - 3][colTwo - 3] = '1';
					gameTable[rowTwo - 1][colTwo - 1] = ' ';
					gameTable[rowTwo - 2][colTwo - 2] = ' ';

					fileRow1 = rowTwo - 2;
					fileCol1 = colTwo - 2;

					beforeRow = rowTwo;
					beforeCol = colTwo;
				}

			}

		}

	}

	//old method
	/*
	for (int row1 = 0; row1 < 8; row1++)
	{
	for (int col1 = 0; col1 < 8; col1++)
	{
	if (gameTable[row1 - 2][col1] == '2' && gameTable[row1 - 3][col1 + 1] != '2' && gameTable[row1 - 1][col1 - 1] == '1') // original - 1, -1
	{
	cout << "You have jumped!" << endl;
	cout << endl;							// Input for jumping: needs to be fixed
	gameTable[row1 - 3][col1 + 1] = '1';    // 6 1 5 2
	gameTable[row1 - 1][col1 - 1] = ' ';    // 3 4 4 3
	gameTable[row1 - 2][col1] = ' ';
	}
	else if (gameTable[row1 - 2][col1 - 2] == '2' && gameTable[row1 - 3][col1 - 3] != '2' && gameTable[row1 - 1][col1 - 1] == '1')
	{
	cout << "You have jumped!" << endl;
	cout << endl;
	gameTable[row1 - 3][col1 - 3] = '1';
	gameTable[row1 - 1][col1 - 1] = ' ';
	gameTable[row1 - 2][col1 - 2] = ' ';
	}
	}
	}
	*/


}


//player 2 piece unfinished match with player 1
void checkerGame::player2Piece(void)
{
	//may change
	system("cls");
	displayBoard();

	cout << "-------------" << endl;
	cout << "PLAYER 2 TURN" << endl;
	cout << "-------------" << endl;

	checkForJumpPlayer2(); // 6 3 5 2 // 3 6 4 5 //6 5 5 4 //3 4 4 5 //2  //6 7 5 6 //2  //5645//

	if (player2Jump == 0) {


		jumped = 0;


		cout << "Enter the row of the piece you want to move: " << endl;
		cin >> row2Piece;


		cout << "Enter the column of the piece you want to move: " << endl;
		cin >> col2Piece;

		//input validation
		while ((gameTable[row2Piece - 1][col2Piece - 1] != '2' && gameTable[row2Piece - 1][col2Piece - 1] != '@')
			|| (gameTable[row2Piece][col2Piece] == '2'			//parameters for pieces with nowhere to go
				&& gameTable[row2Piece][col2Piece - 2] == '2'
				&& gameTable[row2Piece - 2][col2Piece - 2] == '2'
				&& gameTable[row2Piece - 2][col2Piece] == '2')
			)
		{
			cout << "THIS IS AN INVALID LOCATION!" << endl;
			cout << endl;
			cout << "TRY AGAIN!" << endl;
			cout << endl;

			cout << "Enter the row of the piece you want to move: " << endl;
			cin >> row2Piece;


			cout << "Enter the column of the piece you want to move: " << endl;
			cin >> col2Piece;

		}

		//gameTable[row2Piece - 1][col2Piece - 1] = ' ';

	}
	else if (player2Jump == 1)
	{
		//makes the player 2 jump
		jumpForPlayer2();
		checkForWinner();
		player2File();
		checkForJumpPlayer2();
		while (player2Jump == 1)
		{
			jumpForPlayer2();
			player2File();
			checkForJumpPlayer2();
		}

		jumpedTwo = 1;
		player2Jump = 0;
	}
}

//movement for player 2 
void checkerGame::player2Move(void)
{

	int rowMove, colMove;
	if (jumpedTwo == 0) { // 6 3 5 2 // 3 6 4 5 //6 5 5 4 //3 4 4 5 //2  //6 7 5 6 //2//2534//

		cout << "Enter the row you want to move to: " << endl;
		cin >> row2;

		cout << "Enter the column you want to move to: " << endl;
		cin >> col2;

		//input validation may need fixing by adding more or less parameters
		if (gameTable[row2Piece - 1][col2Piece - 1] == '2')
		{

			while (row2Piece >= row2 || col2Piece == col2
				|| row2Piece - row2 != -1 || col2Piece - col2 != -1 && col2Piece - col2 != 1
				|| gameTable[row2 - 1][col2 - 1] == '2'
				|| row2 > 8 || col2 > 8 || row2  < 0 || col2 < 0)
			{
				cout << "THIS IS AN INVALID LOCATION!" << endl;
				cout << endl;
				cout << "TRY AGAIN!" << endl;
				cout << endl;

				cout << "Enter the row you want to move to: " << endl;
				cin >> row2;

				cout << "Enter the column you want to move to: " << endl;
				cin >> col2;
			}
		}
		else if (gameTable[row2Piece - 1][col2Piece - 1] == '@')
		{
			while (row2Piece == row2 || col2Piece == col2
				|| abs(row2Piece - row2) != 1 || abs(col2Piece - col2) != 1
				|| gameTable[row2 - 1][col2 - 1] == '2'
				|| row2 > 8 || col2 > 8 || row2  < 0 || col2 < 0)
			{
				cout << "THIS IS AN INVALID LOCATION!" << endl;
				cout << endl;
				cout << "TRY AGAIN!" << endl;
				cout << endl;

				cout << "Enter the row you want to move to: " << endl;
				cin >> row2;

				cout << "Enter the column you want to move to: " << endl;
				cin >> col2;
			}
		}

		if (player2Jump == 0)
		{
			if (gameTable[row2Piece - 1][col2Piece - 1] == '2')
			{
				gameTable[row2Piece - 1][col2Piece - 1] = ' ';
				gameTable[row2 - 1][col2 - 1] = '2';
				player2File();
			}
			else if (gameTable[row2Piece - 1][col2Piece - 1] == '@')
			{
				gameTable[row2Piece - 1][col2Piece - 1] = ' ';
				gameTable[row2 - 1][col2 - 1] = '@';
				player2File();
			}

			//old
			//gameTable[row2Piece - 1][col2Piece - 1] = ' ';
			//gameTable[row2 - 1][col2 - 1] = '2';
		}

		//system("cls");
		//makes player 2 piece a king
		setPlayer2King();

		//checks if the next move will be a jump
		checkForJumpPlayer2();


		displayBoard();
		checkForWinner();
	}
	if (jumpedTwo == 1)
	{
		//system("cls");

		jumpedTwo = 0;
		checkForJumpPlayer2();
		displayBoard();
		checkForWinner();

	}
}

//checks for jump
void checkerGame::checkForJumpPlayer2()
{
	player2Jump = 0;
	// 6 1 5 2 //3241//5243//
	for (int row2 = 0; row2 <= 8; row2++)
	{
		for (int col2 = 0; col2 <= 8; col2++)
		{
			if ((gameTable[row2][col2] == '1' || gameTable[row2][col2] == '!')
				&& gameTable[row2 + 1][col2 + 1] == ' '
				&& gameTable[row2 - 1][col2 - 1] == '2'
				&& (row2 + 1 <= 8 && col2 + 1 <= 8 && row2 + 1 >= 0 && col2 + 1 >= 0)

				|| (gameTable[row2][col2 - 2] == '1' || gameTable[row2][col2 - 2] == '!')
				&& gameTable[row2 + 1][col2 - 3] == ' '
				&& gameTable[row2 - 1][col2 - 1] == '2'
				&& (row2 + 1 <= 8 && col2 - 3 <= 8 && row2 + 1 >= 0 && col2 - 3 >= 0))
			{
				player2Jump = 1;
			}

			else if ((
				(gameTable[row2][col2] == '1' || gameTable[row2][col2] == '!')
				&& gameTable[row2 + 1][col2 + 1] == ' '
				&& gameTable[row2 - 1][col2 - 1] == '@'
				&& (row2 + 1 <= 8 && col2 + 1 <= 8 && row2 + 1 >= 0 && col2 + 1 >= 0)

				|| (gameTable[row2][col2 - 2] == '1' || gameTable[row2][col2 - 2] == '!')
				&& gameTable[row2 + 1][col2 - 3] == ' '
				&& gameTable[row2 - 1][col2 - 1] == '@'
				&& (row2 + 1 <= 8 && col2 - 3 <= 8 && row2 + 1 >= 0 && col2 - 3 >= 0)

				|| (gameTable[row2 - 2][col2] == '1' || gameTable[row2 - 2][col2] == '!')
				&& gameTable[row2 - 3][col2 + 1] == ' '//upper right 
				&& gameTable[row2 - 1][col2 - 1] == '@'
				&& (row2 - 3 <= 8 && col2 + 1 <= 8 && row2 - 3 >= 0 && col2 + 1 >= 0)

				|| (gameTable[row2 - 2][col2 - 2] == '1' || gameTable[row2 - 2][col2 - 2] == '!')
				&& gameTable[row2 - 3][col2 - 3] == ' '//upper left
				&& gameTable[row2 - 1][col2 - 1] == '@'
				&& (row2 - 3 <= 8 && col2 - 3 <= 8 && row2 - 3 >= 0 && col2 - 3 >= 0)))
			{
				player2Jump = 1;
			}
		}
	}
}

//jumps for player 2
void checkerGame::jumpForPlayer2()
{
	int unitJump = 0;
	int rowOne = 0;
	int colOne = 0;

	int rowTwo = 0;
	int colTwo = 0;

	int kingJumpDown = 0;
	int kingJumpUp = 0;



	for (int row2 = 0; row2 <= 8; row2++)
	{
		for (int col2 = 0; col2 <= 8; col2++)
		{
			//added an extra parameter so the piece doesnt go out of the board

			if ((gameTable[row2][col2] == '1' || gameTable[row2][col2] == '!') //checks if there is a checker piece to jump over
				&& gameTable[row2 + 1][col2 + 1] == ' ' //checks if there is an empty space to jump
				&& (gameTable[row2 - 1][col2 - 1] == '2' || gameTable[row2 - 1][col2 - 1] == '@') //checks if the checker piece is the players
				&& (row2 + 1 <= 8 && col2 + 1 <= 8 && row2 + 1 >= 0 && col2 + 1 >= 0)) //prevents from jumping out of the board
			{
				rowOne = row2;
				colOne = col2;
				//lower right king jump
				if (gameTable[row2 - 1][col2 - 1] == '@')
				{
					kingJumpDown = kingJumpDown + 1;
				}
			}
			else if ((gameTable[row2][col2 - 2] == '1' || gameTable[row2][col2 - 2] == '!')
				&& gameTable[row2 + 1][col2 - 3] == ' '
				&& (gameTable[row2 - 1][col2 - 1] == '2' || gameTable[row2 - 1][col2 - 1] == '@')
				&& (row2 + 1 <= 8 && col2 - 3 <= 8 && row2 + 1 >= 0 && col2 - 3 >= 0))
			{
				rowTwo = row2;
				colTwo = col2;
				//lower left king jump
				if (gameTable[row2 - 1][col2 - 1] == '@')
				{
					kingJumpDown = kingJumpDown + 1;
				}
			}
			else if ((gameTable[row2 - 2][col2] == '1' || gameTable[row2 - 2][col2] == '!')
				&& gameTable[row2 - 3][col2 + 1] == ' '//upper right 
				&& gameTable[row2 - 1][col2 - 1] == '@'
				&& (row2 - 3 <= 8 && col2 + 1 <= 8 && row2 - 3 >= 0 && col2 + 1 >= 0))
			{
				rowOne = row2;
				colOne = col2;
				kingJumpUp = kingJumpUp + 1;


				if ((gameTable[row2 - 2][col2 - 2] == '1' || gameTable[row2 - 2][col2 - 2] == '!')
					&& gameTable[row2 - 3][col2 - 3] == ' '//upper left
					&& gameTable[row2 - 1][col2 - 1] == '@'
					&& (row2 - 3 <= 8 && col2 - 3 <= 8 && row2 - 3 >= 0 && col2 - 3 >= 0))\
				{
					rowTwo = row2;
					colTwo = col2;
					kingJumpUp = kingJumpUp + 1;

				}
			}
			else if ((gameTable[row2 - 2][col2 - 2] == '1' || gameTable[row2 - 2][col2 - 2] == '!')
				&& gameTable[row2 - 3][col2 - 3] == ' '//upper left
				&& gameTable[row2 - 1][col2 - 1] == '@'
				&& (row2 - 3 <= 8 && col2 - 3 <= 8 && row2 - 3 >= 0 && col2 - 3 >= 0))\
			{
				rowTwo = row2;
				colTwo = col2;
				kingJumpUp = kingJumpUp + 1;

				if ((gameTable[row2 - 2][col2] == '1' || gameTable[row2 - 2][col2] == '!')
					&& gameTable[row2 - 3][col2 + 1] == ' '//upper right 
					&& gameTable[row2 - 1][col2 - 1] == '@'
					&& (row2 - 3 <= 8 && col2 + 1 <= 8 && row2 - 3 >= 0 && col2 + 1 >= 0))
				{
					rowOne = row2;
					colOne = col2;
					kingJumpUp = kingJumpUp + 1;
				}
			}

			else if ((row2 == 8 && col2 == 8) && rowOne > 0 && rowTwo == 0 && kingJumpUp == 1)//single king jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;							// Input for jumping: needs to be fixed
				gameTable[rowOne - 3][colOne + 1] = '@';    // 6 1 5 2 //3241//5243//
				gameTable[rowOne - 1][colOne - 1] = ' ';    // 3 4 4 3
				gameTable[rowOne - 2][colOne] = ' ';
				 
				fileRow2 = rowOne - 2;
				fileCol2 = colOne + 2;

				beforeRow2 = rowOne;
				beforeCol2 = colOne;
			}
			else if ((row2 == 8 && col2 == 8) && rowOne == 0 && rowTwo > 0 && kingJumpUp == 1)//single king jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;
				gameTable[rowTwo - 3][colTwo - 3] = '@';
				gameTable[rowTwo - 1][colTwo - 1] = ' ';
				gameTable[rowTwo - 2][colTwo - 2] = ' ';


				fileRow2 = rowTwo - 2;
				fileCol2 = colTwo - 2;

				beforeRow2 = rowTwo;
				beforeCol2 = colTwo;
			}

			else if ((row2 == 8 && col2 == 8) && rowOne > 0 && rowTwo > 0 && kingJumpUp == 2)//pick a king jump
			{
				cout << "YOU MUST JUMP!" << endl;
				cout << "Pick a unit to jump over: " << endl;
				cout << "Unit 1: " << rowOne + 1 << "," << colOne - 1 << endl; //1 6
				cout << "Unit 2: " << rowTwo + 1 << "," << colTwo + 1 << endl;
				cin >> unitJump;

				if (unitJump == 1)
				{	//upper left
					cout << "You have jumped!" << endl;
					cout << endl;							// Input for jumping: needs to be fixed
					gameTable[rowOne - 3][colOne + 1] = '@';    // 6 1 5 2 //3241//5243//
					gameTable[rowOne - 1][colOne - 1] = ' ';    // 3 4 4 3
					gameTable[rowOne - 2][colOne] = ' ';

					fileRow2 = rowOne - 2;
					fileCol2 = colOne + 2;

					beforeRow2 = rowOne;
					beforeCol2 = colOne;
				}
				else if (unitJump == 2)
				{	//upper right
					cout << "You have jumped!" << endl;
					cout << endl;
					gameTable[rowTwo - 3][colTwo - 3] = '@';
					gameTable[rowTwo - 1][colTwo - 1] = ' ';
					gameTable[rowTwo - 2][colTwo - 2] = ' ';

					fileRow2 = rowTwo - 2;
					fileCol2 = colTwo - 2;

					beforeRow2 = rowTwo;
					beforeCol2 = colTwo;

				}
			}

			//lower king jump
			else if ((row2 == 8 && col2 == 8) && rowOne > 0 && rowTwo == 0 && kingJumpDown == 1)//single king jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;

				gameTable[rowOne + 1][colOne + 1] = '@';
				gameTable[rowOne - 1][colOne - 1] = ' ';
				gameTable[rowOne][colOne] = ' ';

				fileRow2 = rowOne + 2;
				fileCol2 = colOne + 2;

				beforeRow2 = rowOne;
				beforeCol2 = colOne;
			}

			else if ((row2 == 8 && col2 == 8) && rowOne == 0 && rowTwo > 0 && kingJumpDown == 1)//single king jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;
				gameTable[rowTwo + 1][colTwo - 3] = '@';
				gameTable[rowTwo][colTwo - 2] = ' ';
				gameTable[rowTwo - 1][colTwo - 1] = ' ';

				fileRow2 = rowTwo + 2;
				fileCol2 = colTwo - 2;

				beforeRow2 = rowTwo;
				beforeCol2 = colTwo;
			}

			else if ((row2 == 8 && col2 == 8) && rowOne > 0 && rowTwo > 0 && kingJumpDown == 2)//ask user to choose which piece to jump
			{
				cout << "YOU MUST JUMP!" << endl;
				cout << "Pick a unit to jump with: " << endl;
				cout << "Unit 1: " << rowOne << "," << colOne << endl;
				cout << "Unit 2: " << rowTwo << "," << colTwo << endl;
				cin >> unitJump;


				if (unitJump == 1)
				{
					cout << "You have jumped!" << endl;
					cout << endl;

					gameTable[rowOne + 1][colOne + 1] = '@';
					gameTable[rowOne - 1][colOne - 1] = ' ';
					gameTable[rowOne][colOne] = ' ';

					fileRow2 = rowOne + 2;
					fileCol2 = colOne + 2;

					beforeRow2 = rowOne;
					beforeCol2 = colOne;
				}
				else if (unitJump == 2)
				{
					cout << "You have jumped!" << endl;
					cout << endl;
					gameTable[rowTwo + 1][colTwo - 3] = '@';
					gameTable[rowTwo][colTwo - 2] = ' ';
					gameTable[rowTwo - 1][colTwo - 1] = ' ';

					fileRow2 = rowTwo + 2;
					fileCol2 = colTwo - 2;

					beforeRow2 = rowTwo;
					beforeCol2 = colTwo;
				}

			}

			//regular jumps
			else if ((row2 == 8 && col2 == 8) && rowOne > 0 && rowTwo == 0)//single jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;

				gameTable[rowOne + 1][colOne + 1] = '2';
				gameTable[rowOne - 1][colOne - 1] = ' ';
				gameTable[rowOne][colOne] = ' ';

				fileRow2 = rowOne + 2;
				fileCol2 = colOne + 2;

				beforeRow2 = rowOne;
				beforeCol2 = colOne;
			}
			else if ((row2 == 8 && col2 == 8) && rowOne == 0 && rowTwo > 0)//single jump
			{
				cout << "You have jumped!" << endl;
				cout << endl;
				gameTable[rowTwo + 1][colTwo - 3] = '2';
				gameTable[rowTwo][colTwo - 2] = ' ';
				gameTable[rowTwo - 1][colTwo - 1] = ' ';

				fileRow2 = rowTwo + 2;
				fileCol2 = colTwo - 2;

				beforeRow2 = rowTwo;
				beforeCol2 = colTwo;
			}
			else if ((row2 == 8 && col2 == 8) && rowOne > 0 && rowTwo > 0)//ask user to choose which piece to jump
			{
				cout << "YOU MUST JUMP!" << endl;
				cout << "Pick a unit to jump with: " << endl;
				cout << "Unit 1: " << rowOne << "," << colOne << endl;
				cout << "Unit 2: " << rowTwo << "," << colTwo << endl;
				cin >> unitJump;


				if (unitJump == 1)
				{
					cout << "You have jumped!" << endl;
					cout << endl;

					gameTable[rowOne + 1][colOne + 1] = '2';
					gameTable[rowOne - 1][colOne - 1] = ' ';
					gameTable[rowOne][colOne] = ' ';

					fileRow2 = rowOne + 2;
					fileCol2 = colOne + 2;

					beforeRow2 = rowOne;
					beforeCol2 = colOne;
				}
				else if (unitJump == 2)
				{
					cout << "You have jumped!" << endl;
					cout << endl;
					gameTable[rowTwo + 1][colTwo - 3] = '2';
					gameTable[rowTwo][colTwo - 2] = ' ';
					gameTable[rowTwo - 1][colTwo - 1] = ' ';

					fileRow2 = rowTwo + 2;
					fileCol2 = colTwo - 2;

					beforeRow2 = rowTwo;
					beforeCol2 = colTwo;
				}

			}

		}
	}
	

}


//! is player 1 king
void checkerGame::setPlayer1King(void)
{
	bool isKing = false;

	for (int col = 0; col <= 8; col++)
	{
		if (gameTable[0][col] == '1')
		{
			isKing = true;
			gameTable[0][col] = '!';
		}


	}

}
//@ is player 2 king
void checkerGame::setPlayer2King(void)
{
	bool isKing = false;


	for (int col = 0; col <= 8; col++)
	{
		if (gameTable[7][col] == '2')
		{
			isKing = true;
			gameTable[7][col] = '@';
		}

	}
}



void checkerGame::checkForWinner(void)
{
	int player1Count = 0;
	int player2Count = 0;

	for (int row = 0; row <= 8; row++)
	{
		for (int col = 0; col <= 8; col++)
		{
			if (gameTable[row][col] == '1' || gameTable[row][col] == '!')
			{
				player1Count = player1Count + 1;
			}
			else if (gameTable[row][col] == '2' || gameTable[row][col] == '@')
			{
				player2Count = player2Count + 1;
			}
		}
	}

	if (player1Count > 0 && player2Count == 0)
	{
		win = 1;
	}
	else if (player1Count == 0 && player2Count > 0)
	{
		win = 2;
	}
}

void checkerGame::showWinner(void)
{
	if (win == 1)
	{
		cout << "-----------------------" << endl;
		cout << "THE WINNER IS PLAYER 1!" << endl;
		cout << "-----------------------" << endl;
	}
	else if (win == 2)
	{
		cout << "-----------------------" << endl;
		cout << "THE WINNER IS PLAYER 2!" << endl;
		cout << "-----------------------" << endl;
	}
}




void checkerGame::systemTime(void)
{
	//outFile.open("data.txt", ios_base::app | std::ios_base::out);

	//long now = time(0);
	//long years = (time(0) / 60 / 60 / 24 / 365) + 1970;
	//long months = ((time(0) / 60 / 60 / 24) % 12);
	//long days = (time(0) / 60 / 60 / 24);

	long hours = ((time(0) / 60 / 60) % 24) - 5;//converted to EST
	long minutes = (time(0) / 60) % 60;
	long seconds = (time(0)) % 60;

	//find the current date
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	if (hours < 0)
	{
		hours = hours + 24;
	}

	outFile << str_t.wMonth << "/" << str_t.wDay << "/" << str_t.wYear << " ";

	outFile << hours << ":" << minutes << ":" << seconds;

	//outFile.close();

}

void checkerGame::player1File(void)
{
	outFile.open("data.txt", ios_base::app | std::ios_base::out);
	outFile << "Player 1 Move: ";
	systemTime();

	outFile << " Name: " << player1Name ;
	
	//may change
	if (player1Jump == 0)
	{

		outFile << " Piece: " << rowPiece << "," << colPiece;
		outFile << " moved to " << row1 << "," << col1;
	}
	else if (player1Jump == 1)
	{

		outFile << " Piece: " << beforeRow << "," << beforeCol;
		outFile << " jumped to "  << fileRow1 << "," << fileCol1;
	}

	if (win == 1)
	{
		outFile << " THE WINNER IS PLAYER 1: " << player1Name << endl;
		outFile << "PLAYER 2 LOST ALL THEIR PIECES! " << endl;
	}
	else if (win == 2)
	{
		outFile << " THE WINNER IS PLAYER 2: " << player2Name << endl;
		outFile << "PLAYER 1 LOST ALL THEIR PIECES! " << endl;
	}
	else
	{
		outFile << " NO WINNER " << endl;
	}
	outFile.close();
}

void checkerGame::player2File(void)
{
	outFile.open("data.txt", ios_base::app | std::ios_base::out);
	outFile << "Player 2 Move: ";
	systemTime();

	outFile << " Name: " << player2Name;

	//may change
	if (player2Jump == 0)
	{

		outFile << " Piece: " << row2Piece << "," << col2Piece;
		outFile << " moved to " << row2 << "," << col2;
	}
	else if (player2Jump == 1)
	{
		outFile << " Piece: " << beforeRow2 << "," << beforeCol2;
		outFile << " jumped to " << fileRow2 << "," << fileCol2;
	}


	if (win == 1)
	{
		outFile << " THE WINNER IS PLAYER 1: " << player1Name<< endl;
		outFile << "PLAYER 2 LOST ALL THEIR PIECES! " << endl;
	}
	else if (win == 2)
	{
		outFile << " THE WINNER IS PLAYER 2: " << player2Name<<endl;
		outFile << "PLAYER 1 LOST ALL THEIR PIECES! " << endl;
	}
	else
	{
		outFile << " NO WINNER " << endl;
	}
	outFile.close();
}

/*
Setting Dependancies in Visual C++
1) Go to Solution Explorer
2) Right click on the Project Name
3) Go to the bottom and choose Properties
4) Expand Linker
5) Choose Input
6) Go to Additional Dependencies
7) Click pull down and pick <edit>
8) In the edit box put "winmm.lib"
9) Choose close
10) Choose close
11) Now add code below
*/

void checkerGame::playMusic(void)
{
	bool stop = false;
	char song1[60];
	char song2[60];

	strcpy_s(song1, "ding.wav");
	strcpy_s(song2, "bing.wav");

	if (win == 0 && played == 0)
	{
		played++;
		PlaySound(TEXT(song1), NULL, SND_SYNC);

	}
	else if (win >= 1)
	{
		stop = true;
		PlaySound(TEXT(song2), NULL, SND_SYNC);
		mciSendString("open \"music.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
		mciSendString("stop mp3", NULL, 0, NULL);
	}

	if (stop == false)
	{
	mciSendString("open \"music.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString("play mp3 repeat", NULL, 0, NULL);
	}
	
}
