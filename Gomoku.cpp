#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

#define capacity 50
const int human = 0;
const int computer = 1;
void init(char A[][capacity], char sym[], string names[], int& dim, int& nop, int& wincount, int& turn)
{

	cout << "ENTER DIMENSION FOR BOARD:" << endl;
	cin >> dim;
	cout << "ENTER NUMBER OF PLAYERS" << endl;
	cin >> nop;


	for (int i = 0; i < nop; i++)
	{
		if (i == 0)
		{
			cout << "ENTER PLAYER NAME" << endl;
			cin >> names[i];
			cout << "ENTER PLAYER's SYMBOL" << endl;
			cin >> sym[i];
		}
		else
		{
			cout << "ENTER NEXT PLAYER NAME" << endl;
			cin >> names[i];
			cout << "ENTER PLAYER's SYMBOL" << endl;
			cin >> sym[i];
		}
	}

	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			A[i][j] = '-';
		}
	}



	cout << "ENTER 3 FOR TIC TAC TOE" << endl;
	cout << "ENTER 5 FOR GOMUKO" << endl;
	cin >> wincount;

	while (wincount != 3 && wincount != 5)
	{
		cout << "INVALID" << endl;
		cin >> wincount;
	}


	srand(time(NULL));
	turn = rand() % nop;

}
void computer_init(char A[][capacity], char sym[], string names[], int& dim, int& nop, int& wincount, int& turn)
{

	cout << "ENTER DIMENSION FOR BOARD:" << endl;
	cin >> dim;
	nop = 2;

	cout << "ENTER PLAYER NAME" << endl;
	cin >> names[human];

	cout << "ENTER PLAYER SYMBOL" << endl;
	cin >> sym[human];

	names[computer] = "BOT";
	cout << "CHOOSE COMPUTER SYMBOL" << endl;
	cin >> sym[computer];




	for (int i = 0; i < dim; i++) //rows
	{
		for (int j = 0; j < dim; j++) //cols
		{
			A[i][j] = '-';
		}
	}



	cout << "ENTER 3 FOR TIC TAC TOE" << endl;
	cout << "ENTER 5 FOR GOMUKO" << endl;
	cin >> wincount;

	while (wincount != 3 && wincount != 5)
	{
		cout << "INVALID" << endl;
		cin >> wincount;
	}


	srand(time(NULL));
	turn = rand() % nop;

}
void print_board(char A[][capacity], int dim)
{
	for (int i = 0; i < dim; i++) //rows
	{
		for (int j = 0; j < dim; j++) //cols
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}
void turn_msg(string name)
{
	cout << name << " " "s TURN" << endl;
}
bool is_valid_move(int r, int c, char A[][capacity], int dim)
{

	if (A[r][c] != '-' || r > dim || c > dim)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void store_move(int& r, int& c, char A[][capacity], int dim)
{
	cout << "ENTER ROW (BETWEEN 1 & " "" << dim << ")" << endl;
	cin >> r;

	cout << "ENTER COLUMN (BETWEEN 1 & " "" << dim << ")" << endl;
	cin >> c;


	r = r - 1;
	c = c - 1;

}

void place_move(char A[][capacity], int r, int c, char sym)
{
	A[r][c] = sym;
}
void turn_change(int& turn, int nop)
{
	turn = (turn + 1) % nop;
}
bool win_horizontal(char A[][capacity], char sym, int dim, int wincount, int r, int c)
{
	if (c + wincount >= dim)
	{
		return false;
	}
	int count = 0;
	for (int i = 0; i < wincount; i++)
	{
		if (A[r][c + i] == sym)
		{
			count++;
		}
	}
	return count == wincount;
}
bool win_vertical(char A[][capacity], char sym, int dim, int wincount, int r, int c)
{
	if (r + wincount >= dim)
	{
		return false;
	}
	int count = 0;
	for (int i = 0; i < wincount; i++)
	{
		if (A[r + i][c] == sym)
		{
			count++;
		}
	}
	return count == wincount;
}
bool win_diagonal_l2r(char A[][capacity], char sym, int dim, int wincount, int r, int c)
{
	if (r + wincount - 1 >= dim || c + wincount - 1 >= dim)
	{
		return false;
	}
	int count = 0;
	for (int i = 0; i < wincount; i++)
	{
		if (A[r + i][c + i] == sym)
		{
			count++;
		}
	}
	return count == wincount;
}
bool win_diagonal_r2l(char A[][capacity], char sym, int dim, int wincount, int r, int c)
{
	if (c - wincount + 1 <= 0)
	{
		return false;
	}
	int count = 0;
	for (int i = 0; i < wincount; i++)
	{
		if (A[r + i][c - i] == sym)
		{
			count++;
		}
	}
	return count == wincount;
}
bool is_win_here(char A[][capacity], char sym, int dim, int wincount, int r, int c)
{
	if (win_horizontal(A, sym, dim, wincount, r, c) == true || win_vertical(A, sym, dim, wincount, r, c) == true || win_diagonal_l2r(A, sym, dim, wincount, r, c) == true || win_diagonal_r2l(A, sym, dim, wincount, r, c) == true)
	{
		return true;
	}
	else
		return false;
}
bool is_win(char A[][capacity], char sym, int dim, int wincount)
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if (is_win_here(A, sym, dim, wincount, i, j) == true)
			{
				return true;
			}
		}
	}
	return false;
}

