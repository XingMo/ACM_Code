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
#include <cassert>
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

const DBL eps=1e-8, pi=acos(-1.0);
const int maxn=1000+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn*maxn], v[2*maxn*maxn], nxt[2*maxn*maxn];
	DBL w[2*maxn*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, DBL _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};
struct data
{
	int x,y,sid,id,tag;
	DBL ang;
	bool operator < (const data &v) const {return ang < v.ang;}
};

int N, K;
data P[maxn], L[maxn];
Graph G;
bool vis[maxn];

DBL dist[maxn];
bool done[maxn];
DBL dijkstra(int,int);

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
		scanf("%d%d", &N, &K);
		int tot=2*N+2, sta=2*N, end=2*N+1;
		G.init(tot);
		
		for(int i=0, u, v; i<N; i++)
		{
			u=i<<1, v=i<<1|1;
			scanf("%d %d %d %d", &P[u].x, &P[u].y, &P[v].x, &P[v].y);
			P[u].sid=i; P[u].id=u;
			P[v].sid=i; P[v].id=v;
			if(P[u].x==P[v].x) P[u].tag = P[v].tag = 1;
			else P[u].tag = P[v].tag = 0;
		}
		scanf("%d %d %d %d", &P[N<<1].x, &P[N<<1].y, &P[N<<1|1].x, &P[N<<1|1].y);
		P[N<<1].tag = P[N<<1|1].tag = -1;
		P[N<<1].id = N<<1; P[N<<1|1].id = N<<1|1;
		
		for(int i=0; i<tot; i++)
		{
			memcpy(L, P, sizeof(data)*tot);
			if(i!=0) swap(L[i], L[0]);
			for(int j=1; j<tot; j++) L[j].ang = atan2(L[j].y-L[0].y, L[j].x-L[0].x);
			sort(L+1, L+tot);
			int sum=0, u=L[0].id, v;
			for(int j=1; j<tot; j++)
			{
				v = L[j].id;
				G.adde(u, v, sqrt(SQR(L[0].x-L[j].x) + SQR(L[0].y-L[j].y)) + (DBL)K*sum);
				if(L[j].tag==-1) continue;
				if(L[j].tag==0 && L[j].y==L[0].y) continue;
				if(L[j].tag==1 && L[j].x==L[0].x) continue;
				if(!vis[L[j].sid]) sum++;
				else sum--;
//				if(sum<0)
//				{
//					printf("%d\n", ck);
//					exit(0);
//				}
				vis[L[j].sid] ^= 1;
//				printf("u:%d v:%d sum:%d tag:%d %d %d\n", u, v, sum, L[j].tag, L[j].y, L[0].y);
			}
		}
//		printf("%d %d\n", G.ndn, G.edn);
//		for(int e=0; e<G.edn; e++) printf("%d->%d %.2f\n", G.u[e], G.v[e], G.w[e]);
		DBL res = dijkstra(sta,end);
		printf("%.8f\n", res);
//		PCUT;
	}
	return 0;
}

struct mpair
{
	DBL d;
	int id;
	bool operator < (const mpair &v) const
	{
		return d > v.d;
	}
};

DBL dijkstra(int sta, int end)
{
	CLR(done);
	for(int i=0; i<=end; i++) dist[i]=1e11;
	priority_queue<mpair> pq;
	dist[sta] = 0;
	pq.push({0,sta});
	
	while(pq.size())
	{
		mpair now=pq.top(); pq.pop();
		int u=now.id;
		if(done[u]) continue;
		done[u] = 1;
		for(int e=G.last[u], v; ~e; e=G.nxt[e])
		{
			v=G.v[e];
			if(done[v]) continue;
			if(dist[u]+G.w[e] < dist[v])
			{
				dist[v] = dist[u] + G.w[e];
				pq.push({dist[v], v});
			}
		}
	}
	
	return dist[end];
}
