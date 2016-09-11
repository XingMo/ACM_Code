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
typedef long long ll;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("\n----------")

const int maxn=1e5+10,maxl=1e9+10,MOD=1e9+7;
int N;
bool sieve[maxn];
vector<int> prime;

LL Pow(LL,LL,LL);
LL GetP(LL);

struct Matrix{
	ll mp[2][2];
	Matrix operator * (const Matrix& rhs) const{
		Matrix ret(0);
		memset(ret.mp, 0, sizeof ret.mp);
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k){
					ret.mp[i][j] += mp[i][k] * rhs.mp[k][j];
					ret.mp[i][j] %= MOD;
				}
		return ret;
	}
	Matrix(int i){
		memset(mp, 0, sizeof mp);
		if (i) mp[1][0] = mp[0][1] = mp[1][1] = 1;
		else mp[0][0] = mp[1][1] = 1;
	}
};

Matrix quickpow(int p){
	Matrix ret(0), a(1);
	while(p){
		if (p & 1)
			ret = ret * a;
		a = a * a;
		p >>= 1;
	}	
	return ret;
}
ll get(int id){
	if(id==0) return 0;
	if(id==1) return 1;
	Matrix ret = quickpow(id - 2);
	ll ans = ret.mp[1][0] + ret.mp[1][1];
	return ans %= MOD;
}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	for(int i=2; i<maxn; i++) if(!sieve[i])
	{
		for(LL j=(LL)i*i; j<maxn; j+=i) sieve[j]=1;
	}
	while(~scanf("%d", &N))
	{
		if(N==1){puts("2"); continue;}
		prime.clear();
		int Lim=sqrt(N), tem=N;
		for(int i=2; i<=Lim; i++) if(!sieve[i] && !(tem%i))
		{
			while(!(tem%i)) tem/=i;
			prime.push_back(i);
		}
		if(tem>1) prime.push_back(tem);
		LL ans=0;
		for(int i=1; i<Lim; i++) if(!(N%i))
		{
			ans = (ans + GetP(N/i)*(get(i-1) + get(i+1))%MOD)%MOD;
			ans = (ans + GetP(i)*(get(N/i-1) + get(N/i+1))%MOD)%MOD;
		}
		if(Lim*Lim==N) ans = (ans + GetP(N/Lim)*(get(Lim-1)+get(Lim+1))%MOD)%MOD;
		
		ans = ans*Pow(N, MOD-2, MOD)%MOD;
		printf("%lld\n", (ans+MOD)%MOD);
	}
	return 0;
}

LL Pow(LL x, LL n, LL p)
{
	LL res = 1;
	while(n)
	{
		if(n&1) res=res*x%MOD;
		x=x*x%MOD;
		n>>=1;
	}
	return res;
}

LL GetP(LL n)
{
	LL res=n;
	for(int i=0; i<(int)prime.size(); i++) if(!(n%prime[i]))
	{
		res = res*(prime[i]-1)%MOD;
		res = res*Pow(prime[i], MOD-2, MOD)%MOD;
	}
	return res;
}
