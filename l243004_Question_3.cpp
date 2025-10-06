#include <iostream>
using namespace std;

class TicTacToe {
	char** board;
	char player1, player2;
	int count;

public:
	TicTacToe()
	{
		board = new char* [3];
		for (int c = 0; c < 3; c++)
			*(board + c) = new char[3];

		for (int c = 0; c < 3; c++)
			for (int d = 0; d < 3; d++)
				*(*(board + c) + d) = '.';

		count = 0;
		player1 = 'X';
		player2 = 'O';
	}

	~TicTacToe() {
		for (int c = 0; c < 3; c++)
			delete[] * (board + c);
		delete[] board;
	}

private:
	void Print()
	{
		for (int c = 0; c < 3; c++)
		{
			for (int d = 0; d < 3; d++)
			{
				cout << *(*(board + c) + d) << " | ";
			}
			cout << endl;
		}
		cout << endl;
	}

	void Turn(char word)
	{
		int r, c;
		do {
			cout << "Enter row and column (0-2): ";
			cin >> r >> c;
		} while (r < 0 || r >= 3 || c < 0 || c >= 3 || *(*(board + r) + c) != '.'); //invalid inputs (out of bound,filled cells)

		*(*(board + r) + c) = word;
		Print();
	}

	char isValid()
	{
		for (int r = 0; r < 3; r++) {                                  //rows check kar rhe hein
			if (*(*(board + r) + 0) != '.' &&
				*(*(board + r) + 0) == *(*(board + r) + 1) &&
				*(*(board + r) + 1) == *(*(board + r) + 2))
				return *(*(board + r) + 0);
		}

		for (int c = 0; c < 3; c++) {                                 //cols check krrhe hein
			if (*(*(board + 0) + c) != '.' &&
				*(*(board + 0) + c) == *(*(board + 1) + c) &&
				*(*(board + 1) + c) == *(*(board + 2) + c))
				return *(*(board + 0) + c);
		}

		if (*(*(board + 0) + 0) != '.' &&
			*(*(board + 0) + 0) == *(*(board + 1) + 1) &&             //right diagonal check
			*(*(board + 1) + 1) == *(*(board + 2) + 2))
			return *(*(board + 0) + 0);


		if (*(*(board + 0) + 2) != '.' &&                             //left diagonal check
			*(*(board + 0) + 2) == *(*(board + 1) + 1) &&
			*(*(board + 1) + 1) == *(*(board + 2) + 0))
			return *(*(board + 0) + 2);

		return '=';
	}

	void Results()
	{
		Print();
		char winner = isValid();
		if (winner == 'X')
			cout << "Player X Wins!" << endl;
		else if (winner == 'O')
			cout << "Player O Wins!" << endl;
		else if (count == 9)
			cout << "It's a Draw!" << endl;
	}

public:
	void Play()
	{
		while (count < 9)
		{
			if (count % 2 == 0)
				Turn(player1);
			else
				Turn(player2);

			count++;
			if (isValid() != '=')
			{
				Results();
				return;
			}
		}
		Results();
	}
};

int main()
{
	TicTacToe Game1;
	Game1.Play();
}