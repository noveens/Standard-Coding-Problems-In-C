#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
	int val;
	struct node *next;
}node;

int segment[4100005];
int arr[4100005];

int min(int a, int b)
{
	if(a < b)
		return a;
	return b;
}

int build_tree(int l, int r, int x)
{
	if(l==r)
	{
		segment[x]=arr[l];
		return(0);
	}
	else
	{
		build_tree(l, (r+l)/2, 2*x);
		build_tree( ((r+l)/2)+1, r, (2*x)+1);
		segment[x]=min(segment[2*x], segment[(2*x)+1]);
	}
	return(0);
}

int query(int l, int r, int left, int right, int index)
{
	if(l <= left && r >= right)
	{
		return segment[index];
	}
	else if(l > right || r < left)
	{
		return INT_MAX;
	}
	else
	{
		int a = query(l, r, left, (left+right)/2, 2*index);
		int b = query(l, r, (left+right)/2+1, right, (2*index)+1);
		return min(a, b);
	}
}

int update(int l, int r, int val, int index, int x)
{
	if(l==r && r==index)
	{
		segment[x] = val;
		return(0);
	}
	else
	{
		if(index <= (l+r)/2)
		{
			update(l, (l+r)/2, val, index, 2*x);
			segment[x] = min(segment[2*x], segment[x]);
		}
		else if(index > (l+r)/2)
		{
			update(((l+r)/2)+1, r, val, index, (2*x)+1);
			segment[x] = min(segment[x], segment[(2*x)+1]);
		}
	}
	return(0);
}

int main(void)
{
	int i, n;
	printf("number of values:\n");
	scanf("%d", &n);

	printf("enter values:\n");
	for(i=1;i<=n;i++)
	{
		scanf("%d", &arr[i]);
	}

	build_tree(1, n, 1);

	while(2>1)
	{
		char abc;
		printf("\ntype of query?\nu: update\nm: find min\nq: quit\n");
		scanf(" %c", &abc);
		if(abc=='m')
		{
			printf("what range?:\n");
			int l,r;
			scanf("%d %d", &l, &r);
			int ans = query(l, r, 1, n, 1);
			printf("ans = %d\n", ans);
		}
		else if(abc=='u')
		{
			int v, val;
			printf("update which index, and to what value?\n");
			scanf("%d %d", &v, &val);
			update(1, n, val, v, 1);
			printf("value is updated!\n");
		}
		else if(abc=='q')
		{
			break;
		}
	}
	return(0);
}