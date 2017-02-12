#include <stdio.h>

int mergesort(int arr[],int n)
{
	if(n==1)
		return(0);

	int mid = n/2, i;
	int left[mid];
	int right[n-mid];

	for(i=0;i<mid;i++)
		left[i] = arr[i];

	for(i=mid;i<n;i++)
		right[i-mid] = arr[i];

	mergesort(left,mid);
	mergesort(right,n-mid);
	merge(left,mid,right,n-mid,arr);

	return(0);
}

int merge(int left[], int nl, int right[], int nr, int arr[])
{
	int i=0, j=0, k=0;

	while(i<nl && j<nr)
	{
		if(left[i] > right[j])
		{
			arr[k] = right[j];
			j++;
			k++;
		}
		else
		{
			arr[k] = left[i];
			i++;
			k++;
		}
	}

	while(i < nl)
	{
		arr[k] = left[i];
		i++;
		k++;
	}

	while(j < nr)
	{
		arr[k] = right[j];
		j++;
		k++;
	}

	return(0);
}

int main(void)
{
	int n, i;
	printf("enter the number of values:\n");
	scanf("%d", &n);
	int arr[n];
	printf("enter the values of the elements:\n");

	for(i=0;i<n;i++)
		scanf("%d", &arr[i]);

	mergesort(arr, n);

	printf("the sorted array is:\n");
	for(i=0;i<n;i++)
		printf("%d ", arr[i]);
	printf("\n");

	return (0);
}