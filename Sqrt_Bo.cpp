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

const LL Lim = 4294967296;
char str[110];

int Get(LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf(" %s", str))
	{
		if(strlen(str)>10) puts("TAT");
		else
		{
			LL num = atoll(str);
			if(num>=Lim || num==0) puts("TAT");
			else printf("%d\n", Get(num));
		}
	}
	return 0;
}

int Get(LL num)
{
	for(int i=1; ; i++)
	{
		num = sqrt(num);
		if(num==1) return i;
	}
}
