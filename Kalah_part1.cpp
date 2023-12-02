#include<iostream>
using namespace std;
bool relocation(int* house, int pickHouse)
{
	int bean = house[pickHouse];
	
	int player = 0;//p1=1,p2=2
	if (pickHouse < 6)
	{
		player = 1;
	}
	else
	{
		player = 2;
	}

	int j;
	if (((bean + pickHouse) > 14))
		j = ((bean + pickHouse) % 14) + 1;
	else
		j = ((bean + pickHouse) % 14);
	int empty = 0;
	if (house[j] == 0 && house[12-j] != 0 &&((player==1 && j<6)|| (player == 2 && j > 6))&& j!=6&&j!=13)
	{
		empty = 1;
	}
	house[pickHouse] = 0;

	int i = (pickHouse) % 14;
	while (bean >0)
	{
		i = (i + 1) % 14;
		bean--;
		if (player == 1 && i != 13)
			house[i]++;
		else if (player == 2 && i != 6)
			house[i]++;
		else if ((player == 1 && i == 13) || (player == 2 &&i == 6))
			bean++;
	}

	if (empty == 1)
	{
		if (player == 1)
		{
			house[6] += house[12 - j] + 1;
		}
		else
		{
			house[13] += house[12 - j] + 1;
		}
		house[12 - j] = 0;
		house[j] = 0;
	 }

	cout << "[" << house[0];
	for (int k = 1; k < 14; k++)
		cout << " " << house[k];
	cout << "]" << endl;

	if (player == 1 && i == 6)
		return true;
	else if (player == 2 && i == 13)
		return true;
	else
		return false;

}
int main()
{
	int round, choose;
	char a;
	int box[14];
	cin >> round;
	for (int i = 0; i < round; i++) {
		cin >> a;//[
		for (int j = 0; j < 14; j++)
		{
			cin >> box[j];
		}
		cin >> a;//[
		cin >> choose;
		if (relocation(box, choose))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
