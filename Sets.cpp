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

const int maxn=210, maxm=2e4+10;
set<int> all;
vector<int> inset[maxn], tset[maxm];
bool vis[maxn];
int ans[maxn];
int apr[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	scanf("%d", &N);
	for(int i=N*(N-1)/2; i>=1; i--)
	{
		int cnt,x;
		scanf("%d", &cnt);
		for(int j=1; j<=cnt; j++)
		{
			scanf("%d", &x);
			all.insert(x);
			tset[i].push_back(x);
			inset[x].push_back(i);
		}
	}
	if(N==2)
	{
		printf("1 ");
		for(auto &i:all) {vis[i]=1; printf("%d\n", i); break;}
	}
	for(auto &i:all) if(!vis[i])
	{
		int np=0;
		ans[np++]=i;
		vis[i]=1;
		for(auto &j:inset[i])
		{
			for(auto &k:tset[j]) if(!vis[k]) apr[k]++;
//			printf("%d in %d\n", i, j);
		}
		for(auto &j:all) 
		{
			if(apr[j] == (int)inset[i].size())
			{
				ans[np++] = j;
				vis[j]=1;
			}
			apr[j] = 0;
		}
		printf("%d", np);
		for(int j=0; j<np; j++) printf(" %d", ans[j]);
		puts("");
	}
	return 0;
}

