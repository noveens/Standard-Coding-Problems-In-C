#include <stdio.h>
#include <string.h>

char arr[100005];
long long cum[100005];
long long rev[100005];
long long final[100005];
long long MOD=1000000007;


// returns pow(x,y) MOD m
long long po(long long x, long long y, long long m)
{
	long long pro=1;
	if(x==1)
		return 1;
	while(y>0)
	{
		if(m==1)
		{
			return(0);
		}
		else if(y&1 != 0)
		{
			pro=((pro%m)*(x%m))%m;
		}
		x=(x*x)%m;
		y=y>>1;
	}
	return pro;
}


//calculates the hash values from left andd right side and stores them in cum[] and rev[]
long long hash(long long n)
{
	long long i=0;
	long long po=1;
	for(i=0;i<n;i++)
	{
		if(i==0)
		{
			cum[i]=(arr[i]-'a')%MOD;
		}
		else
		{
			cum[i]=(((cum[i-1])%MOD)+((arr[i]-'a')*po)%MOD)%MOD;
		}
		po = (po * 26)%MOD;
	}
	i=0;
	po=1;
	for(i=n-1;i>=0;i--)
	{
		if(i==n-1)
		{
			rev[i]=(arr[i]-'a')%MOD;
		}
		else
		{
			rev[i]=(((rev[i+1])%MOD)+((arr[i]-'a')*po)%MOD)%MOD;
		}
		po = (po * 26)%MOD;
	}
	long long j=0;
	for(i=n-1;i>=0;i--)
	{
		final[j]=rev[i];
		j++;
	}
	return(0);
}

int main(void)
{
	scanf("%s", arr);
	long long n=strlen(arr);
	long long t,i;
	hash(n);
	scanf("%lld", &t);
	while(t--)
	{
		long long l,r;
		scanf("%lld %lld", &l, &r);
		long long a1,a2;

		//applying inverse modulo to a1, a2
		// (x/y)%m = x%m * pow(y,m-2)%m
		a1 = (((cum[r-1]-cum[l-2]+MOD)%MOD) * po(po(26,l-1,MOD)%MOD, MOD-2, MOD)%MOD)%MOD;
		a2 = (((final[n-l]-final[n-r-1]+MOD)%MOD) * (po(po(26,n-r,MOD)%MOD, MOD-2, MOD))%MOD)%MOD;

		if(a1==a2)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return(0);
}