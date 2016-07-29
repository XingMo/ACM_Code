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

const int maxn=1e5+10;
const int INF=0x3f3f3f3f;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[2*maxn], v[2*maxn], nxt[2*maxn];
	int deg[maxn];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1); CLR(deg);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
		deg[_v]++;
	}
};
int N;
Graph G;
int dp[2][maxn];
int son[maxn];

int dfs(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d", &N);
		if(N==1){puts("0"); continue;}
		if(N==2){scanf("%*d%*d"); puts("1"); continue;}
		G.init(N);
		
		for(int i=1,u,v; i<N; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		
		CLR(dp); CLR(son);
		int root=0, leaf_cnt=0;
		for(int i=1; i<=G.ndn; i++)
		{
			if(!root && G.deg[i]!=1) root = i;
			if(G.deg[i]==1)leaf_cnt++;
		} 
//		printf("root = %d\n", root);
		dfs(root,-1);
		if(leaf_cnt&1) printf("%d\n", dp[1][root]);
		else printf("%d\n", dp[0][root]);
	}
	return 0;
}

int dfs(int u,int f)
{
	if(G.deg[u]==1)
	{
		son[u]=1;
		return 0;
	}
	int child=0;
	for(int e=G.last[u], v; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		if(v==f) continue;
		dfs(v,u);
		dp[0][u] += dp[0][v] + ((son[v]&1)?1:2); 
		son[u] += son[v];
		child++;
	}

	dp[1][u]=INF;
	for(int e=G.last[u], v; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		if(v==f) continue;
		if(child>1 && son[v]==1) dp[1][u] = min(dp[1][u], dp[0][u]);
		if(dp[1][v]>=INF) continue;
		
		dp[1][u] = min(dp[1][u], dp[0][u]-dp[0][v]+dp[1][v]+ ((son[v]&1)?1:-1));
	}
	return 0;
}
