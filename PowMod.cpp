/*
HDU - 5728
求 K = \sum_{i=1}^m phi(i*n) mod 1000000007
其中 n是 square-free number
求 ans = K^K^K^K... mod p

先求 K
由于 phi是积性函数，所以对于 n的每个素因子可以提出来计算
\sum_{i=1}^m phi(i*n) = (p_k-1) * \sum_{i=1}^m phi(i*n/p_k) + \sum_{i=1}^{m/p_k} phi(i*n)
对于素因子 p_k，如果 i中不包含这个因子，提出来是 phi(p_k) = p_k-1
如果 i中包含这个因子，那么提出来就是 p_k，所以在后面加上多减的这一项
而 1到 m中共有 m/p_k个包含 p_k的 i，为 1*p_k、2*p_k...
他们除以 p_k后是 1、2、...m/p_k，所以后面 i是从 1到 m/p_k
设 K = sum(n, m) = (p_k-1)*sum(n/p_k, m) + sum(n, m/p_k)
递归计算即可，复杂度不会超过 O(logN)

再求 ans
利用欧拉定理降幂
a^x = a^{x%phi(p) + phi(p)} mod p
递归计算，phi很快就变成 1了，所以复杂度不会超过 O(logN)

另外在欧拉函数打表那块，由于 N有 1e7 ，最好用 O(N)的欧拉筛
不然容易 TLE （虽然我用埃氏筛没 TLE 
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
#define SQR(a) ((a)*(a))

const int maxn=1e7+10, MOD=1000000007;
int N,M,P;
bool nprim[maxn];
int phi[maxn];
int phi_sum[maxn];
int prime[maxn], pcnt;

void prime_init();
LL SUM(int,int,vector<int>&);
LL PowMod(LL,LL);
LL Pow(LL,LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	prime_init();

	while(~scanf("%d%d%d", &N, &M, &P))
	{
		vector<int> fact;
		int tem=N;
		for(int i=0; i<pcnt && prime[i]<=tem; i++) if(tem%prime[i]==0)
		{
			tem/=prime[i];
			fact.push_back(prime[i]);
		}
		LL K = SUM(N,M,fact);
		printf("%lld\n", PowMod(K,(LL)P));
	}
	return 0;
}

LL PowMod(LL k, LL p)
{
	if(p==1) return 0;
	LL tp=PowMod(k,phi[p]);
	LL res = Pow(k,tp+phi[p],p);
	return res;
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

LL SUM(int n, int m, vector<int>& fact)
{
	if(n==1) return phi_sum[m];
	if(m==1) return phi[n];
	if(m<1)  return 0;
	for(int i=0; i<(int)fact.size(); i++) if(n%fact[i]==0)
		return (SUM( n, m/fact[i], fact) + (LL)(fact[i]-1)*SUM( n/fact[i], m, fact)%MOD)%MOD;
	return 0;
}

void prime_init()
{
	phi[1]=1;
	for(int i=2;i<maxn;i++)
	{
        if(!nprim[i]) {phi[i]=i-1; prime[pcnt++]=i;}
        for(int j=0;j<pcnt;j++)
        {
            if(i*prime[j]>=maxn)break;
            nprim[i*prime[j]]=true;
            if(i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];break;
            }
            else
            {
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
            }
        }
    }
	for(int i=1; i<maxn; i++) phi_sum[i] = (phi_sum[i-1]+phi[i])%MOD;
	
}

