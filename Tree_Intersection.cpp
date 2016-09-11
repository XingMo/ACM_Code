/*
CSU - 1811 （湖南省赛16）
给定一棵树，每个节点都有一个颜色
问割掉任意一条边，生成的两个子树中颜色集合的交集大小

问题可以转化为任意一棵子树中，
这个子树中的颜色数量和只在这个子树中出现的颜色的数量
用总的颜色数量减去独有颜色数量即为这棵子树的答案

从 lcy大爷那里学到了机智的启发式合并的做法
对每个点维护一个 map
来记录这个点为根的子树中颜色的及其数量
然后dfs一遍，对每个节点启发式地将其儿子的map合并到父亲上
合并的时候，如果发现一个颜色出现次数用完了
说明它只在这个子树中出现，所以 res++
最后一个节点 u连向父亲边的答案即为 map[u].size()-res
注意儿子中的 res要累加到父亲上，
并且统计的时候要记一个 vis，免得算重了

由于采用了启发式合并，所以总的时间复杂度只有 O(nlog^2(n))
由于每次都最多只有一个 map，所以总的空间复杂度是 O(n)
虽然还有时间 O(nlogn)的做法，但我觉得能过就行
况且启发式合并编码复杂度极低，并且具有很好的推广性
从某些角度甚至优于 O(nlogn)的做法
*/
//#pragma comment(linker, "/STACK:102400000,102400000")
//#include <cstdio>
//#include <iostream>
//#include <cstdlib>
//#include <cstring>
//#include <algorithm>
//#include <cmath>
//#include <cctype>
//#include <map>
//#include <set>
//#include <queue>
//#include <bitset>
//#include <string>
//#include <complex>
//using namespace std;
//typedef pair<int,int> Pii;
//typedef long long LL;
//typedef unsigned long long ULL;
//typedef double DBL;
//typedef long double LDBL;
//#define MST(a,b) memset(a,b,sizeof(a))
//#define CLR(a) MST(a,0)
//#define SQR(a) ((a)*(a))
//#define PCUT puts("\n----------")

//const int maxn=1e5+10;
//struct Graph
//{
//	int ndn,edn,last[maxn];
//	int u[2*maxn], v[2*maxn], nxt[2*maxn];
//	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
//	void adde(int _u, int _v)
//	{
//		u[edn]=_u; v[edn]=_v;
//		nxt[edn]=last[_u];
//		last[_u]=edn++;
//	}
//};

//int N;
//int col[maxn], cnt[maxn], id[maxn], ans[maxn], vis[maxn];
//map<int,int> have[maxn];
//Graph G;

//int dfs(int,int);

//int main()
//{
//	#ifdef LOCAL
//	freopen("in.txt", "r", stdin);
////	freopen("out.txt", "w", stdout);
//	#endif
//	
//	while(~scanf("%d", &N))
//	{
//		G.init(N); CLR(cnt); CLR(vis);
//		for(int i=1; i<=N; i++) scanf("%d", &col[i]), cnt[col[i]]++;
//		for(int i=0,u,v; i<N-1; i++)
//		{
//			scanf("%d%d", &u, &v);
//			G.adde(u,v); G.adde(v,u);
//		}
//		id[1]=-1;
//		dfs(1,0);
//		for(int i=0; i<N-1; i++) printf("%d\n", ans[i]);
//	}
//	return 0;
//}

//int dfs(int u, int f)
//{
//	int res=0;
//	have[u].clear();
//	for(int e=G.last[u],v; ~e; e=G.nxt[e]) if((v=G.v[e])!=f)
//	{
//		id[v] = e>>1;
//		res += dfs(v,u);
//		if(have[u].size()<have[v].size()) swap(have[u], have[v]);
//		for(auto &pr:have[v])
//		{
//			have[u][pr.first] += pr.second;
//			if(have[u][pr.first] == cnt[pr.first] && !vis[pr.first])
//			{
//				res++;
//				vis[pr.first] = 1;
//			}
//		}
//		have[v].clear();
//	}
//	have[u][col[u]] ++;
//	if(have[u][col[u]] == cnt[col[u]] && !vis[col[u]])
//	{
//		res++;
//		vis[col[u]] = 1;
//	}
//	if(~id[u]) ans[id[u]] = have[u].size() - res;
//	return res;
//}

