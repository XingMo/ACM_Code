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

const int maxn=1e5+10;
int N,K;
int A[maxn];
LL psum[maxn];

bool check(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &K))
	{
		for(int i=1; i<=N; i++) scanf("%d", &A[i]);
		sort(A+1, A+1+N);
		int ans=0, num=A[1];
		for(int i=1; i<=N; i++)
		{
			psum[i] = psum[i-1] + A[i];
			int l=1, r=i;
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(check(mid,i)) r=mid;
				else l=mid+1;
			}
			if(i-l+1>ans)
			{
				ans = i-l+1;
				num = A[i];
			}
		}
		printf("%d %d\n", ans, num);
	}
	return 0;
}

bool check(int l, int r)
{
	LL sum = psum[r] - psum[l-1];
	sum = (LL)(r-l+1)*A[r] - sum;
	return sum<=K;
}

