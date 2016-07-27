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

const int maxn=1e3+10;
int B[maxn];
vector<int> A;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N,K;
	scanf("%d%d", &N, &K);
	for(int i=1; i<=N; i++) scanf("%d", &B[i]);
	A.push_back(N);
	for(int i=N-1; i>=1; i--)
	{
		int np=0;
		for(int j=0; j<(int)A.size(); j++)
		{
			if(B[i]<=0) break;
			if(i+K<=A[j]) B[i]--;
			np++;
		}
		A.insert(A.begin()+np, i);
	}
	for(int i=0; i<(int)A.size(); i++) printf("%d ", A[i]);
	return 0;
}

