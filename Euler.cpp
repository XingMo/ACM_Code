#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)

const int maxn=500+10;
int N,M;
int Map[maxn][maxn];
int deg[maxn], edc[maxn];
bool vis[maxn];

bool judg(), judg_res;
void solve1();
void solve2();

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
		CLR(Map); CLR(edc); CLR(deg);
		scanf("%d%d", &N, &M);
		for(int i=0; i<M; i++)
		{
			int u,v;
			scanf("%d%d", &u, &v);
			Map[u][v]=1; Map[v][u]=-1;
			edc[u]++; edc[v]++;
			deg[u]++; deg[v]--;
		}
		judg();
		solve1();putchar(' ');
		solve2();puts("");
	}
	return 0;
}

void solve1()
{
	if(!judg_res){printf("No");return;}
	int cnt=0;
	for(int i=1; i<=N; i++) if(edc[i]&1) cnt++;
	if(cnt==2 || cnt==0) printf("Yes");
	else printf("No");
}

void solve2()
{
	if(!judg_res){printf("No");return;}
	int cnt0=0, cnt1=0, cnt2=0;
	for(int i=1; i<=N; i++)
	{
		if(deg[i] == 1) cnt0++;
		if(deg[i] == -1) cnt1++;
		if( abs(deg[i]) >= 2) {cnt2++;break;}
	}
	if(cnt2==0 && ((cnt0==0&&cnt1==0) || (cnt0==1&&cnt1==1))) printf("Yes");
	else printf("No");
}

bool judg()
{
	CLR(vis);
	queue<int> que;
	int bcnt=0;
	for(int i=1; i<=N; i++)
	{
		if(vis[i]) continue;
		que.push(i);
		while(que.size())
		{
			int u=que.front(); que.pop();
			for(int v=1; v<=N; v++) if(!vis[v] && Map[u][v]) {que.push(v); vis[v]=1;}
		}
		bcnt++;
		if(bcnt>1) break;
	}
	if(bcnt>1) return judg_res = 0;
	return judg_res = 1;
}
