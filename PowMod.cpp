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
	
//	LL nt=clock();
	prime_init();
//	cout << "time = " << (DBL)(clock()-nt)/CLOCKS_PER_SEC << endl;

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
//	for(int i=0; i<maxn; i++) phi[i]=i;
//	for(int i=2; i<maxn; i++) if(!nprim[i])
//	{
//		phi[i]=i-1;
//		for(LL j=i*2; j<maxn; j+=i)
//		{
//			nprim[j]=1;
//			phi[j]=phi[j]/i*(i-1);
//		}
//		prime[pcnt++]=i;
//	}
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

