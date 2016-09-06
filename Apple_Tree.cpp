/*
Codeforces - 348B
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

LL GCD(LL a, LL b) {return b?GCD(b,a%b):a;}
LL LCM(LL a, LL b) {if(!GCD(a,b)) return 0; else return a/GCD(a,b)*b;}
const int maxn=1e5+10, maxm=2*maxn;
struct Graph
{
	int ndn,edn,last[maxn];
	int u[maxm], v[maxm], nxt[maxm];
	void init(int _n) {ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u,int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

int N;
LL res, A[maxn], K[maxn];
Graph G;

void dfs(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		G.init(N);
		res = 0;
		for(int i=1; i<=N; i++) scanf("%lld", &A[i]), K[i]=A[i]?1:0;
		for(int i=1,u,v; i<N; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		dfs(1,0);
		cout << res << "\n";
	}
	return 0;
}

void dfs(int u,int f)
{
	if(K[u]) return;
	K[u] = 1;
	int son=0;
	vector<LL> as;
	for(int e=G.last[u],v; ~e; e=G.nxt[e]) if((v=G.v[e])!=f)
	{
		dfs(v,u);
		son++;
		A[u] += A[v];
		K[u] = LCM(K[u], K[v]);
		as.push_back(A[v]);
	}
	LL rate=0x3f3f3f3f3f3f3f3f;
	if(!K[u]) rate = 0;
	else for(int i=0; i<(int)as.size(); i++) rate = min(rate, as[i]/K[u]);
	rate *= K[u];
	if(rate==0) for(int i=0; i<(int)as.size(); i++) res += as[i], A[u] -= as[i];
	else for(int i=0; i<(int)as.size(); i++) res += as[i]-rate, A[u] -= as[i]-rate;
	K[u] *= son;
}
