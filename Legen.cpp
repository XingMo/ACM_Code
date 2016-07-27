/*
Codeforces - 697F
构造一个长度为 l的串，其中每包含一个第 i个单词，能获得 a_i的价值
单词可重复，也可相互覆盖，问最大价值是多少

一看就是AC自动机，但是 l特别大，有 1e14，所以要用矩阵快速幂
但是这个dp过程是取max的，所以矩阵和一般的都不一样
由于运算符的抽象性，
所以可以把矩阵乘法中的整数的乘法，即加权的方式，视作加法
把整数的加法，即各个子状态转移的方式，视作取 max
然后相应的，原来的单位矩阵，对角线上是 1,其他是 0
1是乘法的幺元，0是乘法的零元，加法的幺元
1改成 0 ，0改成负无穷
0是加法的幺元，负无穷是加法的零元，取 max的幺元
然后用这样的定义重载矩阵乘法，构造矩阵，进行矩阵快速幂即可
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

const int maxn=210;
const LL INF=0x3f3f3f3f3f3f3f3f;
struct Matrix
{
	LL n[maxn][maxn], siz;
	Matrix(int _siz=maxn){MST(n,-1); siz=_siz;}
	void E(){MST(n,-1); for(int i=0; i<siz; i++) n[i][i]=0;}
	Matrix operator * (const Matrix &v) const
	{
		Matrix tem(siz);
		for(int i=0; i<siz; i++) for(int j=0; j<siz; j++) for(int k=0; k<siz; k++)
			if(~n[i][k] && ~v.n[k][j]) tem.n[i][j] = max(tem.n[i][j], n[i][k]+v.n[k][j]);
		return tem;
	}
};

Matrix Pow(Matrix x, LL n)
{
	Matrix res;
	res.E();
	while(n)
	{
		if(n&1) res=x*res;
		x=x*x;
		n>>=1;
	}
	return res;
}

struct AC_Auto
{
	const static int nsiz=26;
	struct node
	{
		char chr;
		int fail, nxt[nsiz];
		LL val;
	} trie[maxn];
	int siz;
	int chnum(char a){return a-'a';}
	void init(){siz=0; CLR(trie);}
	void addstr(char*,int);
	void construct();
	LL solve(LL);
};


int N;
LL L;
int A[maxn];
char patn[maxn];
AC_Auto ac;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif

	ac.init();	
	scanf("%d%lld", &N, &L);
	for(int i=0; i<N; i++) scanf("%d", &A[i]);
	for(int i=0; i<N; i++)
	{
		scanf(" %s", patn);
		ac.addstr(patn,A[i]);
	}
	ac.construct();
	printf("%lld\n", ac.solve(L));
	return 0;
}

LL AC_Auto::solve(LL len)
{
	Matrix res(siz+1);
	for(int np=0; np<=siz; np++)
	{
		for(int i=0; i<nsiz; i++)
		{
			int nxp=trie[np].nxt[i];
			if(nxp) res.n[nxp][np] = max(res.n[nxp][np], (LL)trie[nxp].val);
		}
	}
	res = Pow(res,len);
	LL ans=0;
	for(int i=1; i<=siz; i++) ans=max(ans, res.n[i][0]);
	return ans;
}

void AC_Auto::addstr(char str[], int val)
{
	int np=0, len=strlen(str);
	for(int i=0; i<len; i++)
	{
		int chn=chnum(str[i]);
		if(trie[np].nxt[chn]) np=trie[np].nxt[chn];
		else
		{
			trie[np].nxt[chn]=++siz;
			np=siz;
			trie[np].chr=str[i];
		}
		if(i==len-1) trie[np].val+=val;
	}
}

void AC_Auto::construct()
{
	queue<int> que;
	for(int i=0; i<nsiz; i++)
	{
		int np=trie[0].nxt[i];
		if(np) que.push(np);
	}
	while(que.size())
	{
		int np=que.front(); que.pop();
		for(int i=0; i<nsiz; i++)
		{
			int nxp=trie[np].nxt[i];
			int fap=trie[np].fail;
			if(!nxp) trie[np].nxt[i]=trie[fap].nxt[i];
			else
			{
				que.push(nxp);
				trie[nxp].fail = trie[fap].nxt[i];
				fap = trie[nxp].fail;
				trie[nxp].val += trie[fap].val;
			}
		}
	}
}
