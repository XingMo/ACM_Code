/*
Ural - 1132
求一个二次剩余方程

裸题裸题……
根据二次剩余的相关定义与解法
对于方程 x^2 = n (mod p)
如果mod p的剩余系中存在 a使得
w = a^2 - n不是mod p的二次剩余
那么 x = (a+sqrt(w))^((p+1)/2)是方程的一个解
方程的另一个解为 p-x

判断一个数是不是mod p的二次剩余，可以用欧拉判定准则
如果 n^((p-1)/2) = 1 (mod p)，那么 n是 mod p的二次剩余
如果 n^((p-1)/2) = -1 (mod p)，那么 n不是 mod p的二次剩余
前者可以用费马小定理证，后者可以用威尔逊定理证

由于二次剩余方程是针对 mod 一个奇素数的，所以要特判一下 p=2的情况
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
#include <ctime>
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

int A,N;

struct quad
{
	LL a,b,d;
	quad operator * (const quad &v) const
	{
		quad tem;
		tem.a = (a*v.a%N + b*v.b*d%N)%N;
		tem.b = (a*v.b%N + b*v.a%N)%N;
		tem.d = d;
		return tem;
	}
	quad operator ^ (LL n)
	{
		quad res, now=*this;
		res.a = 1, res.b=0;
		while(n)
		{
			if(n&1) res=now*res;
			now=now*now;
			n>>=1;
		}
		return res;
	}
};

LL Pow(LL,LL,LL);
int Legendre(LL,LL);
int quad_residue(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	srand(time(0));
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &A, &N);
		int a = quad_residue(A,N), b;
		if(a==-1) puts("No root");
		else
		{
			b = N-a;
			if(a>b) swap(a,b);
			if(a==b) printf("%d\n", a);
			else printf("%d %d\n", a, b);
		}
	}
	return 0;
}

int quad_residue(int n, int p)
{
	if(p==2) return 1;
	if(Legendre(n,p)==-1) return -1;
	LL a, w;
	while(1)
	{
		a = rand()%p;
		w = ( (a*a-n)%p + p )%p;
		if(Legendre(w,p)==-1) break;
	}
	quad res;
	res.a = a;
	res.b = 1;
	res.d = w;
	res = res^((LL)(p+1)>>1);
	return res.a;
}

int Legendre(LL a, LL p)
{
	LL res = Pow(a, (p-1)>>1, p);
	if(res==p-1) res=-1;
	return (int)res;
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
