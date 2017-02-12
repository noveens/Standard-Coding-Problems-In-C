#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int val;
	int wt;
	struct node *next;
}node;

int main(void)
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		printf("enter the number of nodes:\n");
		int n,i,j,e;
		scanf("%d", &n);
		node *graph[n+5]; // means an array of pointers to nodes
		for(i=0;i<n+5;i++)
		{
			graph[i]=NULL;
		}
		printf("enter the number of edges:\n");
		scanf("%d", &e);
		for(i=0;i<e;i++)
		{
			int x,y,z;
			printf("from which vertex to which and it's weight:\n");
			scanf("%d %d %d", &x, &y, &z);

			node *temp=(node *)malloc(sizeof(node));
			if(graph[x]!=NULL)
				temp->next=graph[x];
			else
				temp->next=NULL;
			temp->val=y;
			temp->wt=z;
			graph[x]=temp;
		}
		int s,d;
		scanf("%d %d", &s, &d);
		int ans[100]={0};
		int temp[100][2]={0};
		temp[1][1]=1;

		for(i=2;i<100;i++)
		{
			ans[i]=100000;
			temp[i][0]=100000;
			temp[i][1]=0;
		}

		int min=s;
		for(i=1;i<=e;i++)
		{
			node *tem=graph[min];
			while(tem!=NULL)
			{
				if(temp[tem->val][1]==0 && temp[tem->val][0] > temp[min][0] + tem->wt)
				{
					temp[tem->val][0] = temp[min][0] + tem->wt;
				}
				tem=tem->next;
			}

			int rem, y=100000000;

			for(j=1;j<=n;j++)
			{
				if(temp[j][0] < y && temp[j][1]!=1)
				{
					y=temp[j][0];
					rem=j;
				}
			}
			temp[rem][1]=1;
			ans[rem]=temp[rem][0];
			min=rem;
		}

		for(i=1;i<=n;i++)
		{
			if(ans[i] != 100000)
				printf("shortest path from vertex '%d' to vertex '%d' = %d\n", s, i, ans[i]);
			else
				printf("shortest path from vertex '%d' to vertex '%d' = INFINITE\n", s, i);
		}
	}
	return(0);
}
