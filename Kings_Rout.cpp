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

const int maxn=2e5+10, maxm = 4e5+10;

struct Graph
{
	int ndn, edn, ind[maxn], last[maxn];
	int u[maxm], v[maxm], nxt[maxm];
	void init(int _n){ndn=_n; edn=0; MST(last,-1); CLR(ind);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
		ind[_v]++;
	}
};

int N,M;
Graph G;
int ans[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		G.init(N);
		for(int i=0, u, v; i<M; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(v,u);
		}
		priority_queue<int> que;
		for(int i=1; i<=N; i++) if(!G.ind[i]) que.push(i);
		int cnt=0;
		while(que.size())
		{
			int u=que.top(); que.pop();
			ans[cnt++] = u;
			for(int e=G.last[u],v; ~e; e=G.nxt[e])
			{
				v=G.v[e];
				G.ind[v]--;
				if(!G.ind[v]) que.push(v);
			}
		}
		for(int i=cnt-1; i>=0; i--) printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}

