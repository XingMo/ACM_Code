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
//	printf("%d\n", T);
	for(int ck=1; ck<=T; ck++)
	{
		int G=4, B=12, S=2;
		printf("%d %d %d\n", G, B, S);
		for(int i=0, n; i<B; i++)
		{
			n = rand()%4+1;
			printf("%d ", n);
			for(int j=0; j<n; j++) printf("%d ", rand()%G+1); puts("");
		}
	}
	printf("0 0 0\n");
	return 0;
}

int get(int &x, int &y)
{
	x = rand()%MOD-MOD/2;
	y = rand()%MOD-MOD/2;
}
