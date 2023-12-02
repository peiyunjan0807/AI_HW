#include<stdio.h>
#include<iostream> 
using namespace std;
int main()
{
	int n,error_con=0;
	int space[9];
	char a;
	cin>>n;

	for (int i = 0; i < n; i++)
	{
		error_con = 0;
		cin>>a;
		for (int y = 0; y < 9; y++) {
			cin>>space[y];
		}
		cin>>a;
		
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
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
