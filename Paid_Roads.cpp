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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int INF=0x3f3f3f3f;
struct Graph
{
	const static int maxn=20, maxm=20;
	int ndn, edn, last[maxm];
	int u[maxm], v[maxm], w[maxm], nxt[maxm];
	int alv[maxm], alw[maxm];
	void init(int tn){ndn=tn; edn=0; MST(last,-1);}
	void adde(int tu, int tv, int tw, int talv, int talw)
	{
		u[edn]=tu; v[edn]=tv; w[edn]=tw; alv[edn]=talv; alw[edn]=talw;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};
struct data
{
	int u,m;
	data(int tu,int tm):u(tu),m(tm){};
};
int N,M;
Graph G;
int dp[10][1<<10];
bool inq[10][1<<10];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		G.init(N);
		for(int i=0; i<M; i++)
		{	
			int u,v,alv,w,alw;
			scanf("%d%d%d%d%d", &u, &v, &alv, &alw, &w);
			G.adde(u-1,v-1,w,alv-1,alw);
		}

		MST(dp,0x3f); CLR(inq);		
		queue<data> que;
		que.push(data(0,1));
		dp[0][1]=0;
		inq[0][1]=1;
		while(que.size())
		{
			int u=que.front().u, m=que.front().m;
			for(int e=G.last[u]; ~e; e=G.nxt[e])
			{
				int v=G.v[e];
				int w=G.w[e];
				if(m&(1<<G.alv[e])) w=min(w, G.alw[e]);
				int nm=m|(1<<v);
				if( dp[u][m]+w < dp[v][nm])
				{
					dp[v][nm]=dp[u][m]+w;
					if(!inq[v][nm])
					{
						inq[v][nm]=1;
						que.push(data(v,nm));
					}
				} 
			}
			que.pop();
			inq[u][m]=0;
		}
		
		int ans=INF;
		for(int i=0; i<1<<N; i++) ans=min(ans, dp[N-1][i]);
		
		if(ans<INF) printf("%d\n", ans);
		else puts("impossible");
	}
	return 0;
}
