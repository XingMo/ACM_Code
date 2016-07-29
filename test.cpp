#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <string>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

LL exgcd(LL a, LL b, LL &x, LL &y)
{
	if(!b) {x=1; y=0; return a;}
	LL t,res;
	res = exgcd(b,a%b,x,y);
	t=x, x=y, y=t-a/b*y;
	return res;
}

LL check(LL b)
{
	LL lim=sqrt(b);
	for(int i=2; i<=lim; i++)
	{
		if(b%i==0) return i;
	}
	return 0;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	LL a=2,b=6,x,y;
	for(int i=1; i<=100; i++)
	{
		do
		{
			b=rand()%100000;
		} while(!(a=check(b)));
		exgcd(a,b,x,y);
		printf("%lld %lld %lld %lld\n", a, b, x, y);	
	}
	return 0;
}

