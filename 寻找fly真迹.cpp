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

const int maxn=500+10, maxm=maxn*maxn;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[2*maxm],v[2*maxm],nxt[2*maxm];
	void init(int a){ndn=a; edn=0; MST(last,-1);}
	void adde(int tu,int tv)
	{
		u[edn]=tu; v[edn]=tv;
		nxt[edn]=last[tu];
		last[tu]=edn++;
	}
};
int N,M;
Graph G;
int deg[maxn];
int ban[maxn];
int bsiz[10];

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
		scanf("%d%d", &N, &M);
		G.init(N);
		CLR(deg); CLR(ban); CLR(bsiz);
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
			deg[u]++; deg[v]++;
		}
		for(int u=1; u<=N; u++) if(deg[u]==N-1) ban[u]=-1;
		int bcnt=0;
		for(int i=1; i<=N; i++)
		{
			if(ban[i]) continue;
			else
			{
				bcnt++;
				if(bcnt>2) break;
				int tot=0;
				queue<int> que;
				que.push(i);
				ban[i]=bcnt;
				while(que.size())
				{
					int u=que.front(); que.pop();
					tot++;
					for(int e=G.last[u]; ~e; e=G.nxt[e])
					{
						int v=G.v[e];
						if(!ban[v])
						{
							que.push(v);
							ban[v]=bcnt;
						}
						if(ban[v]==-1) deg[u]--;
					}
				}
				bsiz[bcnt]=tot;
			}
		}
		if(bcnt>2) puts("No");
		else
		{
//			for(int i=1; i<=N; i++) printf("%d ", ban[i]); puts("");
//			for(int i=1; i<=N; i++) if(~ban[i]) printf("%d ", deg[i]); puts("");
//			for(int i=1; i<=bcnt; i++) printf("%d ", bsiz[bcnt]); puts("");
			bool ok=1;
			for(int i=1; i<=N; i++)
			{
				if(ban[i]>0 && deg[i]!=bsiz[ban[i]]-1) {ok=0; break;}
			}
			if(ok) puts("Yes");
			else puts("No");
		}
	}
	return 0;
}

