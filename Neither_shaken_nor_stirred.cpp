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

const int maxn = 1e5+10;
int N, val[maxn];
vector<int> G[maxn];
int ent[maxn], lev[maxn];
bool inq[maxn];

bool update(int,int&);
void pri(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=1,k; i<=N; i++)
		{
			scanf("%d%d", &val[i], &k);
			G[i].clear();
			for(int j=1,v; j<=k; j++)
			{
				scanf("%d", &v);
				G[i].push_back(v);
			}
		}
		MST(ent,-1); MST(lev,-1); CLR(inq);
		queue<int> que;
		que.push(1);
		ent[1] = 0;
		inq[1] = 1;
		while(que.size())
		{
			int u = que.front(); que.pop();
			inq[u] = 0;
			lev[u] = val[u]?val[u]:ent[u];
			
			for(int i=0, v; i<(int)G[u].size(); i++)
			{
				v = G[u][i];
				if(update(lev[u], ent[v]) && !inq[v])
				{
					inq[v] = 1;
					que.push(v);
				}
			}
		}
		for(int i=1; i<=N; i++)
		{
			pri(ent[i]); putchar(' '); pri(lev[i]); putchar('\n');
		}
	}
	return 0;
}

void pri(int n)
{
	if(n==-2) printf("unknown");
	else if(n==0) printf("sober");
	else printf("%d", n);
}

bool update(int tval, int &nval)
{
	if(nval==-2) return 0;
	int tem = nval;
	if(nval==-1) nval = tval;
	else
	{
		if(tval==-2) nval = -2;
//		else if(tval>0 && nval==0) nval = tval;
//		else if(tval>0 && nval>0 && tval != nval) nval = -2;
		else if(nval>=0 && tval != nval) nval = -2;
	}
	return tem != nval;
}
