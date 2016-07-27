/*
Codeforces - 697C
有三个倒扣着的碗，刚开始钥匙放在中间
之后每次将中间的碗和其他碗交换位置，
交换选择的碗是等概率的
问最后钥匙在中间的概率是多少

很容易就写出一个dp式子
然后将转移过程写成矩阵的形式
然后求矩阵的特征值和对应的特征向量
再把初始状态用特征向量表达，最后就能得出概率
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

const int maxn=1e5+10;
const LL MOD0=1e9+6, MOD1=1e9+7;
int N;
LL A[maxn];

LL Pow(LL,LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	LL tp=1, r;
	scanf("%d", &N);
	for(int i=0; i<N; i++)
	{
		LL x;
		cin >> x;
		tp=tp*(x%MOD0)%MOD0;
	}
	if(tp&1) r=-1;
	else r=1;
	tp=((tp-1)%MOD0+MOD0)%MOD0;
	LL q=Pow(2,tp,MOD1), p=q+r;
	p=p*Pow(3,MOD1-2,MOD1)%MOD1;
	cout << p << "/" << q << endl; 
	return 0;
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=x*res%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}

