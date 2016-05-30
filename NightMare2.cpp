#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)

const int maxn=1e4+10, maxm=5e4+10;
struct Edge{int u,v,w,t,nxt;};
int N,M,K;

int edn, last[maxn];
Edge edge[2*maxm];

bool inq[maxn];
int dist[maxn];

void adde(int,int,int,int);
bool judg(int);

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
		edn=0; MST(last,-1);
		
		scanf("%d%d%d", &N, &M, &K);
		for(int i=0; i<M; i++)
		{
			int u,v,w,t;
			scanf("%d%d%d%d", &u, &v, &w, &t);
			adde(u,v,w,t);
			adde(v,u,w,t);
		}
		int l=0, r=2e9+10;
		while(l<r)
		{
			int mid=(l+r+1)>>1;
			if(judg(mid)) l=mid;
			else r=mid-1;
		}
		if(judg(l)) printf("%d\n", l);
		else puts("Poor RunningPhoton!");
	}
	return 0;
}

void adde(int u, int v, int w, int t)
{
	edge[edn].u = u;
	edge[edn].v = v;
	edge[edn].w = w;
	edge[edn].t = t;
	edge[edn].nxt = last[u];
	last[u] = edn++;
}

bool judg(int W)
{
	queue<int> que;
	MST(dist,0x3f); CLR(inq);
	inq[1]=1;
	dist[1]=0;
	que.push(1);
	
	while(que.size())
	{
		int u=que.front(); que.pop();
		for(int e=last[u]; ~e; e=edge[e].nxt)
		{
			if(edge[e].w < W) continue;
			int v=edge[e].v;
			int t=edge[e].t;
//			printf("%d->%d\n", u, v);
			if(dist[v] > dist[u] + t)
			{
				dist[v] = dist[u] + t;
				if(!inq[v])
				{
					que.push(v);
					inq[v] = 1;
				}
			}
		}
		inq[u]=0;
	}
	
//	printf("%d\n", W);
//	printf("%d\n", dist[N]<=K);
	
	if(dist[N]<=K) return 1;
	return 0;
}
