#include<iostream>
#include <stack>
#include <stdlib.h>
using namespace std;
char goal[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
struct dataNode
{
	char space[16];	   //puzzle
	char state[4];	   //up, down, left, right
	int action;
	int zero;
	int depth;
};

dataNode* newNode(char* space, int action, int zero)
{
	dataNode* node = new dataNode;
	//node->parent = parent;

	// copy data from parent node to current node
	if (action == -1)	//root's puzzle copy
		memcpy(node->space, space, sizeof node->space);
	else
	{
		if (action == 0) //up puzzle copy 
		{
			int tmp = space[zero - 4] - '0';
			for (int y = 0; y < 16; y++)
				node->space[y] = space[y];
			node->space[zero - 4] = '0';
			node->space[zero] = tmp + '0';
			node->zero = zero - 4;
		}
		else if (action == 1) //down puzzle copy 
		{
			int tmp = space[zero + 4] - '0';
			for (int y = 0; y < 16; y++)
				node->space[y] = space[y];
			node->space[zero + 4] = '0';
			node->space[zero] = tmp + '0';
			node->zero = zero + 4;
		}
		else if (action == 2)	//left puzzle copy 
		{
			int tmp = space[zero - 1] - '0';
			for (int y = 0; y < 16; y++)
				node->space[y] = space[y];
			node->space[zero - 1] = '0';
			node->space[zero] = tmp + '0';
			node->zero = zero - 1;
		}
		else if (action == 3) //right puzzle copy
		{
			int tmp = space[zero + 1] - '0';
			for (int y = 0; y < 16; y++)
				node->space[y] = space[y];
			node->space[zero + 1] = '0';
			node->space[zero] = tmp + '0';
			node->zero = zero + 1;
		}
	}

	node->action = action;

	return node;
}

int unsolvable(int space[16], int blank)
{
	int error_con = 0;
	for (int k = 0; k < 16; k++)
	{
		for (int j = k+1; j < 16; j++)
		{
			if (space[k] != 0 &&space[j] != 0 && space[k] > space[j])
			{
				error_con++;
			}
		}
	}
	//cout << error_con << endl;
	if ((error_con % 2 == 1&&(blank/4)%2==0)|| (error_con % 2 == 0 && (blank / 4) % 2 == 1))
		return -1;
	else
		return 1;
}
int test_goal(dataNode* a)
{
	for (int i = 0; i < 16; i++)
	{
		if ((a->space[i]) != goal[i])
			return -1;
	}
	return 1;
}
int test_goal(int space[16])
{
	for (int i = 0; i < 16; i++)
	{
		if ((space[i]) != i)
			return -1;
	}
	return 1;
}


dataNode* successor(dataNode* a, int zero)
{
	int up = 0, down = 0, left = 0, right = 0;
	char state[4] = { '0','0','0','0' };
	if (zero / 4 == 0)
		down = 1;
	else if (zero / 4 == 1)
	{
		up = 1;
		down = 1;
	}
	else if (zero / 4 == 2)
	{
		up = 1;
		down = 1;
	}
	else
	{
		up = 1;
	}
	if (zero % 4 == 0)
	{
		right = 1;
	}
	else if (zero % 4 == 1)
	{
		right = 1;
		left = 1;
	}
	else if (zero % 4 == 2)
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

static long long int coco = 1;
dataNode* final = NULL;
void ids(dataNode* pq, int hight)
{
	dataNode* min = NULL;
	if (final != NULL)
		return;
	if (pq->depth <= hight) {
		min = pq;
		
		if (test_goal(min) == 1)
		{
			final = min;
			//cout << final->con << endl;
			return;
		}
		coco++;
		if (min->state[0] == '1' && final == NULL)
		{	
			//cout << min->con << ":UP" << min->depth <<endl;
			dataNode* child = newNode(min->space, 0, min->zero);
			child = successor(child, child->zero);
			child->depth = min->depth + 1;
			ids(child, hight);
			delete(child);
		}
		if (min->state[1] == '1' && final == NULL)
		{
			//cout << min->con << ":DOWN :" << min->depth<< endl;
			dataNode* child = newNode(min->space, 1, min->zero);
			child = successor(child, child->zero);
			child->depth = min->depth + 1;
			ids(child, hight);
			delete(child);
		}
		if (min->state[2] == '1' && final == NULL)
		{
			//cout << min->con << ":LEFT" << min->depth << endl;
			dataNode* child = newNode(min->space, 2, min->zero);
			child = successor(child, child->zero);
			child->depth = min->depth + 1;
			ids(child,hight);
			delete(child);
		}
		if (min->state[3] == '1' && final == NULL)
		{
			//cout << min->con << ":RIGHT" << min->depth << endl;
			dataNode* child = newNode(min->space, 3, min->zero);
			child = successor(child, child->zero);
			child->depth = min->depth + 1;
			ids(child, hight);
			delete(child);
		}
	}
	else
	{
		return;
	}
}

void solve(int space[16], int zero,int hight)
{
	stack<dataNode*> pq;

	char spa[16];
	for (int i = 0; i < 16; i++)
	{
		if(space[i]>9)
			spa[i] = space[i]-10 + 'A';
		else
			spa[i] = space[i] + '0';
	}

	dataNode* root = newNode(spa, -1, zero);
	root->zero = zero;
	root = successor(root, zero);
	root->depth = 0;

	pq.push(root);
    for(int i=0;i<=hight;i++)
		ids(root, i);
}
void print(int move)
{
	if (move >=0)
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
}
int main()
{
	char a;
	int spa[16];
	int zero;
	int depth;
	cin >> a;//[
	for (int i = 0; i < 16; i++)
	{
		cin >> a;
		if (a == 'A' || a == 'B' || a == 'C' || a == 'D' || a == 'E' || a == 'F')
			spa[i] = a - 'A' + 10;
		else
			spa[i] = a - '0';
		if (spa[i] == 0)
			zero = i;
	}
	cin >> a;
	cin >> depth;
	if (unsolvable(spa, zero) == -1)
		cout << "No solution!!" << endl;
	else if (test_goal(spa) == 1)
		cout << "It is the goal state." << endl;
	else
	{
		solve(spa, zero, depth);
		cout << coco-1 << endl;
	}
	return 0;
}

