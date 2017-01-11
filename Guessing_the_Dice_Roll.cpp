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

const DBL eps = 1e-13;
struct Matrix
{
	int siz;
	DBL n[110][110];
	Matrix(int _n){siz=_n; CLR(n);}
	void E(){CLR(n);for(int i=0; i<siz; i++) n[i][i] = 1;}
	Matrix operator * (const Matrix &rhs) const
	{
		Matrix tem(siz);
		for(int i=0; i<siz; i++) for(int k=0; k<siz; k++) if(n[i][k] > eps) for(int j=0; j<siz; j++)
			tem.n[i][j] += n[i][k] * rhs.n[k][j];
		return tem;
	}
};

struct AC_Auto
{
	struct node
	{
		int nxt[6],fail,val;
	} trie[110];
	int siz;
	void init(){siz=0; CLR(trie);}
	void addstr(int*,int,int);
	void build();
	void construct(Matrix&);
} ac;

int N,L;
Matrix Pow(Matrix,int);
DBL ans[15];

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
		scanf("%d%d", &N, &L);
		int buff[12];
		ac.init();
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<L; j++) scanf("%d", &buff[j]);
			ac.addstr(buff,L,i+1);
		}
		ac.build();
		Matrix mat(ac.siz+1);
		ac.construct(mat);
		mat = Pow(mat,1e9);
		for(int i=0; i<=ac.siz; i++) if(ac.trie[i].val)
			ans[ac.trie[i].val] = mat.n[i][0];
		for(int i=1; i<=N; i++) printf("%.6f%s", ans[i], i==N?"\n":" ");
	}
	return 0;
}

Matrix Pow(Matrix mat, int n)
{
	Matrix res(mat.siz);
	res.E();
	while(n)
	{
		if(n&1) res = res*mat;
		mat = mat*mat;
		n>>=1;
	}
	return res;
}

void AC_Auto::addstr(int str[], int L, int nval)
{
	int np = 0;
	for(int i=0; i<L; i++)
	{
		int ch = str[i]-1;
		if(trie[np].nxt[ch]) np = trie[np].nxt[ch];
		else
		{
			trie[np].nxt[ch] = ++siz;
			np = siz;
		}
		if(i==L-1) trie[np].val = nval;
	}
}

void AC_Auto::build()
{
	queue<int> que;
	for(int i=0; i<6; i++)
	{
		int pt = trie[0].nxt[i];
		if(pt) que.push(pt);
	}
	
	while(que.size())
	{
		int np=que.front(); que.pop();
		for(int i=0; i<6; i++)
		{
			int nxp = trie[np].nxt[i];
			int fap = trie[np].fail;
			if(!nxp)
			{
				trie[np].nxt[i] = trie[fap].nxt[i];
				continue;
			}
			que.push(nxp);
			trie[nxp].fail = trie[fap].nxt[i];
		}
	}
}

void AC_Auto::construct(Matrix &mat)
{
	for(int np=0; np<=siz; np++)
	{
		if(trie[np].val) mat.n[np][np] += 1;
		else
		{
			for(int i=0; i<6; i++)
			{
				int now = trie[np].nxt[i];
				mat.n[now][np] += 1.0/6;
			}
		}
	}
}
