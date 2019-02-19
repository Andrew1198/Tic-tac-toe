#include <iostream>
#include <vector>

using namespace std;
struct Point
{
	int x, y;
	Point(int z, int c) :x(z), y(c)
	{
	}

};
class Field
{
public:
	unsigned char A[3][3];
	unsigned char player_com;
	unsigned char player_hum;


	Field()
	{
		for (int i = 0; i < 9; i++)
			A[i / 3][i % 3] = 249;
	}
	void draw()
	{
		char h = 'A';
		cout << "  1  2  3";
		for (int i = 0; i < 9; i++)
		{
			if (i % 3 == 0)
				cout << endl << endl << h++ << "  ";
			cout << A[i / 3][i % 3] << " ";
		}
	}
	void input(const char&human)
	{
		if (human == 'x' || human == 'X' || human == 'õ')
		{
			player_com = '0';
			player_hum = 'x';
		}
		else
		{
			player_com = 'x';
			player_hum = '0';
		}
	}
	bool first_mov_com()
	{
		for (int j = 0; j < 9; j++)
			if (A[j / 3][j % 3] == 'x' || A[j / 3][j % 3] == '0')
				return 0;
		A[1][1] = player_com;
		return 1;

	}
	bool check_fin()
	{
		int f;
		for (int j = 0; j < 3; j++)
		{
			f = 1;
			for (int i = 0; i < 3; i++)
				if (A[j][0] != A[j][i])
					f = 0;
			if (f == 1 && A[j][0] != 249)
			{
				cout << "Win " << A[j][0];
				return 1;
			}
		}




		for (int j = 0; j < 3; j++)
		{
			f = 1;
			for (int i = 0; i < 3; i++)
				if (A[0][j] != A[i][j])
					f = 0;
			if (f == 1 && A[0][j] != 249)
			{
				cout << "Win " << A[0][j];
				return 1;
			}
		}




		f = 1;
		for (int j = 0; j < 3; j++)
			if (A[j][j] != A[0][0])
				f = 0;
		if (f == 1 && A[0][0] != 249)
		{
			cout << "Win " << A[0][0];
			return 1;
		}

		f = 1;
		for (int j = 0; j < 3; j++)
			if (A[j][2 - j] != A[0][2])
				f = 0;
		if (f == 1 && A[0][2] != 249)
		{
			cout << "Win " << A[0][2];
			return 1;
		}
		return 0;


	}
	bool check_hum_win_or_com()
	{
		int x = -1; int y;
		int count_hum, count_com;
		for (int j = 0; j < 3; j++)
		{
			count_com = 0; count_hum = 0;
			for (int i = 0; i < 3; i++)
			{
				if (A[j][i] == player_hum)
					count_hum++;
				if (A[j][i] == player_com)
					count_com++;
			}
			if (count_com == 2 || count_hum == 2)
			{
				int i = 0;
				while (A[j][i] != 249 && i < 3)
					i++;
				if (i < 3)
					if (A[j][0] || A[j][1] || A[j][2] == player_com)
					{
						A[j][i] = player_com;
						return 1;
					}
					else
					{
						x = j;
						y = i;
					}
			}
		}



		for (int j = 0; j < 3; j++)
		{
			count_com = 0; count_hum = 0;
			for (int i = 0; i < 3; i++)
			{
				if (A[i][j] == player_hum)
					count_hum++;
				if (A[i][j] == player_com)
					count_com++;
			}
			if (count_com == 2 || count_hum == 2)
			{
				int i = 0;
				while (A[i][j] != 249 && i < 3)
					i++;
				if (i < 3)
					if (A[i][0] || A[i][1] || A[i][2] == player_com)
					{
						A[i][j] = player_com;
						return 1;
					}
					else
					{
						x = i;
						y = j;
					}

			}

		}

		count_com = 0; count_hum = 0;
		for (int i = 0; i < 3; i++)
		{
			if (A[i][i] == player_hum)
				count_hum++;
			if (A[i][i] == player_com)
				count_com++;
		}

		if (count_com == 2 || count_hum == 2)
		{
			int i = 0;
			while (A[i][i] != 249 && i < 3)
				i++;
			if (i < 3)
				if (A[0][0] || A[0][1] || A[0][2] == player_com)
				{
					A[i][i] = player_com;
					return 1;
				}
				else
				{
					x = i;
					y = i;
				}
		}


		count_com = 0; count_hum = 0;
		for (int i = 0; i < 3; i++)
		{
			if (A[i][2 - i] == player_hum)
				count_hum++;
			if (A[i][2 - i] == player_com)
				count_com++;
		}
		if (count_com == 2 || count_hum == 2)
		{
			int i = 0;
			while (A[i][2 - i] != 249 && i < 3)
				i++;
			if (i < 3)
			{
				A[i][2 - i] = player_com;
				return 1;
			}
		}
		if (x != -1)
		{
			A[x][y] = player_com;
			return 1;
		}
		return 0;

	}
	void com()
	{
		float best_cost = 0;
		float cost;
		int x; int y;
		vector<Point>Best_price;
		for (int j = 0; j < 9; j++)
			if (A[j / 3][j % 3] == 249)
			{
				A[j / 3][j % 3] = player_com;
				cost = this->try_();
				A[j / 3][j % 3] = 249;
				if (cost > best_cost || best_cost == 0)
					best_cost = cost;



			}

		for (int j = 0; j < 9; j++)
			if (A[j / 3][j % 3] == 249)
			{
				A[j / 3][j % 3] = player_com;
				cost = this->try_();
				A[j / 3][j % 3] = 249;
				if (cost == best_cost)
				{
					Best_price.push_back(Point(j / 3, j % 3));
				}
			}

		unsigned char d = player_com;
		player_com = player_hum;
		player_hum = d;
		best_cost = 0;
		for (auto j : Best_price)
		{
			A[j.x][j.y] = player_hum;
			cost = this->try_();
			A[j.x][j.y] = 249;
			if (cost < best_cost || best_cost == 0)
			{
				x = j.x; y = j.y;
				best_cost = cost;
			}
		}

		d = player_com;
		player_com = player_hum;
		player_hum = d;

		A[x][y] = player_com;




	}
	float try_()
	{
		float cost = 0;

		int com_obj; int empty;
		for (int j = 0; j < 3; j++)
		{
			com_obj = 0; empty = 0;

			for (int i = 0; i < 3; i++)
				if (A[j][i] == player_com)
					com_obj++;
				else
					if (A[j][i] == 249)
						empty++;

			if (com_obj == 2 && empty == 1)
				cost += 1.5;
			else
				if (com_obj == 1 && empty == 2)
					cost++;
		}



		for (int j = 0; j < 3; j++)
		{
			com_obj = 0; empty = 0;

			for (int i = 0; i < 3; i++)
				if (A[i][j] == player_com)
					com_obj++;
				else
					if (A[i][j] == 249)
						empty++;

			if (com_obj == 2 && empty == 1)
				cost += 1.5;
			else
				if (com_obj == 1 && empty == 2)
					cost++;
		}


		com_obj = 0; empty = 0;
		for (int j = 0; j < 3; j++)

			if (A[j][j] == player_com)
				com_obj++;
			else
				if (A[j][j] == 249)
					empty++;

		if (com_obj == 2 && empty == 1)
			cost += 1.5;
		else
			if (com_obj == 1 && empty == 2)
				cost++;


		com_obj = 0; empty = 0;
		for (int j = 0; j < 3; j++)

			if (A[j][2 - j] == player_com)
				com_obj++;
			else
				if (A[j][2 - j] == 249)
					empty++;

		if (com_obj == 2 && empty == 1)
			cost += 1.5;
		else
			if (com_obj == 1 && empty == 2)
				cost++;


		return cost;
	}


};
int main()
{
	Field A;
	char human;
	cout << "Please choose x or 0 \n";
	cin >> human;
	A.input(human);
	char B[2];

	if (A.player_hum == 'x')
	{
		A.draw();
		cin >> B;
		if (B[0] >= 'a'&&B[0] <= 'c' && B[1] >= '1'&&B[1] <= '3')
			A.A[B[0] - 'a'][B[1] - '0' - 1] = A.player_hum;
		else
			A.A[B[1] - 'a'][B[0] - '0' - 1] = A.player_hum;

	}

	while (true)
	{
		system("cls");

		if (!A.first_mov_com())
			if (!A.check_hum_win_or_com())
				A.com();
		A.draw();
		if (A.check_fin())
			break;

		cin >> B;


		if (B[0] >= 'a'&&B[0] <= 'c' && B[1] >= '1'&&B[1] <= '3')
			A.A[B[0] - 'a'][B[1] - '0' - 1] = A.player_hum;
		else
			A.A[B[1] - 'a'][B[0] - '0' - 1] = A.player_hum;

		system("cls");
		A.draw();

		if (A.check_fin())
			break;

	}





	cout << endl;
	system("pause");
	return 0;
}