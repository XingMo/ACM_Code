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

int N,D,L;
int ans[200];
int Get(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &D, &L))
	{
		int x,y;
		if(!(N&1))
		{
			if(Get(D))
			{
				for(int i=0; i<N; i++) printf("%d ", ans[i]);
				puts("");
			}
			else puts("-1");
		}
		else
		{
			N--;
			bool ok=0;
			for(int f=1; f<=L; f++)
			{
				if(Get(f-D))
				{
					printf("%d ", f);
					for(int i=0; i<N; i++) printf("%d ", ans[i]);
					puts("");
					ok=1;
					break;
				}
			}
			if(!ok) puts("-1");
		}
	}
	return 0;
}

int Get(int d)
{
	int ad = abs(d);
//	printf("%d\n", d);
	if(ad<=(L-1)*N/2)
	{
		for(int i=0; i<N; i+=2)
		{
			int det = min(ad, L-1), x=1, y=x+det;
			if(d<0) swap(x,y);
			ans[i] = y;
			ans[i+1] = x;
			ad -= det;
		}
	}
	else return 0;
}
