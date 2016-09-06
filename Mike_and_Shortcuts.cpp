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
	int ndn, edn, last[maxn];
	int u[3*maxn], v[3*maxn], nxt[3*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

int N, dist[maxn];
bool inq[maxn];
Graph G;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		G.init(N);
		for(int i=1,x; i<=N; i++)
		{
			if(i<N) {G.adde(i, i+1); G.adde(i+1, i);}
			scanf("%d", &x);
			G.adde(i,x);
		}
		MST(dist,0x3f);
		CLR(inq);
		queue<int> que;
		que.push(1);
		inq[1]=1;
		dist[1]=0;
		while(que.size())
		{
			int u=que.front(); que.pop();
			for(int e=G.last[u],v; ~e; e=G.nxt[e])
			{
				v=G.v[e];
				if(dist[v] > dist[u] + 1)
				{
					dist[v] = dist[u] +1;
					if(!inq[v])
					{
						inq[v]=1;
						que.push(v);
					}
				}
			}
			inq[u]=0;
		}
		for(int i=1; i<=N; i++) printf("%d ", dist[i]);
		puts("");
	}
	return 0;
}