void computer_move(char A[][capacity], int dim, int& r, int& c, char sym[capacity], int wincount)
{
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			r = i;
			c = j;
			if (is_valid_move(r, c, A, dim))
			{
				A[i][j] = sym[computer];
				if (is_win(A, dim, sym[computer], wincount)) {
					A[i][j] = '-';
					return;
				}
				A[i][j] = '-';
			}
		}
	}

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			r = i;
			c = j;
			if (is_valid_move(r, c, A, dim)) {
				A[i][j] = sym[human];
				if (is_win(A, dim, sym[human], wincount)) {
					A[i][j] = '-';
					return;
				}
				A[i][j] = '-';
			}
		}
	}


	do {
		r = rand() % dim;
		c = rand() % dim;
	} while (!is_valid_move(r, c, A, dim));
}





int main()
{
	char A[capacity][capacity]{};
	char sym[capacity]{};
	string names[capacity]{};
	int dim = 0, nop = 0, wincount = 0, turn = 0;
	int r = 0, c = 0;
	bool x = false;
	int winner = -123;

	int choice;
	cout << "CHOOSE GAME MODE" << endl;
	cout << "1 FOR HUMAN v HUMAN" << endl;
	cout << "2 FOR HUMAN v COMPUTER" << endl;

	cin >> choice;
	while (choice != 1 && choice != 2)
	{
		cout << "INVALID INPUT" << endl;
		cin >> choice;
	}
	system("CLS");
	if (choice == 1)
	{
		init(A, sym, names, dim, nop, wincount, turn);
		print_board(A, dim);
		do
		{
			turn_msg(names[turn]);
			do
			{
				store_move(r, c, A, dim);
			} while (!is_valid_move(r, c, A, dim));
			place_move(A, r, c, sym[turn]);
			print_board(A, dim);
			x = is_win(A, sym[turn], dim, wincount);
			if (x == true)
			{
				winner = turn;
			}
			turn_change(turn, nop);
		} while (x == false);
		if (winner == -123)
		{
			cout << "GAME ENDED IN A DRAW" << endl;
		}
		else
		{
			cout << "WINNER IS:  " << names[winner] << endl;
		}
	}
	else if (choice == 2)
	{
		computer_init(A, sym, names, dim, nop, wincount, turn);
		print_board(A, dim);
		do
		{
			turn_msg(names[turn]);
			if (turn == 1)
			{
				computer_move(A, dim, r, c, sym, wincount);
			}
			else
			{
				do
				{
					store_move(r, c, A, dim);
				} while (!is_valid_move(r, c, A, dim));
			}
			place_move(A, r, c, sym[turn]);
			print_board(A, dim);
			x = is_win(A, sym[turn], dim, wincount);
			if (x == true)
			{
				winner = turn;
			}
			if (x == false)
			{
				turn_change(turn, nop);
			}
		} while (x == false);
		if (winner == -123)
		{
			cout << "GAME ENDED IN A DRAW" << endl;
		}
		else
		{
			cout << "WINNER IS:  " << names[winner] << endl;
		}
	}

}
