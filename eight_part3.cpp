#include<stdio.h>
#include<stdlib.h>
#include<iostream> 
using namespace std;

int main()
{
	int n,zero,con=0,row,col,y_row,y_col;
	int space[9];
	char a;
	cin>>n;

	for (int i = 0; i < n; i++)
	{
		con=0;
		cin>>a;
		for (int y = 0; y < 9; y++) {
			cin>>space[y];
			if(space[y]==0)
				zero=y;
		}
		cin>>a;
		for(int y=0;y<9;y++)
		{
			if(space[y] != y && y!=zero)
			{
				int tmp=0;
				row=space[y]/3;
				y_row=y/3;
				col=space[y]%3;
				y_col=y%3;
				if(row==y_row)
				{
					tmp=abs(col-y_col);
				}
				else if(col==y_col)
				{
					tmp=abs(row-y_row);
				}
				else
				{
					tmp=abs(row-y_row)+abs(col-y_col);
				}
				con+=tmp;
			}
		}
		printf("%d\n",con);
	}
	return 0;
}
