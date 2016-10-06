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
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("\n----------")

const int maxn=1e5+10;
int N,M;
int in[maxn];
deque<LL> dq[2];

LL check(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d", &N, &M);
		for(int i=1; i<=N; i++) scanf("%d", &in[i]);
		sort(in+1, in+1+N);
		int l=2, r=N;
		printf("%lld\n", check(3));
		return 0;
		while(l<r)
		{
			int mid=(l+r)>>1;
			if(check(mid) <= M) r=mid;
			else l=mid+1;
		}
		printf("%d\n", l);
	}
	return 0;
}

LL check(int k)
{
	LL res=0, tot=N, sum;
	dq[0].clear(); dq[1].clear();
	for(int i=1; i<=N; i++) dq[0].push_back(in[i]);
	while(tot>1)
	{
		int cnt=0;
		LL sum = 0, now, tp;
		while(cnt<k)
		{
			if(!dq[0].size() && !dq[1].size()) break;
			cnt++;
			if(!dq[0].size() && dq[1].size()) now = dq[1].front(), tp=1;
			else if(dq[0].size() && !dq[1].size()) now = dq[0].front(), tp=0;
			else if(dq[0].front() <= dq[1].front()) now = dq[0].front(), tp=0;
			else now = dq[1].front(), tp=1;
			sum+=now, dq[tp].pop_front();
		}
		res += sum;
		dq[1].push_back(sum);
		tot = tot-cnt+1;
		printf("%lld %lld\n", sum, tot);
		if(!dq[0].size()) swap(dq[0], dq[1]);
	}
	return res;
}
