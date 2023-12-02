#include<stdio.h>
#include<iostream> 
using namespace std;

int main()
{
	int n,zero,up, down, left, right;
	int space[9];
	char a;
	cin>>n;

	for (int i = 0; i < n; i++)
	{
		up=0; down=0; left=0; right = 0;
		cin>>a;
		for (int y = 0; y < 9; y++) {
			cin>>space[y];
			if(space[y]==0)
				zero=y;
		}
		cin>>a;
		if(zero/3==0)
		{
			down=1;
		}
		else if(zero/3==1)
		{
			up=1;
			down=1;
		}
		else
		{
			up=1;
		}
		if(zero%3==0)
		{
			right=1;
		}
		else if(zero%3==1)
		{
			right=1;
			left=1;
		}
		else
		{
			left=1;
		}
		printf("%d\n",up+down+right+left);
		if(up==1)
		{
			printf("move 0 to up\n");
			int tmp=space[zero-3];
			space[zero-3]=0;
			space[zero]=tmp;
			printf("[%d",space[0]);
			for(int y=1;y<9;y++)
				printf(" %d",space[y]);
			printf("]\n");
			space[zero-3]=tmp;
			space[zero]=0;
		}
		if(down==1)
		{
			printf("move 0 to down\n");
			int tmp=space[zero+3];
			space[zero+3]=0;
			space[zero]=tmp;
			printf("[%d",space[0]);
			for(int y=1;y<9;y++)
				printf(" %d",space[y]);
			printf("]\n");
			space[zero+3]=tmp;
			space[zero]=0;
		}
		if(left==1)
		{
			printf("move 0 to left\n");
			int tmp=space[zero-1];
			space[zero-1]=0;
			space[zero]=tmp;
			printf("[%d",space[0]);
			for(int y=1;y<9;y++)
				printf(" %d",space[y]);
			printf("]\n");
			space[zero-1]=tmp;
			space[zero]=0;
		}
		if(right==1)
		{
			printf("move 0 to right\n");
			int tmp=space[zero+1];
			space[zero+1]=0;
			space[zero]=tmp;
			printf("[%d",space[0]);
			for(int y=1;y<9;y++)
				printf(" %d",space[y]);
			printf("]\n");
			space[zero+1]=tmp;
			space[zero]=0;
		}
	}
	return 0;
}
