/*
HDU - 5881
有一壶水和两个杯子，每次只能从壶里往杯子里倒水
杯子中的水量是可见的，壶中的水量是不可见的
但是可以知道壶里的水倒完了没有
开始壶中的水量在 [L,R]中，要求将水到入杯中
并且最后壶中的水量不超过 1，两个杯子的水量差不超过 1

贪心，由于我不知道壶中有多少水，但我知道下限
于是先向一个杯子中倒入 {L-1}/2 + 1的水，另一个杯子中倒入 {L-1}/2
然后每次往少的杯子中倒入 2的水，这样两杯的水始终是平衡的
但是这题trick很多，主要集中在一些极端数据上
1. L==R的时候，直接能够确定水量，所以直接贪心倒即可
2. L<=1的时候，刚开始倒的水量可能不是 {L-1}/2 + 1，所以直接枚举小数据手算即可
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

LL L,R;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%lld%lld", &L, &R))
	{
		LL ans;
		if(L==R)
		{
			if(L<2) ans = 0;
			else if(L==2) ans = 1;
			else ans = 2;
		}
		else
		{
			if(L>1)
			{
				ans = 2 + (R-L)/2;
				if(R-L>=2) ans--;
			}
			else if(L==1)
			{
				ans = 1 + (R-L)/2;
			}
			else
			{
				if(R==1) ans = 0;
				else if(R==2) ans = 1;
				else ans = 1 + (R-1)/2;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}

