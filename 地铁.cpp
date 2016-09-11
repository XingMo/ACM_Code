/*
CSU - 1808 （湖南省赛16）
给定一张图，每条边有一个距离和颜色
问从 1到 n的最短路为多少
其中一条路径的长度不仅要算上距离
还要算上相邻两条边颜色的差

如果对每个点记录从某个颜色转移过来的最短路肯定是不现实的
以边为点跑最短路肯定也是不现实的，这种做法与前者无本质区别
但在CSUOJ上这两种做法都能过，可能是数据比较弱
正解是拆点，一个点每连出去一条边，就拆一个点出来
然后按颜色从小到大在相邻的内点中连上边，边权为颜色差
然后其他点按原有距离为边权连边
最终就转化为多源多汇的最短路
*/
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

const int maxn=1e5+10;
struct Graph
{
	int ndn,edn,last[3*maxn];
	int u[5*maxn],v[5*maxn],w[5*maxn],nxt[5*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
struct data
{
	int v, c, w;
	data(){}
	data(int _v,int _c,int _w):v(_v),c(_c),w(_w){}
	bool operator < (const data &rhs) const
	{
		if(c != rhs.c) return c < rhs.c;
		if(v != rhs.v) return v < rhs.v;
		if(w != rhs.w) return w < rhs.w;
		return 0;
	}
};

int N,M;
Graph G;
vector<data> in[maxn];
vector<int> id[maxn];

LL dist[3*maxn];
bool done[3*maxn];

LL dijkstra(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		for(int i=1; i<=N; i++) in[i].clear(), id[i].clear();
		for(int i=0,u,v,c,w; i<M; i++)
		{
			scanf("%d%d%d%d", &u, &v, &c, &w);
			in[u].push_back({v,c,w}); in[v].push_back({u,c,w});
		}
		for(int i=1; i<=N; i++) sort(in[i].begin(), in[i].end());
		int tot=2;
		for(int i=1; i<=N; i++) for(int j=0; j<(int)in[i].size(); j++) id[i].push_back(++tot);
		G.init(tot);
		for(int i=0; i<(int)in[1].size(); i++) G.adde(1, id[1][i], 0);
		for(int i=0; i<(int)in[N].size(); i++) G.adde(id[N][i], 2, 0);
		for(int i=1; i<=N; i++) for(int j=0; j<(int)in[i].size(); j++)
		{
			int v=in[i][j].v, c=in[i][j].c, w=in[i][j].w;
			int tid=lower_bound(in[v].begin(), in[v].end(), data(i,c,w))-in[v].begin();
			G.adde(id[v][tid], id[i][j], w);
			if(j)
			{
				G.adde(id[i][j-1], id[i][j], abs(in[i][j-1].c - in[i][j].c));
				G.adde(id[i][j], id[i][j-1], abs(in[i][j-1].c - in[i][j].c));
			}
		}
//		for(int i=0; i<G.edn; i++) printf("%d->%d %d\n", G.u[i], G.v[i], G.w[i]);
		
		cout << dijkstra(1,2) << "\n";
	}
	return 0;
}

struct dstr
{
	int u; LL d;
	bool operator < (const dstr &rhs) const {return d > rhs.d;}
};
LL dijkstra(int sta, int end)
{
	priority_queue<dstr> pq;
	pq.push({sta,0});
	MST(dist,0x3f);
	dist[sta]=0;
	
	while(pq.size())
	{
		int u=pq.top().u;
		LL d=pq.top().d;
		pq.pop();
		if(d>dist[u]) continue;
		for(int e=G.last[u],v; ~e; e=G.nxt[e])
		{
			v=G.v[e];
			if(dist[u]+G.w[e] < dist[v])
			{
				dist[v] = dist[u]+G.w[e];
				pq.push({v,dist[v]});
			}
		}
	}
	
	return dist[end];
}
