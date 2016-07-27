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

int X,Y,N,D;
int sg[410][410];
int vec[30][2];

bool judge(int,int);
int SG(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	MST(sg,-1);
	scanf("%d%d%d%d", &X, &Y, &N, &D);
	for(int i=0; i<N; i++) scanf("%d%d", &vec[i][0], &vec[i][1]);
	if(SG(X+200,Y+200)) puts("Anton");
	else puts("Dasha");
	return 0;
}

int SG(int x, int y)
{
	if(~sg[x][y]) return sg[x][y];
	for(int i=0; i<N; i++) if(judge(x+vec[i][0], y+vec[i][1]))
	{
		if(!SG(x+vec[i][0],y+vec[i][1])) return sg[x][y] = 1;
	}
	return sg[x][y] = 0;
}

bool judge(int x,int y)
{
	return SQR(D) >= SQR(x-200)+SQR(y-200);
}
