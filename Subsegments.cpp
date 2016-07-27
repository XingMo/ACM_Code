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

const int maxn=1e5+10;
int N,K;
int inpt[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d%d", &N, &K);
	for(int i=1; i<=N; i++) scanf("%d", &inpt[i]);
	map<int,int> cnt;
	set<int> list;
	for(int i=1; i<=K; i++)
	{
		int ncnt=++cnt[inpt[i]];
		if(ncnt==1) list.insert(inpt[i]);
		else if(ncnt>1) list.erase(inpt[i]); 
	}
	for(int i=K; i<=N; i++)
	{
		if(list.begin() == list.end()) puts("Nothing");
		else
		{
			auto it=--list.end();
			printf("%d\n", *it);
		}
		int ncnt;
		ncnt = --cnt[inpt[i-K+1]];
		if(ncnt==1) list.insert(inpt[i-K+1]);
		else if(ncnt>1 || ncnt==0) list.erase(inpt[i-K+1]);
		
		ncnt = ++cnt[inpt[i+1]];
		if(ncnt==1) list.insert(inpt[i+1]);
		else if(ncnt>1 || ncnt==0) list.erase(inpt[i+1]);
	}
	return 0;
}

