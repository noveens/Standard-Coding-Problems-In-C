#include<stdio.h>

int arr[10000];

int sort(int start, int n)
{
	if(start==n-1 || n==0)
		return(0);

	int fun[10000],i,pivot=arr[start],g=0,now;
	for(i=start+1;i<n;i++)
	{
		if(arr[i]<=pivot)
		{
			fun[g]=arr[i];
			g++;
		}
	}
	printf("Entered!\n");
	fun[g]=pivot;
	now=g;
	g++;
	for(i=start+1;i<n;i++)
	{
		if(arr[i]>pivot)
		{
			fun[g]=arr[i];
			g++;
		}
	}
	for(i=start;i<n;i++)
		arr[i]=fun[i];
	sort(start,now);
	sort(now,n-now-1);
	return(0);
}

int main(void)
{
	int n,i;
	scanf("%d", &n);
	for(i=0;i<n;i++)
		scanf("%d", &arr[i]);
	sort(0,n);
	for(i=0;i<n;i++)
		printf("%d ", arr[i]);
	printf("\n");
	return(0);
}
