/*
HDU - 5823
给定一个 N个点的图，
求它的每一个子图的最小染色数
其中 N<=18

没想到枚举子集居然是 3^N次方的
没想到 3^N也能过……
总之就先枚举每一个子图，再枚举子图的一个子集
如果这个子集是一个独立集的话，这个子集就涂同一个颜色
然后从割掉这个独立集剩下的图的状态转移出来，取一个min
别管复杂度了，总之是过了，1600+ms……
看了下赛上的榜，大部分差不多就是这个时间
难道他们也是这样暴力怼过去的么 orz
*/
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
typedef unsigned int uint;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("\n----------")

int N, fmask;
bool invid[1<<18];
uint res[1<<18];
char Map[20][20];

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
		scanf("%d", &N);
		CLR(invid);
		fmask = (1<<N)-1;
		for(int i=0; i<N; i++) scanf(" %s", Map[i]);
		for(int m=1; m<=fmask; m++)
		{
			for(int i=0; i<N; i++) if((m>>i)&1)
			{
				for(int j=0; j<N; j++) if((m>>j)&1 && Map[i][j]=='1') {invid[m]=1; break;}
				if(invid[m]) break;
			}
		}
		MST(res, 0x3f);
		res[0]=0;
		for(int m=1; m<=fmask; m++)
		{
			for(int m0=m; m0; m0=(m0-1)&m) if(!invid[m0])
			{
				res[m] = min(res[m], res[m^m0]+1);
			}
		}
		
		uint prod=1, ans=0;
		for(int m=1; m<=fmask; m++) ans += res[m]*(prod*=233);
		printf("%u\n", ans);
	}
	return 0;
}
