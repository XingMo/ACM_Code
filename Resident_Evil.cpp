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
#include <complex>
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

const int maxn=3000+5;
struct BIT
{
	bool bit[maxn][maxn], siz;
	void init(int _n){siz=_n; CLR(bit);}
	void add(int x1, int y1, int x2, int y2, int b)
	{
		if(!(b&1)) return;
		for(int i=x1; i<=siz; i+=i&-i)
		{
			for(int j=y1; j<=siz; j+=j&-j)
			{
				bit[i][j] ^= b&1;
			}
		}
		for(int i=x2+1; i<=siz; i+=i&-i)
		{
			for(int j=y2+1; j<=siz; j+=j&-j)
			{
				bit[i][j] ^= b&1;
			}
		}
	}
	int sum(int x1, int y1, int x2, int y2)
	{
		int res=0;
		for(int i=x1-1; i>0; i-=i&-i)
		{
			for(int j=y1-1; j)
		}
	}
}
int N,M;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		char opt;
		int x1,y1,x2,y2,k,a,b;
		for(int m=0; m<M; m++)
		{
			scanf(" %c", &opt);
			if(opt=='P')
			{
				scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
				for(int i=0; i<k; i++)
				{
					scanf("%d%d", &a, &b);
					bit[a].add(x1,y1,x2,y2,b);
				}
			}
			else
			{
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				for(int i=1; i<=50; i++) printf("%d ", bit[i].sum(x1,y1,x2,y2));
			}
		}
	}
	return 0;
}

