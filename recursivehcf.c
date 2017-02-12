#include <stdio.h>

int hcf(int x, int y)
{
	if(y==0)
		return x;
	
	return(hcf(y, x%y));
}

int main(void)
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int x,y,ans;
		printf("please enter the 2 numbers:\n");
		scanf("%d %d", &x, &y);
		ans = hcf(x,y);
		printf("%d\n", ans);
	}
	return(0);
}
