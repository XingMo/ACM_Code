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

const int maxn=1e6+10, INF=0x3f3f3f3f;
int N;
int inpt[2*maxn];
deque<int> que,pos;

void push(int,int);
void pop(int);
void init();
void pri();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d", &N);
	for(int i=0; i<N; i++)
	{
		scanf("%d", &inpt[i]);
		inpt[i+N]=inpt[i];
	}
	int l=0, r=0, sum=0, ans=0;
	init();
	while(l<N)
	{
		if(inpt[l]<0){l++; continue;}
		for(r=max(l,r); r-l+1<=N; r++)
		{
			sum+=inpt[r];
			push(sum,r);
			if(l+1>8) pri();
			if(sum<0) break;
		}
		if(r-l+1<=N)
		{
			l=r+1;
			sum=0;
			init();
		}
		else
		{
			ans++;
			printf("%d %d\n", l+1, r);
			int tem=0;
//			if(l+1>=8) pri();
			tem+=inpt[l];
			sum-=inpt[l++];
			while(l<N && inpt[l]<0){ tem+=inpt[l]; sum-=inpt[l++];}
			pop(l);
			while(l<N && que.size() && (que[0]-=tem)<0)
			{
				while(l<N && l<=pos.front()) {tem+=inpt[l]; sum-=inpt[l++];}
				pop(l);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}

void init()
{
	que.clear(); pos.clear();
}

void push(int v, int p)
{
	while(que.size() && que.back() >= v) {que.pop_back(); pos.pop_back();}
	que.push_back(v);
	pos.push_back(p);
}

void pop(int p)
{
	while(pos.size() && pos.front() < p) {que.pop_front(); pos.pop_front();}
}

void pri()
{
	puts("the queue:");
	for(int i=0; i<(int)que.size(); i++)
	{
		printf("%d %d\n", que.at(i), pos.at(i));
	}
}
