#include <iostream>
#include <bits/stdc++.h>
using namespace std;


int table[11][11]; // ������� ����
int open[11][11]; // �������� ������
size_t r[] = {-1, -1, -1, 0, 0, 1, 1, 1};
size_t c[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int opened; // ���������� �������� ������

void Random() 
{
    unsigned int seed;                                                                        
    asm("rdtsc" : "=A" (seed));
    srand(seed);        
}

void fill() 
{
	for(int i = 0; i < 11; i++) // ��������� ������� -1
	{
		table[0][i] = -1;
		table[i][0] = -1;
		table[10][i] = -1;
		table[i][10] = -1;
	}
	Random();
	int x, y;
	int num_mines = 0;
	while(num_mines < 10) 
	{
		x = rand() % 9 + 1;
		y = rand() % 9 + 1;
		if(table[x][y] != 9 && open[x][y] != 1) 
		{
			table[x][y] = 9; // 9 ����� ���������� ���� ������ ��� �������� ��� ������� 8
			num_mines++;
			for(int i = 0; i < 8; i++) // ������ ������������� �� 1 ������ ��� ����� ����
				if(table[x + r[i]][y + c[i]] != 9 && table[x + r[i]][y + c[i]] != -1) table[x + r[i]][y + c[i]]++;	
		}
 	}
}

void print() 
{
	cout << "���������� ���� 10 " << endl;
	for(int i = 0; i < 11; i++) 
	{
		for(int j = 0; j < 11; j++) 
		{
			if (i == 0 && j != 10) cout << j << " ";
			else if (j == 0 && i != 10) cout << i << " ";
			else if(open[i][j] == 1 && table[i][j] != -1) cout << table[i][j] << " ";
			else if (open[i][j] == 2) cout << "B" << " ";
			else if(i != 10 && j != 10) cout << "*" << " ";
		}
		cout << endl;
	}
}

void move(int row, int column) 
{
	if(table[row][column] != 0 || open[row][column] == 1)
	{
		if(table[row][column] > 0 && open[row][column] == 0) opened++;
		open[row][column] = 1;
		return;
	}
	open[row][column] = 1;
	opened++;
	for(int i = 0; i < 8; i++) move(row + r[i], column + c[i]);	
}

bool again() 
{
	char ch;
	while(1) 
	{
		cout << "������ ������� ��� [Y/N]: ";
		cin >> ch;
		if(ch == 'Y') 
		{	
			opened = 0;
			for(int i = 0; i < 11; i++) 
				for(int j = 0; j < 11; j++) 
				{
					open[i][j] = 0;
					table[i][j] = 0;
				}
			return true;
		}
		else if(ch == 'N') return false;
		else cout << "������������ ����, ���������� ��� ���\n";
	}
}
void end() 
{
	for(int i = 0; i < 11; i++) 
		for (int j = 0; j < 11; j++) 
		{
			if(table[i][j] == 9) open[i][j] = 2;
			else open [i][j] = 1;
		}
}

void play () 
{
	int row, column;
	bool ok = false;
	while(1) 
	{
		cout << "������� ������ � ������� ����� ������: ";
		cin >> row >> column;
		if(row > 9 || row < 1 || column > 9 || column < 1) 
		{
			cout << "������������ ����\n";
			continue;
		} else
		{
			open[row][column] = 1;
			break;
		}
	}
	fill();
	open[row][column] = 0;
	move(row, column);
	print();
	while(1) 
	{
		if(ok) 
		{
			cout << "������� ������ � ������� ��� ������� ����� ������[-1 ����� �������� �������]: ";
			cin >> row;
			if(row == -1) 
			{
				ok = false;
				continue;
			}
			cin >> column;
			if(row > 9 || row < 1 || column > 9 || column < 1) 
			{
				cout << "������������ ����\n";
				continue;
			} else if (open [row][column] == 1) 
			{
				cout << "������ ��� �������, ���������� ������� ������" << endl;
				continue;	
			} else if(open[row][column] == 2) 
			{
				open[row][column] = 0;
				ok = false;
				print();
				continue;
			}
			open[row][column] = 2;
			ok = false;
			print();
			continue;  
		}
		cout << "������� ������ � ������� ����� ������ [������� -1 ����� �������� ������ ��� ������ �������]: ";
		cin >> row; 
		if(row == -1) 
		{
			ok = true;
			continue;
		} 
		cin >> column;
		if(row > 9 || row < 1 || column > 9 || column < 1) 
		{
			cout << "������������ ����\n";
			continue;
		} else if (open [row][column] == 1) 
		{
			cout << "������ ��� �������, ���������� ������� ������" << endl;
			continue;	
		}   
		if(table[row][column] == 9) 
		{
			cout << "�� ���������(\n";
			end();
			print();
			if(again()) play();
        	else return;
		} else if (opened == 71) 
		{
			cout << "�� ��������)\n";
			end();
			print();
			if(again()) play();
        	else return;
		}
		move(row, column);
		print();
	}	
}

int main() {
	setlocale(LC_ALL, "Russian");
	print();
	play();
	return 0;
}
