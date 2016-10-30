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

const DBL eps = 1e-8;
int sgn(DBL x){return x>eps?1:(x<-eps?-1:0);}
struct data
{
	DBL x,y,s,r,d;
	int read(){return scanf("%lf%lf%lf%lf%lf", &x, &y, &s, &r, &d);}
};

int N;
DBL HP;
data in[110];
bool vis[110];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		for(int i=0; i<N; i++) in[i].read();
		for(int i=0; i<N; i++) in[i].r += 100;
		CLR(vis);
		scanf("%lf", &HP);
		int ok=1;
		while(ok)
		{
			ok = 0;
			DBL sum = 0;
			for(int i=0; i<N; i++) if(!vis[i] && sgn( SQR(100-in[i].x) + SQR(in[i].y) - SQR(in[i].r)) <= 0)
			{
				ok = 1;
				vis[i] = 1;
				HP -= in[i].d;
				sum += in[i].s;
			}
			for(int i=0; i<N; i++) if(!vis[i]) in[i].r += sum;
		}
		puts(sgn(HP)>0? "Safe!":"Danger!");
	}
	return 0;
}

