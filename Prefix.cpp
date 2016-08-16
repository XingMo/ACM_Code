/*
HDU - 5790
给定 N个字符串，问区间 [L,R]的字符串中
共有多少个不同的前缀
其中所有字符串的长度和不超过 1e5
并且此题强制在线

由于所有字符串的长度和不超过 1e5
所以所有可能的前缀最多 1e5
给所有前缀hash一下，然后问题就转化为了
在某个区间 [l,r]上，有多少个不同的数
即 SPOJ - D-query
在线的话用主席树搞一搞即可
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
const ULL seed=1e9+7;
struct Discrete
{
	ULL ais[maxn], siz;
	void init(){sort(ais, ais+siz); siz = unique(ais, ais+siz)-ais;}
	void add(ULL x){ais[siz++]=x;}
	int id(ULL x){return lower_bound(ais, ais+siz, x) - ais + 1;} 
};
struct PSegmentTree
{
	struct node
	{
		int ls, rs, sum;
	} segt[maxn*40];
	int siz,time,len,root[2*maxn];
	void init(int _n){siz=0; time=0; len=_n;}
	int update(int,int,int=-1,int=-1,int=-1);
	int query(int,int,int,int,int);
	void maintain(int);
};
char buff[maxn];
int N, Q, sp[2][maxn], last[maxn], qt[maxn];
int ht_siz;
ULL ht[maxn];
Discrete D;
PSegmentTree pstree;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		ht_siz=0; D.siz=0;
		CLR(sp); CLR(last); CLR(qt);
		for(int i=1, len; i<=N; i++)
		{
			scanf("%s", buff);
			len=strlen(buff);
			ULL now=0;
			sp[0][i] = ht_siz+1;
			for(int j=0; j<len; j++)
			{
				now = now*seed+buff[j];
				ht[++ht_siz] = now;
				D.add(now);
			}
			sp[1][i] = ht_siz;
		}
		D.init();
		pstree.init(ht_siz);
		
		int np=1;
		for(int i=1; i<=ht_siz; i++)
		{
			int idx = D.id(ht[i]);
			if(last[idx]) pstree.update(last[idx], -1);
			pstree.update(i, 1);
			last[idx] = i;
			if( i == sp[1][np]) qt[np++] = pstree.root[pstree.time];
		}
		
		int ans=0;
		scanf("%d", &Q);
		for(int i=0, L, R; i<Q; i++)
		{
			scanf("%d%d", &L, &R);
			int l = min((ans+L)%N, (ans+R)%N) + 1;
			int r = max((ans+L)%N, (ans+R)%N) + 1;
			ans = pstree.query(sp[0][l], sp[1][r], qt[r], 1, ht_siz);
			printf("%d\n", ans);
		}
	}
	return 0;
}

int PSegmentTree::update(int p, int v, int np, int nl, int nr)
{
	int tp=++siz;
	if(np==-1)
	{
		np=root[time], nl=1, nr=len;
		root[++time] = tp;
	}
	node &now=segt[np], &to=segt[tp];
	to = now;
	if(nl==nr) {to.sum += v; return tp;}
	int mid=(nl+nr)>>1;
	if(p<=mid) to.ls = update( p, v, now.ls, nl, mid);
	else to.rs = update( p, v, now.rs, mid+1, nr);
	maintain(tp);
	return tp;
}

int PSegmentTree::query(int ql, int qr, int np, int nl, int nr)
{
	node &now=segt[np];
	if(ql<=nl && nr<=qr) return now.sum;
	int mid=(nl+nr)>>1, res=0;
	if(ql<=mid) res += query(ql, qr, now.ls, nl, mid);
	if(qr>mid)  res += query(ql, qr, now.rs, mid+1, nr);
	return res;
}

void PSegmentTree::maintain(int np)
{
	segt[np].sum = segt[ segt[np].ls ].sum + segt[ segt[np].rs ].sum;
}


