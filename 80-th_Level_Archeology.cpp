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

const int maxn=5e5+10, maxm=1e6+10;
int N,C;
int in[2][maxn];
int len[2];
int sque[maxm];

void work(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &C))
	{
		CLR(sque);
		int cur=1, las=0, tot=0;
		scanf("%d", &len[cur]);
		for(int i=1; i<=len[cur]; i++) scanf("%d", &in[cur][i]);
		for(int i=2; i<=N; i++)
		{
			cur=i&1, las=(i-1)&1;
			scanf("%d", &len[cur]);
			for(int j=1; j<=len[cur]; j++) scanf("%d", &in[cur][j]);
			bool flag=0;
			for(int j=1; j<=len[cur] && j<=len[las]; j++)
			{
				if(in[cur][j] == in[las][j]) continue;
				flag = 1;
				tot++;
				work(in[las][j], in[cur][j]);
				break;
			}
			if(!flag && len[cur]<len[las]) tot++;
		}
		int now=0, ans=-1;
		for(int i=0; i<C; i++)
		{
			now += sque[i];
			if(now==tot) {ans=i; break;}
		}
		printf("%d\n", ans);
	}
	return 0;
}

void work(int x, int y)
{
	int l=C-max(x,y)+1, r=C-min(x,y);
	if(x>y) sque[l]++, sque[r+1]--;
	else
	{
		sque[0]++, sque[l]--;
		sque[r+1]++, sque[C]--;
	}
}
