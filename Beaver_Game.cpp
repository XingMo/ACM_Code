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

int N,M,K;
bool SG(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d%d%d", &N, &M, &K);
	if(!(N&1)) {puts("Marsel"); return 0;}
	if(K==1)
	{
		if(M != 1) puts("Timur");
		else puts("Marsel");
		return 0;
	}
	if(SG(M)) puts("Timur");
	else puts("Marsel");
	return 0;
}

bool SG(int num)
{
	int lim=sqrt(num);
	if(num<2*K) return 0;
	for(int i=2; i<=lim; i++)
	{
		if(num%i) continue;
		if(i>=K && !((num/i)&1)) return 1;
		if(num/i>=K && !(i&1)) return 1;
		if(i>=K && !SG(num/i) ) return 1;
		if(num/i>=K && !SG(i) ) return 1;
	}
	return 0;
}

