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

const int maxn=100+10, maxm=200+10;
struct data
{
	int u, b, k, t;
	bool operator < (const data &rhs) const {return t > rhs.t;}
};
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxm], v[maxm], t[maxm], w[maxm], nxt[maxm];
	void init(int _n) {ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _t, int _w) 
	{
		u[edn]=_u; v[edn]=_v; t[edn]=_t; w[edn]=_w;
		nxt[edn] = last[_u];
		last[_u] = edn++;
	}
};

int N, M, B, K, R, T; 
int dist[maxn][7][7][205];
bool inq[maxn][7][7][205];
Graph G;
int cost[7][maxn];

int SPFA();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int Tc;
	scanf("%d", &Tc);
	for(int ck=1; ck<=Tc; ck++)
	{
		scanf("%d%d%d%d%d%d", &N, &M, &B, &K, &R, &T);
		G.init(N);
		for(int i=0; i<K; i++) for(int j=1; j<=N; j++) scanf("%d", &cost[i][j]);
		for(int i=0,u,v,t,w; i<M; i++)
		{
			scanf("%d%d%d%d", &u, &v, &t, &w);
			G.adde(u,v,t,w);
		}
		int ans = SPFA();
		printf("Case #%d: ", ck);
		if(ans>=0) printf("%d\n", ans);
		else puts("Forever Alone");
	}
	return 0;
}

bool update(int &now, int val)
{
	if(val<0) return 0;
	if(val > now) {now=val; return 1;}
	return 0;
}
int SPFA()
{
	CLR(inq); MST(dist,-1);
	priority_queue<data> que;
	que.push({1,0,0,0});
	dist[1][0][0][0] = R;
	inq[1][0][0][0] = 1;
	
	while(que.size())
	{
		int u = que.top().u;
		int b = que.top().b;
		int k = que.top().k;
		int t = que.top().t;
		que.pop();
		inq[u][b][k][t] = 0;
//		printf("u:%d b:%d k:%d t:%d res:%d\n", u, b, k, t, dist[u][b][k][t]);
		if(u==N) continue;
		
		if(t<T && u!=1 && u!=N)
		{
			if(b<B && update(dist[u][b+1][(k+1)%K][t+1], dist[u][b][k][t] - cost[(k+1)%K][u]))
				if(!inq[u][b+1][(k+1)%K][t+1]) que.push({u, b+1, (k+1)%K, t+1}), inq[u][b+1][(k+1)%K][t+1] = 1;
				
			if(b>0 && update(dist[u][b-1][(k+1)%K][t+1], dist[u][b][k][t] + cost[(k+1)%K][u]))
				if(!inq[u][b-1][(k+1)%K][t+1]) que.push({u, b-1, (k+1)%K, t+1}), inq[u][b-1][(k+1)%K][t+1] = 1;
				
			if(update(dist[u][b][(k+1)%K][t+1], dist[u][b][k][t]))
				if(!inq[u][b][(k+1)%K][t+1]) que.push({u, b, (k+1)%K, t+1}), inq[u][b][(k+1)%K][t+1] = 1;
		}

		for(int e=G.last[u],v,nt,nw; ~e; e=G.nxt[e])
		{
			v = G.v[e]; nt = G.t[e]; nw = G.w[e];
			if((v==N || v==1) && k) continue;
			if(dist[u][b][k][t] - nw < 0 || t+nt>T) continue;
			if(v!=1 && v!=N && b<B && update(dist[v][b+1][k][t+nt], dist[u][b][k][t] - cost[k][v] - nw))
				if(!inq[v][b+1][k][t+nt]) que.push({v, b+1, k, t+nt}), inq[v][b+1][k][t+nt] = 1;
			if(v!=1 && v!=N && b>0 && update(dist[v][b-1][k][t+nt], dist[u][b][k][t] + cost[k][v] - nw))
				if(!inq[v][b-1][k][t+nt]) que.push({v, b-1, k, t+nt}), inq[v][b-1][k][t+nt] = 1;
			if(update(dist[v][b][k][t+nt], dist[u][b][k][t] - nw))
				if(!inq[v][b][k][t+nt]) que.push({v, b, k, t+nt}), inq[v][b][k][t+nt] = 1;
		}
	}
	
	int res=-1;
	for(int j=0; j<=T; j++) update(res, dist[N][0][0][j]);
	return res;
} 
