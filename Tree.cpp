/*
POJ - 1741
给定一棵树，计算长度不超过 K的链的个数

树分治入门题，看着题解刷的
选定一个点，首先一条链要么在此点的子树上
要么这条链经过这个点
在子树上就可以划分为子问题，然后分治处理
经过这个点的链，可以把子树上的点到根的距离处理出来
然后对这些距离排个序，就能 O(n)统计

选点要选重心，重心的所有子树大小不超过 N/2
这样保证分治至少是 logn层的，不会发生退化
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

using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

#define PCUT puts("--------------------")

const int maxn=1e4+10;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], w[2*maxn], nxt[2*maxn];
	int del[maxn];
	void init(int _n){ ndn=_n; edn=0; MST(last,-1); CLR(del);}
	void adde(int _u, int _v, int _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};


int N,K;
Graph G;

int nsiz[maxn];
void solve(int,int&);
void get_size(int,int);
void get_centroid(int,int,int&,int&,int&);
void get_dist(int,int,int,vector<int>&);
int  get_ans(vector<int>&);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &K))
	{
		if(N==0 && K==0) break;
		G.init(N);
		for(int i=1; i<N; i++)
		{
			int u,v,w;
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		
		int ans=0;
		solve(1, ans);
		printf("%d\n", ans);
	}
	return 0;
}

vector<int> dist, temp;
void solve(int u, int &ans)
{
	int C=u,tmin,tot;
	get_size(u,0);
	tot=tmin=nsiz[u];
	if(nsiz[u]==1) return;
	get_centroid(u,0,C,tmin,tot);
	
//	PCUT;
//	printf("Entrance = %d\n", u);
//	printf("Centroid = %d\n", C);
//	printf("Nsiz = %d\n", nsiz[u]);
	
	dist.clear();
	dist.push_back(0);
	for(int e=G.last[C], v; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		if(G.del[v]) continue;
		temp.clear();
		get_dist(v,C,G.w[e],temp);
		ans -= get_ans(temp);
		dist.insert(dist.end(), temp.begin(), temp.end());
	}
	ans += get_ans(dist);
	G.del[C]=1;
	
//	printf("ans = %d\n", ans);
//	pause(1);
//	PCUT;
	for(int e=G.last[C]; ~e; e=G.nxt[e])
	{
		int v=G.v[e];
		if(G.del[v]) continue;
		solve(v,ans);
	}
}

void get_size(int u, int f)
{
	nsiz[u]=1;
	for(int e=G.last[u], v; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		if(v==f || G.del[v]) continue;
		get_size(v,u);
		nsiz[u] += nsiz[v];
	}
}

void get_centroid(int u,int f,int &C,int &tmin, int &tot)
{
	int tmax=0;
	for(int e=G.last[u], v; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		if(v==f || G.del[v]) continue;
		get_centroid(v,u,C,tmin,tot);
		tmax = max(tmax, nsiz[v]);
	}
	tmax = max(tmax, tot-nsiz[u]);
	if(tmax<tmin)
	{
		tmin=tmax;
		C=u;
	}
}

void get_dist(int u,int f,int dept,vector<int> &vec)
{
	vec.push_back(dept);
	for(int e=G.last[u], v; ~e; e=G.nxt[e])
	{
		v=G.v[e];
		if(v==f || G.del[v]) continue;
		get_dist(v, u, dept+G.w[e], vec);
	}
}

int get_ans(vector<int> &vec)
{
	int res=0;
	sort(vec.begin(), vec.end());
	int np=vec.size();
	for(int i=0; i<(int)vec.size(); i++)
	{
		while(np>0 && vec[np-1]+vec[i] > K ) np--;
		res += np;
		if(np>i) res-=1;
	}
	return res/2;
}
