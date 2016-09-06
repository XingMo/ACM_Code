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
#include <cassert>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define MSTO(a,b) memset(&a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define CLRO(a) MSTO(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("\n----------")

const int maxl=1e5+10;
struct SAM
{
	const static int nxt_siz=27;
	const static int maxn = 7e6+1e5+10;
	struct node
	{
		int len, fath, pos, nxt[nxt_siz];
	} sam[maxn];
	int last,siz;
	int chnum(char x){return x-'a';}
	int newnode()
	{
		CLRO(sam[siz]);
		siz ++;
		return siz-1;
	}
	void init()
	{
		siz = 0;
		last = newnode();
		sam[0].fath = -1;
	}
	void extend(char,int);
	void solve(char*);
	char buff[maxn];
	void display(int np=0, int dep=0)
	{
		bool ok=0;
		for(int i=0; i<nxt_siz; i++) if(sam[np].nxt[i])
		{
			buff[dep] = i+'a';
			ok=1;
			display(sam[np].nxt[i], dep+1);
		}
		if(!ok)
		{
			buff[dep]=0;
			puts(buff);
		}
	}
};

int N,M;
char buff[maxl];
SAM sam;

int main()
{
	#ifdef LOCAL
	freopen("1010.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		sam.init();
		scanf("%d%d", &N, &M);
		int len=0;
		for(int i=0; i<N; i++)
		{
			scanf("%s", buff);
			len+=strlen(buff);
			for(int j=0; buff[j]; j++) sam.extend(buff[j], j+1);
			sam.extend('z'+1, 0);
		}
		printf("Case #%d:\n", ck);
		for(int i=0; i<M; i++)
		{
			scanf("%s", buff);
			sam.solve(buff);
		}
	}
	return 0;
}

void SAM::solve(char str[])
{
	int np=0;
	for(int i=0; str[i]; i++)
	{
		np = sam[np].nxt[chnum(str[i])];
		if(!np) break;
	}
	if(!np) puts("0");
	else printf("%d\n", min(sam[np].pos, sam[np].len) - sam[sam[np].fath].len);
}

void SAM::extend(char _c, int pos)
{
	int c = chnum(_c), u=last, np = newnode();
	last = np;
	sam[np].len = sam[u].len+1;
	sam[np].pos = pos;
	for( ; ~u && !sam[u].nxt[c]; u=sam[u].fath) sam[u].nxt[c] = np;
	if(u==-1) sam[np].fath = 0;
	else
	{
		int v = sam[u].nxt[c];
		if(sam[u].len+1 == sam[v].len) sam[np].fath = v;
		else
		{
			int w = newnode();
			memcpy(sam+w, sam+v, sizeof(sam[w]));
			sam[w].len = sam[u].len + 1;
			sam[w].pos = pos;
			sam[v].fath = sam[np].fath = w;
			for(; ~u && sam[u].nxt[c]==v; u=sam[u].fath) sam[u].nxt[c] = w;
		}
	}
}
