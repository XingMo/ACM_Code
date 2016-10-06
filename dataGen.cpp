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
#include <ctime>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))

int MOD=3;
const DBL eps = 1e-5;
int sgn(DBL x){return x<-eps?-1:(x>eps?1:0);}
int get(int&,int&);

int main()
{
	freopen("in.txt", "w", stdout);
	
	srand(time(0));
	int T=1;
	printf("%d\n", T);
	for(int ck=1; ck<=T; ck++)
	{
		set<Pii> vis;
		int N=4, M=4, B=4, K=2, R=1e5, T=200;
		printf("%d %d %d %d %d %d\n", N, M, B, K, R, T);
		for(int i=0; i<K; i++,puts("")) for(int j=1; j<=N; j++)
		{
			int temp=-1;
			if(j!=1 && j!=N) temp = rand()%100+1;
			printf("%d ", temp);
		}
		for(int i=2; i<=N; i++)
		{
			int u = rand()%(i-1)+1;
			vis.insert({u,i});
			vis.insert({i,u});
			printf("%d %d %d %d\n", u, i, rand()%15+1, rand()%101);
		}
		for(int i=M-(N-1); i>0; i--)
		{
			int u,v;
			do{u=rand()%N+1, v=rand()%N+1;} while(u==v || vis.find({u,v})!=vis.end());
			printf("%d %d %d %d\n", u, v, rand()%15+1, rand()%101);
		}
	}
	return 0;
}

int get(int &x, int &y)
{
	x = rand()%MOD-MOD/2;
	y = rand()%MOD-MOD/2;
}
