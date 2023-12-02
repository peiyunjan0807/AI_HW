#include<iostream>
#include <queue>
#include<stdlib.h>
#include <cstring>
using namespace std;

struct dataNode
{
	char space[9];
	char state[4];
	int action;
	int g, h, f, con;
	int zero;
	dataNode* parent;
};

void print(int move)
{
	if (move == 0)
		cout << "move 0 to up" << endl;
	else if (move == 1)
		cout << "move 0 to down" << endl;
	else if (move == 2)
		cout << "move 0 to left" << endl;
	else
		cout << "move 0 to right" << endl;
}

dataNode* newNode(char* space, int action, int con, int zero,dataNode* parent)
{
	dataNode* node = new dataNode;

	// set pointer for path to root
	node->parent = parent;

	// copy data from parent node to current node
	if(action==-1)
		memcpy(node->space, space, sizeof node->space);
	else
	{
		if (action == 0)
		{
			int tmp = space[zero - 3] - '0';
			for (int y = 0; y < 9; y++)
				node->space[y] = space[y];
			node->space[zero - 3] = '0';
			node->space[zero] = tmp + '0';
			node->zero = zero - 3;
		}
		else if (action == 1)
		{
			int tmp = space[zero + 3] - '0';
			for (int y = 0; y < 9; y++)
				node->space[y] = space[y];
			node->space[zero + 3] = '0';
			node->space[zero] = tmp + '0';
			node->zero = zero + 3;
		}
		else if (action == 2)
		{
			int tmp = space[zero - 1] - '0';
			for (int y = 0; y < 9; y++)
				node->space[y] = space[y];
			node->space[zero - 1] = '0';
			node->space[zero] = tmp + '0';
			node->zero = zero - 1;
		}
		else
		{
			int tmp = space[zero + 1] - '0';
			for (int y = 0; y < 9; y++)
				node->space[y] = space[y];
			node->space[zero + 1] = '0';
			node->space[zero] = tmp + '0';
			node->zero = zero + 1;
		}
	}

	node->action = action;
	node->con = con;

	return node;
}

int unsolvable(int space[9])
{
	int error_con = 0;
	for (int k = 0; k < 9; k++)
	{
		for (int j = k; j < 9; j++)
		{
			if (space[j] != 0 && space[k] > space[j])
			{
				error_con++;
			}
		}
	}
	if (error_con % 2 == 1)
		return -1;
	else
		return 1;
}
int test_goal(dataNode* a)
{
	for (int i = 0; i < 9; i++)
	{
		if ((a->space[i] - '0') != i)
			return -1;
	}
	return 1;
}
int test_goal(int space[9])
{
	for (int i = 0; i < 9; i++)
	{
		if ((space[i]) != i)
			return -1;
	}
	return 1;
}

int heuristic(char space[9])
{
	int con = 0, row, col, y_row, y_col;
	for (int y = 0; y < 9; y++)
	{
		if (space[y] - '0' != y && space[y] != '0')
		{
			int tmp = 0;
			row = (space[y] - '0') / 3;
			y_row = y / 3;
			col = (space[y] = '0') % 3;
			y_col = y % 3;
			if (row == y_row)
			{
				tmp = abs(col - y_col);
			}
			else if (col == y_col)
			{
				tmp = abs(row - y_row);
			}
			else
			{
				tmp = abs(row - y_row) + abs(col - y_col);
			}
			con += tmp;
		}
	}
	return con;
}

struct cmp {
	bool operator ()(dataNode* a, dataNode* b) {
		if (a->f == b->f)
			return a->con > b->con;
		return a->f > b->f;
	}
};

dataNode* successor(dataNode* a, int zero)
{
	int up = 0, down = 0, left = 0, right = 0;
	char state[4] = { '0','0','0','0' };
	if (zero / 3 == 0)
		down = 1;
	else if (zero / 3 == 1)
	{
		up = 1;
		down = 1;
	}
	else
	{
		up = 1;
	}
	if (zero % 3 == 0)
	{
		right = 1;
	}
	else if (zero % 3 == 1)
	{
		right = 1;
		left = 1;
	}
	else
	{
		left = 1;
	}
	if (up == 1)
		state[0] = '1';

	if (down == 1)
		state[1] = '1';

	if (left == 1)
		state[2] = '1';

	if (right == 1)
		state[3] = '1';
	memcpy(a->state, state, sizeof a->state);
	return a;
}

void solve(int space[9], int zero)
{
	priority_queue<dataNode*, vector<dataNode*>, cmp> pq;

	char spa[9];
	for (int i = 0; i < 9; i++)
	{
		spa[i] = space[i] + '0';
	}
	int nextStateCount = 0;
	dataNode* root = newNode(spa, -1, nextStateCount++, zero,NULL);
	dataNode* final = NULL;
	root->zero = zero;
	root = successor(root, zero);
	root->g = 0;
	root->h = heuristic(spa);
	root->f = root->h;

	pq.push(root);

	char sp[9];
	dataNode* min=NULL;
	while (!pq.empty())
	{
		min = pq.top();
		pq.pop();

		if (test_goal(min) == 1)
		{
			final = min;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			if (min->state[i] == '1')
			{
				dataNode* child = newNode(min->space, i, nextStateCount++, min->zero, min);
				child = successor(child, child->zero);
				memcpy(sp, child->space, sizeof(child->space));
				child->h = heuristic(sp);
				child->g = min->g + 1;
				child->f = child->g + child->h;
				pq.push(child);
			}
		}
	}
	if (final == NULL)
	{
		cout << "No solution!!" << endl;
	}
	else
	{
		vector<int> a;
		dataNode* current = min;

		while (current != NULL)
		{
			a.push_back(current->action);
			current = current->parent;
		}
		for (int i = a.size()-2; i >=0 ; i--)
		{
			print(a[i]);
		}
	}
}

int main()
{
	char a;
	int spa[9];
	int zero;
	cin >> a;//[
	for (int i = 0; i < 9; i++)
	{
		cin >> spa[i];
		if (spa[i] == 0)
			zero = i;
	}
	cin >> a;//]
	if (unsolvable(spa) == -1)
		cout << "No solution!!" << endl;
	else if (test_goal(spa) == 1)
		cout << "It is the goal state." << endl;
	else
	{
		solve(spa, zero);
	}
	return 0;
}

