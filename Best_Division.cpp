/*
HDU - 5845
给定一段数列，将其划分成最多的段
并且每段长度不超过 L且异或和不超过 X

有一个很显然的 O(N^2)的dp做法
dp[i]表示到 i为止最多能分成多少段
然后从前面最多 L个 dp值转移出来
但是对前面 L个 dp可以用 xor-trie维护一下
这样一来时间复杂度就是 O(Nlog(A))

每次将当前位置的前缀异或和插入trie，
并且在叶子节点维护一下当前位置的 dp值，其他节点维护出子树的 dp最大值
做到 i的时候，在 trie树上沿着异或等于 X的路径走
而小于 X的路径可以直接用已经维护好的最大值
长度超过 L的部分需要删掉，而 trie树不好直接删除，所以只需将 dp值标记成 -1即可
由于 dp肯定是递增的，所以后来的值肯定更优，
所以前缀异或和相同的只需要保存最后一个即可
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

const int maxn=1e5+10, MOD=1<<28, Len=28;
struct Trie
{
	struct node
	{
		int tmax, pos, nxt[2];
	} tr[maxn*28];
	int siz;
	void init(){siz=1; CLR(tr); tr[0].tmax=-1;}
	void addstr(int,int,int,int=0,int=27);
	int findstr(int,int,int=0,int=27);
	void delstr(int,int,int=0,int=27);
};

int N,X,L,P,Q,A[maxn],dp[maxn];
Trie trie;

int main()
{
	#ifdef LOCAL
	freopen("1002.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif

	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d%d%d%d%d", &N, &X, &L, &A[1], &P, &Q);
		for(int i=2; i<=N; i++) A[i] = ((LL)A[i-1]*P+Q)%MOD;
		for(int i=2; i<=N; i++) A[i] ^= A[i-1];

		trie.init(); trie.addstr(0,0,0);
		for(int i=1; i<=N; i++)
		{
			dp[i] = trie.findstr( A[i], X);
			if(~dp[i]) trie.addstr( i, A[i], ++dp[i]);
			if(i>=L && ~dp[i-L]) trie.delstr(i-L, A[i-L]);
		}
		if(~dp[N]) printf("%d\n", dp[N]);
		else puts("0");
	}
	return 0;
}

void Trie::addstr(int pos, int num, int tmax, int np, int npos)
{
	if(npos<0)
	{
		tr[np].pos = pos; tr[np].tmax = tmax;
		return;
	}
	int now = (num>>npos)&1, &nxt = tr[np].nxt[now];
	if(!nxt) nxt = siz++;
	addstr(pos,num,tmax,nxt,npos-1);
	if(np) tr[np].tmax = max(tr[np].tmax, tmax);
}

int Trie::findstr(int num, int lim, int np, int npos)
{
	if(npos<0) return tr[np].tmax;
	int now = (num>>npos)&1, lnow = (lim>>npos)&1, nxt, res=-1;
	if(nxt=tr[np].nxt[now])
	{
		if(0<lnow) res = max(res, tr[nxt].tmax);
		else res = max(res, findstr(num, lim, nxt, npos-1));
	}
	if(nxt=tr[np].nxt[now^1])
	{
		if(1==lnow) res = max(res, findstr(num, lim, nxt, npos-1));
	}
	return res;
}

void Trie::delstr(int pos, int num, int np, int npos)
{
	if(npos<0)
	{
		if(tr[np].pos == pos) tr[np].tmax = -1;
		return;
	}
	int now = (num>>npos)&1, nxt = tr[np].nxt[now];
	delstr(pos, num, nxt, npos-1);
	if(np) tr[np].tmax = max(tr[tr[np].nxt[now]].tmax, tr[tr[np].nxt[now^1]].tmax);
}
