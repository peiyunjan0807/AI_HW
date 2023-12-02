#include<iostream>
#include <queue>
#include<string.h>
using namespace std;
struct arr{
	char space[9];
	int num;
	int con;
	arr (int* s,int n,int c)
	{
		for(int i=0;i<9;i++)
		{
			space[i]=s[i]+'0';
		}
		num=n;
		con=c;
	}
};
struct cmp{
	bool operator ()(arr a,arr b){
		if(a.num==b.num)
			return a.con>b.con; 
		return a.num>b.num;
	}
};
int main()
{
	char str[7],a;
	int spa[9],x,y,con=0;
	priority_queue <arr, vector<arr>, cmp > s;
	while(cin>>str)
	{
		if(!strcmp(str, "enqueue"))
		{
			cin>>a;//[
			for(int i=0;i<9;i++)
			{
				cin >> spa[i];
			}
			cin>>a;//]
			cin>>a;//(
			cin>>x;
			cin>>a;//,
			cin>>y;
			cin>>a;//)
			arr tmp=arr(spa,x+y,con);
			s.push(tmp);
			cout<<"Insert OK!"<<endl;
			con++;
		}
		else if(!strcmp(str, "dequeue"))
		{
			if(!s.empty())
			{
				arr top= s.top();
				s.pop();
				cout<<"Got";
				cout<<" ["<<top.space[0];
				for(int i=1;i<9;i++)
				{
					cout<<" "<<top.space[i];
				}
				cout<<"]"<<endl;
			}
			else{
				cout<<"Queue is empty!!"<<endl;
			}	
		}
		else
		{
			break;
		}
	}	
	return 0;
} 
