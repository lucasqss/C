#include <stdio.h>
#define TOT 10000

int main()
{
	int n, i, t[TOT], maior, segundo, test;
	while(1)
	{
		scanf("%d", &n);
		if(n==0)
		{
			break;
		}
		else
		{	
			maior=0;
			segundo=0;
			test=0;
			for(i=0; i<n; i++)
			{
				scanf("%d", (t+i));
			}
			for(i=0; i<n; i++)
			{
				if(maior<t[i])
				{
					maior = t[i];
				}
			}
			for (i = 0; i < n; i++)
			{
				if(test<t[i] && t[i]<maior)
				{
					segundo=(i+1);
					test= t[i];
				}
			}
			printf("%d\n", segundo);
		}
	}
	return 0;
}
