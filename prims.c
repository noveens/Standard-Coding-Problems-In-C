#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define s(x) scanf("%lld", &x) 
#define p(x) printf("%lld\n", x)

typedef struct node
{
	int val;
	int wt;
	struct node *next;
}node;

node *graph[100005];
long long heap[100005];
long long map[100005];
long long ulta_map[100005];
long long done[100005];
long long len=0;
long long ans=0;

long long heapify_top(long long s)
{
	long long min=s/2;
	if(s/2>=1 && heap[s]<heap[min])
		min=s;
	
	if(min!=s/2)
	{
		long long temp=heap[s/2];
		heap[s/2]=heap[min];
		heap[min]=temp;
		
		temp=map[s/2];
		map[s/2]=map[min];
		map[min]=temp;
		
		ulta_map[map[s/2]]=s/2;
		ulta_map[map[min]]=min;

		heapify_top(s/2);
	}

	return(0);
}

long long heapify(long long s)
{
	long long min=s;
	if(2*s<=len && heap[2*s]<heap[min])
		min=2*s;

	if((2*s)+1<=len && heap[(2*s)+1]<heap[min])
		min=(2*s)+1;
	
	if(min!=s)
	{
		long long temp=heap[s];
		heap[s]=heap[min];
		heap[min]=temp;
		
		temp=map[s];
		map[s]=map[min];
		map[min]=temp;
		
		ulta_map[map[s]]=s;
		ulta_map[map[min]]=min;

		heapify(min);
	}

	return(0);
}

long long build_heap(long long n)
{
	long long i;
	for(i=1;i<=n;i++)
	{
		heap[i]=INT_MAX;
		map[i]=i;
		ulta_map[i]=i;
	}
	heap[1]=0;
	len=n;
	return(0);
}

long long delete_min()
{
	ans += heap[1];

	done[map[1]]=1;
	
	long long temp=heap[1];
	heap[1]=heap[len];
	heap[len]=temp;
	
	temp=map[1];
	map[1]=map[len];
	map[len]=temp;
		
	ulta_map[map[1]]=1;
	ulta_map[map[len]]=len;
	
	len--;

	heapify(1);

	return(0);
}

int print()
{
	long long i;
	for(i=1;i<=len;i++)
	{
		printf("heap[%lld]=%lld, vertex=%lld, index should be %lld\n", i, heap[i], map[i], ulta_map[map[i]]);
	}
}

int main(void)
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		long long n,m,i,j;
		s(n);
		s(m);

		ans=0;
		long long sum=0;

		for(i=0;i<n+5;i++)
		{
			graph[i]=NULL;
			heap[i]=0;
			done[i]=0;
		}
		len=0;

		for(i=0;i<m;i++)
		{
			long long x,y,z;
			s(x);
			s(y);
			s(z);
			sum += z;

			node *temp=(node *)malloc(sizeof(node));
			temp->val=x;
			temp->wt=z;
			temp->next=graph[y];
			graph[y]=temp;

			temp=(node *)malloc(sizeof(node));
			temp->val=y;
			temp->wt=z;
			temp->next=graph[x];
			graph[x]=temp;
		}

		build_heap(n);

		while(len!=0)
		{	
			// map returns vertex inputs heap_index
			// ulta_map returns heap_index inputs vertex
			node *temp=graph[map[1]];
			delete_min();
			while(temp!=NULL)
			{
				if(done[temp->val] == 0)
				{
					if(temp->wt < heap[ulta_map[temp->val]])
					{
						heap[ulta_map[temp->val]] = temp->wt;
						heapify_top(ulta_map[temp->val]);
					}
				}
				temp=temp->next;
			}
		}
		p(sum-ans);
	}
	return(0);
}
