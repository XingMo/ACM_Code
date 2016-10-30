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

const int maxn=2e5+10;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[2*maxn], v[2*maxn], nxt[2*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

int N,M,K;
bool vis[maxn];
int col[maxn], vec[maxn], vend;
Graph G;

void dfs(int);
int findmax(int*,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d%d", &N, &M, &K))
	{
		G.init(N); CLR(vis);
		for(int i=1; i<=N; i++) scanf("%d", &col[i]);
		for(int i=1,u,v; i<=M; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		int ans = 0;
		for(int i=1; i<=N; i++) if(!vis[i])
		{
			vend=0;
			dfs(i);
			ans += vend - findmax(vec,vend);
		}
		printf("%d\n", ans);
	}
	return 0;
}

void dfs(int u)
{
	vis[u] = 1;
	vec[vend++] = col[u];
	for(int e=G.last[u]; ~e; e=G.nxt[e]) if(!vis[G.v[e]]) dfs(G.v[e]);
}

int findmax(int arr[], int siz)
{
	if(!siz) return 0;
	sort(arr, arr+siz);
	int res=0, l=0, np=arr[0];
	for(int i=0; i<siz; i++)
	{
		if(arr[i] != arr[l])
		{
			res = max(res, i-l);
			l = i;
		}
	}
	res = max(res, siz-l);
	return res;
}
