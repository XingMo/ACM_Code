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
struct data
{
	int id,a;
	bool operator < (const data &v) const {return a < v.a;}
};
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], w[2*maxn], nxt[2*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
Graph G;
vector<data> node[maxn];
int ans[maxn];
void solve(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	while(~scanf("%d", &N))
	{
		G.init(N);
		CLR(ans);
		data x;
		for(int i=1; i<=N; i++)
		{
			node[i].clear();
			scanf("%d", &x.a);
			x.id=i;
			node[i].push_back(x);
		}
		for(int i=2,u,v,w; i<=N; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		int cnt=0;
		while(1)
		{
			cnt += node[1].size();
			node[1].clear();
			if(cnt==N) break;
			solve(1,0);
		}
		for(int i=1; i<=N; i++) printf("%d ", ans[i]); puts("");
	}
	return 0;
}

void solve(int u, int f)
{
	for(int e=G.last[u],v,getv; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		if(v==f) continue;
//		printf("%d -> %d\n", u, v);
		sort(node[v].begin(), node[v].end());
//		printf("%d have: ", v);
//		for(int i=0; i<(int)node[v].size(); i++) printf("%d ", node[v][i].id);
//		PCUT;
		getv=0;
		for(int i=0; i<(int)node[v].size(); i++) ans[ node[v][i].id ] ++;
		for(int i=0; i<G.w[e] && i<(int)node[v].size(); i++)
		{
			node[u].push_back( node[v][i] );
			getv++;
		}
		node[v].erase(node[v].begin(), node[v].begin()+getv);
		solve(v,u);
	}
}

