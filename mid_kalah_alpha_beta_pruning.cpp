#include<iostream>
using namespace std;
long long int node_con = 0;
int act = 0;

struct Node {
	int house[14];
	int depth;
	int action;
};
Node* newNode(int* house)
{
	node_con++;
	Node* node = new Node;
	for (int i = 0; i < 14; i++)
		node->house[i] = house[i];
	return node;
}
int move(int* house, int pickHouse)
{
	
	int bean = house[pickHouse];

	int player = 0;//p1=0,p2=1
	if(pickHouse>6)
		player=1;
		
	house[pickHouse] = 0;
	
	int i = pickHouse;
	int check=bean;
	int last_place=i;
	//check
	while(check>0)
	{
		last_place = (last_place + 1) % 14;
		check--;
		if ((player == 0 && last_place == 13) || (player == 1 && last_place == 6))
			check++;
	}
	
	int flag=0;
	if(house[last_place]==0)
		flag=1;
		
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
	if (house[12-j]!=0 && flag==1 && ((player == 0 && j < 6) || (player == 1 && j > 6)) && j != 6 && j != 13 && j!=pickHouse)
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
	

	if (player == 0 && i == 6)
		return 1;
	else if (player == 1 && i == 13)
		return 1;
	else
		return 0;
}
int evaluate(int* house,int turn)
{
	int score;
	if(turn==1)
		score = house[13] - house[6];
	else
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

int minValue(int turn,Node* node, int depthMAX, int alpha, int beta);
int maxValue(int turn,Node* node, int depthMAX, int alpha, int beta);


int minValue(int turn,Node* node, int depthMAX,int alpha,int beta){
	
	if (terminal(node->house) ||(node->depth >= depthMAX)){
		int val = evaluate(node->house,turn);
		delete(node);
		return val;
	}
	else{
		int val = 1000,tmp;
		int index=0;
		int start_addr = (turn == 0) ? 7: 0;	
		for (int i = 0; i < 6; i++){
			if (node->house[start_addr+i] != 0){
				
				Node* n1 = newNode(node->house);
				n1->depth = node->depth;
				n1->action = i+start_addr;
				
				int next_act = move(n1->house, n1->action);
				if (next_act == 1) {
					n1->depth+=2;
					tmp = minValue(turn, n1, depthMAX, alpha, beta);
				}
				else {
					n1->depth++;
					tmp = maxValue(turn, n1, depthMAX, alpha, beta);
				}
				if(val>tmp)
					index=i+start_addr;
				val = min(val, tmp);
				beta = min(beta, val);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		act=index;
		return val;
	}		
}
int maxValue(int turn,Node* node, int depthMAX, int alpha, int beta){
	
	if (terminal(node->house) || (node->depth >= depthMAX))	{
		int val = evaluate(node->house,turn);
		delete(node);
		return val;
	}
	else{		
		int val = -1000,tmp;
		int index=0;
		int start_addr = (turn == 1) ? 7: 0;
		for (int i = 0; i < 6; i++){
			if (node->house[start_addr + i] != 0){
				Node* n1 = newNode(node->house);
				n1->depth = node->depth;
				n1->action = start_addr + i;
				
				int next_act = move(n1->house, n1->action);
				if (next_act == 1) {
					n1->depth+=2;
					tmp = maxValue(turn, n1, depthMAX, alpha, beta);
				}
				else {
					n1->depth++;
					tmp = minValue(turn, n1, depthMAX, alpha, beta);
				}
				if(val<tmp)
					index=i+start_addr;
				val = max(val, tmp);
				alpha = max(alpha, val);  
				if (beta <= alpha)
				{	
					break;
				}
			}
		}
		act=index;
		return val;
	}			
}

int minimaxDecision(int* house, int turn, int depthMAX){
	
	int val=0;
	Node* n1 = newNode(house);
	n1->depth = 0;
	n1->action=-1;
	val=maxValue(turn, n1,depthMAX,-1000,1000);
	
	cout <<"node數: " <<node_con << endl;
	cout<<"估計val值: " <<val<<endl<<"最優選擇: ";
	
	return act;
}
int main()
{
	int round, players, depth;
	char a;
	int house[14];
	cout<<"輸入回合數: ";
	cin >> round;
	cout<<endl;
	for (int i = 0; i < round; i++)
	{
		node_con = 0;
		cout<<"輸入狀態: ";
		cin >> a;//[
		for (int j = 0; j < 14; j++)
		{
			cin >> house[j];
		}
		cin >> a;//[
		cout<<"輸入玩家: ";
		cin >> players;
		cout<<"輸入最深度: ";
		cin >> depth;
		cout << minimaxDecision(house, players, depth) << endl<<endl;
	}
}
