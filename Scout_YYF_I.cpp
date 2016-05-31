/*
PKU - 3744
一条路上有 N个地雷，刚开始在 1位置，
每次有 P的概率向前走一步，1-P的概率向前走两步
问不踩到任何一个地雷的概率

由于地雷的位置很大，所以用矩阵快速幂加速DP
可以使用两个矩阵，一个无雷向前递推一格，一个有雷向前递推一格
然后注意特判一下起始点有雷的情况
*/
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
#define Sqr(a) ((a)*(a))

const DBL eps=1e-7;
struct Matrix
{
	DBL n[2][2];
	Matrix(){CLR(n);}
	void E(){CLR(n);for(int i=0; i<2; i++) n[i][i]=1.0;}
	Matrix operator * (const Matrix &v) const
	{
		Matrix tem;
		for(int i=0; i<2; i++) for(int j=0; j<2; j++) for(int k=0; k<2; k++)
			tem.n[i][j]+=n[i][k]*v.n[k][j];
		return tem;
	}
};
int N;
DBL P;
int inpt[15];

Matrix MPow(Matrix,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	Matrix norm,zero;
	zero.n[1][0]=1.0;
	while(~scanf("%d%lf", &N, &P))
	{
		CLR(inpt);
		for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
		sort(inpt+1, inpt+1+N);
		N=unique(inpt+1,inpt+1+N)-(inpt+1);
		if(inpt[1]==1){puts("0.0000000"); continue;}
		
		inpt[0]=1;
		norm=zero;
		norm.n[0][0]=P; norm.n[0][1]=(1-P);
		
		Matrix ans;
		ans.E();
		
		for(int i=1; i<=N; i++)
		{
			int dist=inpt[i]-inpt[i-1];
			ans=MPow(norm,dist-1)*ans;
			ans=zero*ans;
		}
		ans=norm*ans;
		printf("%.7f\n", ans.n[0][0]);
	}
	return 0;
}

Matrix MPow(Matrix mat, int tim)
{
	Matrix res;
	res.E();
	while(tim>0)
	{
		if(tim&1) res=mat*res;
		mat=mat*mat;
		tim>>=1;
	}
	return res;
}


