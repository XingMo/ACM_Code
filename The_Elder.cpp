/*
HDU - 5956
树上的一个斜率DP裸题

用斜率DP加可持久化单调队列强行搞。
可持久化单调队列就是弹的时候用二分在log时间内确定弹到什么位置
然后加入的时候一次只修改一个，只要备份一下原来的一个值即可
这题注意开一下longlong
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

const int maxn=1e5+10, maxe=2*maxn;
struct Graph
{
	int ndn, edn, last[maxn];
	int u[maxe], v[maxe], w[maxe], nxt[maxe];
	void init(int _n){ndn=_n; edn=0; MST(last,-1);}
	void adde(int _u, int _v, int _w)
	{
		u[edn]=_u; v[edn]=_v; w[edn]=_w;
		nxt[edn]=last[_u];
		last[_u] = edn++;
	}
};

Graph G;
int N,P,que[maxn];
LL dp[maxn], S[maxn];

LL Up(int,int);
LL Down(int,int);
void dfs(int,int,int,int);

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
		scanf("%d%d", &N, &P);
		G.init(N);
		for(int i=1,u,v,w; i<N; i++)
		{
			scanf("%d%d%d", &u, &v, &w);
			G.adde(u,v,w); G.adde(v,u,w);
		}
		S[1] = 0; dp[1] = -P;
		que[0] = 1;
		for(int e=G.last[1]; ~e; e=G.nxt[e])
		{
			S[G.v[e]] = G.w[e];
			dfs(G.v[e],1,0,1);
		}
		LL ans = 0;
		for(int i=2; i<=N; i++) ans = max(ans, dp[i]);
		printf("%lld\n", ans);
	}
	return 0;
}

void dfs(int u, int f, int head, int tail)
{
	int l=head, r=tail-2;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(Up(que[mid+1], que[mid]) <= S[u]*Down(que[mid+1], que[mid])) l=mid+1;
		else r=mid;
	}
	if(l+1<tail && Up(que[l+1], que[l]) <= S[u]*Down(que[l+1], que[l])) l++;
	head = l;
	
	dp[u] = dp[que[head]] + SQR(S[u]-S[que[head]]) + P;
	LL old, oldp;
	
	l = head+2, r = tail;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(Up(que[mid-1], que[mid-2])*Down(u, que[mid-1]) >= Up(u, que[mid-1])*Down(que[mid-1], que[mid-2])) r = mid;
		else l=mid+1;
	}
	if(head+1<l && Up(que[l-1], que[l-2])*Down(u, que[l-1]) >= Up(u, que[l-1])*Down(que[l-1], que[l-2])) l--;
	tail = l;
	
	old = que[tail], oldp = tail;
	que[tail++] = u;
	
	for(int e=G.last[u],v; ~e; e=G.nxt[e]) if((v=G.v[e]) != f)
	{
		S[v] = S[u] + G.w[e];
		dfs(v, u, head, tail);
	}
	que[oldp] = old;
}

LL Up(int j, int k){return (dp[j] + SQR(S[j]) ) - (dp[k] + SQR(S[k]));}
LL Down(int j, int k){return 2*(S[j] - S[k]);}
