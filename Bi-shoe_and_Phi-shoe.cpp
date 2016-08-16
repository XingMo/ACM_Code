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
#define PCUT puts("----------")

const int maxn=1e6+10;
int phi[maxn], prime[maxn], pcnt;
int ans[maxn];
bool sieve[maxn];
void init();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	init();
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		int N;
		scanf("%d", &N);
		LL res=0;
		for(int i=0,x; i<N; i++)
		{
			scanf("%d", &x);
			if(x!=1) res += ans[x];
			else res += 2;
		}
		printf("Case %d: %lld Xukha\n", ck, res);
	}
	return 0;
}

void init()
{
	phi[1]=1;
	for(int i=2; i<maxn; i++)
	{
		if(!sieve[i]) {phi[i]=i-1; prime[pcnt++]=i;}
		for(int j=0; j<pcnt; j++)
		{
			if((LL)i*prime[j] >= maxn) break;
			sieve[i*prime[j]] = 1;
			if(i%prime[j]) phi[i*prime[j]] = phi[i]*(prime[j]-1);
			else { phi[i*prime[j]] = phi[i]*prime[j]; break;}
		}
	}
	for(int i=1; i<=180; i++) printf("%d: %d\n", i, phi[i]);
	MST(ans,-1);
	int tmin=-1;
	for(int i=1; i<maxn; i++) if(ans[phi[i]] == -1)
	{
		ans[phi[i]] = i;
	}
	for(int i=maxn-1; i>=1; i--)
	{
		if(ans[i] != -1) tmin = ans[i];
		else ans[i] = tmin;
	}
}
