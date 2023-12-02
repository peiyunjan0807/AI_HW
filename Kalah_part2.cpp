#include<iostream>
using namespace std;

struct Node {
	int house[14];
	int depth;
	int action;
};
Node* newNode(int* house)
{
	Node* node = new Node;
	for (int i = 0; i < 14; i++)
		node->house[i] = house[i];
	return node;
}
int move(int* house, int pickHouse, int turn)
{
	int bean = house[pickHouse];

	int player = turn;//p1=0,p2=1

	house[pickHouse] = 0;

	int i = (pickHouse) % 14;
	while (bean > 0)
	{
		i = (i + 1) % 14;
		bean--;
		if (player == 0 && i != 13)
			house[i]++;
		else if (player == 1 && i != 6)
			house[i]++;
		else if ((player == 0 && i == 13) || (player == 1 && i == 6))
			bean++;
	}

	int j=i;
	int empty = 0;
	if (house[j] == 1 && house[12 - j] != 0 && ((player == 0 && j < 6) || (player == 1 && j > 6)) && j != 6 && j != 13 && j!=pickHouse)
	{
		empty = 1;
	}
	if (empty == 1)
	{
		if (player == 0)
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
	//cout << pickHouse << ":[ ";
	//for (int i = 0;i<14;i++)
	//{
	//	cout << house[i] << " ";
	//}
	//cout << "]" << endl;
	
	if (player == 0 && i == 6)
		return 1;
	else if (player == 1 && i == 13)
		return 1;
	else
		return 0;
}
int evaluate(int* house)
{
	int score;
	score = house[13] - house[6];
	return score;
}

int evaluate_0(int* house)
{
	int score;
	score = house[6] - house[13];
	return score;
}

bool terminal(int* house)
{
	int con = 0;
	
	for (int i = 0 ; i < 6; i++)
		if (house[i] == 0)
			con++;
	if (con == 6)
	{
		for (int i = 7; i < 13; i++)
		{
			house[13] += house[i];
			house[i] = 0;
		}
		return true;
	}
	else
	{
		con = 0;
		
		for (int i = 7; i < 13; i++)
			if (house[i] == 0)
				con++;
		if (con == 6)
		{
			for (int i = 0; i < 6; i++)
			{

				house[6] += house[i];
				house[i] = 0;
			}
			return true;
		}
		
		return false;
	}	
}

int minValue(Node* node, int depthMAX);
int maxValue(Node* node, int depthMAX);

int minValue_0(Node* node, int depthMAX);
int maxValue_0(Node* node, int depthMAX);

int minValue(Node* node, int depthMAX){
	//cout<<node->depth<<" "<<node->action<<" "<<node->house[13]-node->house[6]<<" z\n";
	if (terminal(node->house) ||(node->depth >= depthMAX)){
		int val = evaluate(node->house);
		//for(int i=0;i<14;i++) cout<<node->house[i]<<" ";
		//cout<<"\n"<<node->action<<" "<<node->house[6]<<" "<<node->house[13]<<" z\n";
		//cout<<val<<" ";
		delete(node);
		return val;
	}
	else{
		int val = 1000,tmp;		
		for (int i = 0; i < 6; i++){
			if (node->house[i] != 0){
				Node* n1 = newNode(node->house);
				n1->depth = node->depth;
				n1->action = i;
				int next_act = move(n1->house, n1->action, 0);
				if (next_act == 1) {
					n1->depth+=2;
					tmp = minValue(n1, depthMAX);
				}
				else {
					n1->depth++;
					tmp = maxValue(n1, depthMAX);	
				}
				val = min(val, tmp);
			}
		}//cout<<val<<" ";
		return val;
	}		
}
int maxValue(Node* node, int depthMAX){
	//cout<<node->depth<<" "<<node->action<<" "<<node->house[13]-node->house[6]<<" M\n";
	if (terminal(node->house) || (node->depth >= depthMAX))	{
		int val = evaluate(node->house);
		//for(int i=0;i<14;i++) cout<<node->house[i]<<" ";
		//cout<<"\n"<<node->action<<" "<<node->house[6]<<" "<<node->house[13]<<" M\n";
		//cout<<val<<" ";
		delete(node);
		return val;
	}
	else{		
		int val = -1000,tmp;
		for (int i = 0; i < 6; i++){
			if (node->house[7 + i] != 0){
				Node* n1 = newNode(node->house);
				n1->depth = node->depth;
				n1->action = 7 + i;
				int next_act = move(n1->house, n1->action, 1);
				if (next_act == 1) {
					n1->depth+=2;
					tmp = maxValue(n1, depthMAX);
				}
				else {
					n1->depth++;
					tmp = minValue(n1, depthMAX);	
				}
				val = max(val, tmp);
			}
		}
		return val;
	}			
}

int minValue_0(Node* node, int depthMAX) {
	//cout<<node->depth<<" "<<node->action<<" "<<node->house[13]-node->house[6]<<" z\n";
	if (terminal(node->house) || (node->depth >= depthMAX)) {
		int val = evaluate_0(node->house);
		//for(int i=0;i<14;i++) cout<<node->house[i]<<" ";
		//cout<<"\n"<<node->action<<" "<<node->house[6]<<" "<<node->house[13]<<" z\n";
		//cout<<val<<" ";
		delete(node);
		return val;
	}
	else {
		int val = 1000, tmp;
		for (int i = 0; i < 6; i++) {
			if (node->house[i+7] != 0) {
				Node* n1 = newNode(node->house);
				n1->depth = node->depth;
				n1->action = i+7;
				int next_act = move(n1->house, n1->action, 1);
				if (next_act == 1) {
					n1->depth += 2;
					tmp = minValue_0(n1, depthMAX);
				}
				else {
					n1->depth++;
					tmp = maxValue_0(n1, depthMAX);
				}
				val = min(val, tmp);
			}
		}//cout<<val<<" ";
		return val;
	}
}
int maxValue_0(Node* node, int depthMAX) {
	//cout<<node->depth<<" "<<node->action<<" "<<node->house[13]-node->house[6]<<" M\n";
	if (terminal(node->house) || (node->depth >= depthMAX)) {
		int val = evaluate_0(node->house);
		//for(int i=0;i<14;i++) cout<<node->house[i]<<" ";
		//cout<<"\n"<<node->action<<" "<<node->house[6]<<" "<<node->house[13]<<" M\n";
		//cout<<val<<" ";
		delete(node);
		return val;
	}
	else {
		int val = -1000, tmp;
		for (int i = 0; i < 6; i++) {
			if (node->house[i] != 0) {
				Node* n1 = newNode(node->house);
				n1->depth = node->depth;
				n1->action = i;
				int next_act = move(n1->house, n1->action, 0);
				if (next_act == 1) {
					n1->depth += 2;
					tmp = maxValue_0(n1, depthMAX);
				}
				else {
					n1->depth++;
					tmp = minValue_0(n1, depthMAX);
				}
				val = max(val, tmp);
			}
		}
		return val;
	}
}
int minimaxDecision(int* house, int turn, int depthMAX){
	int action = turn * 7;
	int val[6] = { -1000,-1000,-1000,-1000,-1000,-1000 };
	for (int i = 0; i < 6; i++,action++){
		if (house[action] != 0)
		{
			Node* n1 = newNode(house);
			n1->depth = 0;
			n1->action = action;
			int next_act = move(n1->house, n1->action, turn);
			if (turn == 1)
			{
				if (next_act == 1) {
					n1->depth += 2;
					val[i] = maxValue(n1, depthMAX);
				}
				else {
					n1->depth++;
					val[i] = minValue(n1, depthMAX);
				}
			}
			else
			{
				if (next_act == 1) {
					n1->depth += 2;

					val[i] = maxValue_0(n1, depthMAX);
				}
				else {
					n1->depth++;
					val[i] = minValue_0(n1, depthMAX);
				}
			}
		}
	}
	int max = -1000, index = 0 + turn * 7;
	
	for (int i = 0; i < 6; i++)
	{
		cout << val[i] << " ";
		if (val[i] > max)
		{
			max = val[i];
			index = i;
		}
	}
	action = index + turn * 7;
	//cout << endl << action << endl;
	return action;
}
int main()
{
	int round, players, depth;
	char a;
	int house[14];
	cin >> round;
	for (int i = 0; i < round; i++)
	{
		cin >> a;//[
		for (int j = 0; j < 14; j++)
		{
			cin >> house[j];
		}
		cin >> a;//[
		cin >> players;
		cin >> depth;
		cout << minimaxDecision(house, players, depth) << endl;
	}
}
