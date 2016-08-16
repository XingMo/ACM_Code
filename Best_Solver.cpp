/*
HDU - 5451
y = (5+2*sqrt(6))^(1+2^x)
给定 x和 质数M，求 [y]%M

首先 x很大，肯定要快速幂一下
有一个向下取整，所以要把底数配成整数
设 A_n = (5+2*sqrt(6))^n + (5-2*sqrt(6))^n
可以发现，A_n为整数，(5-2*sqrt(6))^n < 1，
所以 A_n即为 (5+2*sqrt(6))^n向上取整，答案即为 A_n-1
用 A_n*(5+2*sqrt(6) + 5-2*sqrt(6))化一化，就能得到
A_{n+1} = 10A_n - A_{n-1}
然后就能用矩阵快速幂搞一搞了

但是实际上，1+2^x这个指数还是很大，所以要先降幂
但是底数是个无理数，所以不能用费马小定理降幂
所以要采取更为通用的方法，找循环节
简单记一下结论，就是如果特征值 λ=(a±√b)/c ， 
这个形式的根号下的那个 b ，只要用欧拉准则判断它是不是 mod p的二次剩余。
如果是，则循环节为 p−1 ，否则为 (p+1)(p−1)
知道了二次剩余相关的知识，现在平方根（无理数）模数也能搞了……
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

int MOD;
struct Matrix
{
	int n[2][2],siz;
	Matrix(int _n){siz=_n; CLR(n);}
	void E(){CLR(n);for(int i=0; i<siz; i++) n[i][i]=1;}
	Matrix operator * (const Matrix &v) const
	{
		Matrix tem(siz);
		for(int i=0; i<siz; i++) for(int j=0; j<siz; j++) for(int k=0; k<siz; k++)
			tem.n[i][j] = (tem.n[i][j] + n[i][k]*v.n[k][j]%MOD) %MOD;
		return tem;
	}
	Matrix operator ^ (LL n) const
	{
		Matrix tem(siz), x=*this;
		tem.E();
		while(n)
		{
			if(n&1) tem=tem*x;
			x=x*x;
			n>>=1;
		}
		return tem;
	}
};
int X,M;
LL Pow(LL,LL,LL);
int Legendre(LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	Matrix mat(2);
	mat.n[0][0]=10; mat.n[0][1]=-1;
	mat.n[1][0]=1;  mat.n[1][1]=0;
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &X, &M);
		MOD = M;
		int L = Legendre(6, M);
		LL ans, tp = L==1?(M-1):((LL)(M+1)*(M-1));
		LL N = (Pow(2,X,tp)+1)%tp;
		if(N==1) ans=10-1;
		else if(N==2) ans=98-1;
		else
		{
			N-=2;
			Matrix res = mat^(N);
			ans = ((LL)98*res.n[0][0]%MOD + (LL)10*res.n[0][1]%MOD - 1)%MOD;
		}
		printf("Case #%d: %d\n", ck, (int)((ans+MOD)%MOD));
		//+ MOD
	}
	return 0;
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=res*x%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}

int Legendre(LL x, LL p)
{
	int res = Pow(x, (p-1)>>1, p);
	if(res==p-1) res=-1;
	return res;
}
