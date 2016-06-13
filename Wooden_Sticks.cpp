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

const int maxn=5e3+10;
int N;
Pii inpt[maxn];
bool vis[maxn];
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
		scanf("%d", &N);
		for(int i=0; i<N; i++)
		{
			scanf("%d%d", &inpt[i].first, &inpt[i].second);
		}
		sort(inpt, inpt+N);
		int ans=0;
		CLR(vis);
		for(int i=0; i<N; i++)
		{
			if(vis[i]) continue;
			ans++;
			int high=inpt[i].second;
			for(int j=i; j<N; j++)
			{
				if(!vis[j] && inpt[j].second >= high)
				{
					vis[j]=1;
					high = inpt[j].second;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

