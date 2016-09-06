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

const int maxn=100+10;
int N,M,Q;
int id[maxn][maxn];
int ans[maxn][maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &M, &Q))
	{
		CLR(ans);
		for(int i=0; i<N; i++) for(int j=0; j<M; j++) id[i][j] = M*i+j;
//		for(int i=0; i<N; i++,puts("")) for(int j=0; j<M; j++) printf("%d ", id[i][j]);
		for(int q=0, opt, r, c, x, fir; q<Q; q++)
		{
			scanf("%d", &opt);
			if(opt==1)
			{
				scanf("%d", &r); r--;
				fir = id[r][0];
				for(int i=0; i<M-1; i++) id[r][i] = id[r][i+1];
				id[r][M-1] = fir;
			}
			if(opt==2)
			{
				scanf("%d", &c); c--;
				fir = id[0][c];
				for(int i=0; i<N-1; i++) id[i][c] = id[i+1][c];
				id[N-1][c] = fir;
			}
			if(opt==3)
			{
				scanf("%d%d%d", &r, &c, &x); r--; c--;
				fir = id[r][c];
				ans[fir/M][fir%M] = x;
			}
		}
//		for(int i=0; i<N; i++,puts("")) for(int j=0; j<M; j++) printf("%d ", id[i][j]);
		for(int i=0; i<N; i++,puts("")) for(int j=0; j<M; j++) printf("%d ", ans[i][j]);
	}
	return 0;
}

