/*
LightOJ - 1265
一个岛上有若干只虎，若干只鹿，一个人
每天只有两个动物会相见
如果人和虎相见，人死
如果鹿和虎相见，鹿死
如果虎和虎相见，虎死
其他情况均没有伤亡，各种情况均等概率
问人活到虎全死光的概率有多少

感觉二维dp直接搞正确性很显然
但是网上有另一种做法，就是直接忽略掉鹿的存在，当没有鹿
不是很懂这样做的正确性，网上的解释是鹿吃与被吃，
与人没有关系，顶多延长游戏时间

有几个trick，如果虎的数量为奇数，那么人死定了，
如果虎的数量为 0 ，那么人直接赢
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
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

int N,M;

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
		scanf("%d%d", &N, &M);
		printf("Case %d: ", ck);
		if(N==0) puts("1");
		else if(N&1) puts("0");
		else 
		{
			DBL ans=1;
			while(N)
			{
				ans *= (DBL)(N-1)/(N+1);
				N -= 2;
			}
			printf("%.8f\n", ans);
		}
	}
	return 0;
}