/*
CSU - 1811 （湖南省赛16）
给定一棵树，每个节点都有一个颜色
问割掉任意一条边，生成的两个子树中颜色集合的交集大小

这个是 dfs序处理子树 + 离线询问 + bit维护的解法
首先问题转化为求解一个子树中有多少种颜色以及独有颜色的数量
用总的颜色数量减去独有颜色数量即为这棵子树的答案
先做一遍 dfs，再按 dfs序重新组建颜色序列
这样对子树的询问，就变成了对序列上区间的询问
某个区间内有多少种颜色和独有颜色数量

然后离线所有询问，按区间右端点排序，然后从 1到 N地扫描这个区间
首先区间内颜色数量已经是很套路的做法了
只要预处理出第 i个颜色上一次出现的位置 pre[i]，
然后扫到 i的时候，在 [ pre[i]+1, i] 上都加 1，这样保证不会重复统计
其次区间内独有颜色计数，需要预处理出两个量
某个颜色第一次出现的位置 fir[i]，以及最后出现的位置 las[i]
当扫到的颜色处于其最后出现的位置，那么区间左端点在 fir[i]及之前时
这个颜色都会成为独有的颜色
所以只要在 [1,fir[i]-1] 上都减 1即可
这个区间操作，单点查询用树状数组维护即可
总的时间复杂度是 O(nlogn)，空间复杂度 O(n)
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
	int ndn, edn, last[maxn];
	int u[2*maxn], v[2*maxn], nxt[2*maxn];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v)
	{
		u[edn]=_u; v[edn]=_v;
		nxt[edn]=last[_u];
		last[_u]=edn++;
	}
};

struct Query
{
	int l,r,id;
	bool operator < (const Query &rhs) const {return r < rhs.r;}
};

struct BIT
{
	int bit[maxn], siz;
	void init(int _n){siz=_n; CLR(bit);}
	void add(int p, int x){for(; p<=siz; p+=p&-p) bit[p]+=x;}
	int sum(int p){int res=0; for(; p>0; p-=p&-p) res+=bit[p]; return res;}
};

int N;
int col[maxn], fir[maxn], las[maxn], pre[maxn], ans[maxn], id[maxn];
int dfst, dfsn[maxn], que[maxn];
vector<Query> Q;
BIT bit;
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
		MST(fir,-1); MST(las,-1); CLR(pre);
		G.init(N);
		for(int i=1; i<=N; i++) scanf("%d", &col[i]);
		for(int i=0,u,v; i<N-1; i++)
		{
			scanf("%d%d", &u, &v);
			G.adde(u,v); G.adde(v,u);
		}
		
		Q.clear();
		dfst=0; CLR(dfsn);
		dfs(1,0);
		for(int i=1; i<=N; i++)
		{
			las[que[i]] = i;
			if(fir[que[i]]==-1) fir[que[i]] = i;
		}
		
		bit.init(N);
		int np=0;
		for(int i=0; i<(int)Q.size(); i++)
		{
			while(np<Q[i].r)
			{
				np++;
				bit.add(pre[que[np]]+1, 1);
				bit.add(np+1, -1);
				pre[que[np]] = np;
				if(las[que[np]] == np)
				{
					bit.add(1, -1);
					bit.add(fir[que[np]]+1, 1);
				}
			}
			ans[Q[i].id] = bit.sum(Q[i].l);
		}
		
		for(int i=0; i<N-1; i++) printf("%d\n", ans[i]);
	}
	return 0;
}

void dfs(int u, int f)
{
	dfsn[u] = ++dfst;
	que[dfst] = col[u];
	for(int e=G.last[u], v; ~e; e=G.nxt[e]) if((v=G.v[e])!=f)
	{
		id[v] = e>>1;
		dfs(v,u);
	}
	if(f) Q.push_back({dfsn[u], dfst, id[u]});
}
