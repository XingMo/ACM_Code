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
#define PCUT puts("\n----------")

const int maxn=1e5+10;
int N, have[4][maxn], tend[4], cnt[15];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(tend); CLR(cnt);
		int zero=0, rem=0;
		for(int i=0,x; i<N; i++)
		{
			scanf("%d", &x);
			have[x%3][tend[x%3]++] = x;
			if(!x) zero++;
			rem = (rem+x)%3;
		}
		
		if(!zero) puts("-1");
		else
		{
			sort(have[1], have[1]+tend[1]);
			sort(have[2], have[2]+tend[2]);
			int del1=0, del2=0;
			if(rem==1)
			{
				if(tend[1]==0) del2=2;
				else del1=1;
			}
			if(rem==2)
			{
				if(tend[2]==0) del1=2;
				else del2=1;
			}
			for(int i=0; i<tend[0]; i++) cnt[have[0][i]] ++ ;
			for(int i=del1; i<tend[1]; i++) cnt[ have[1][i] ] ++;
			for(int i=del2; i<tend[2]; i++) cnt[ have[2][i] ] ++;
			int lead=0;
			for(int i=9; i>=0; i--)
			{
				for(int j=0; j<cnt[i]; j++) 
				{
					if(i) lead=1;
					if(!i && !lead) break;
					putchar(i+'0');
				}
			}
			if(!lead) putchar('0');
			puts("");
		}
	}
	return 0;
}

