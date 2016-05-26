/*
POJ - 1017
有 1*1、2*2、3*3、4*4、5*5、6*6六种货物
要求用最少的包裹把他们全装进去

首先肯定先选用 6*6的包裹
然后我们可以联想到一个哲学故事：
往一个瓶子里装满了石头，这时候还能往里面灌沙子
灌满了沙子，还能往里面灌水……
所以我们可以想到，在一个包裹里优先装大的物品
如果这个包裹还有剩的空间，再小的物品尽可能地塞进去

首先 6、5、4肯定是独占一个包裹
把 5放进包裹时，剩下的空间可以放 11个 1
把 4放进包裹时，剩下的空间可以放 5个 2

把 3放进包裹时，1 个包裹正好装 4个 3
如果还有剩下的，就分别考虑
剩下 1个 3，装进包裹后还能放 5个 2和 7 个 1
剩下 2个 3，装进包裹后还能放 3个 2和 6 个 1
剩下 3个 3，装进包裹后还能放 1个 2和 5 个 1

如果 2已经放完了，就把放 2的空间放 4个 1
剩下的就只有 2和 1，就比较好处理了
*/
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

LL inpt[10];
void redc();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(1)
	{
		for(int i=1; i<=6; i++) scanf("%lld", &inpt[i]);
		LL judg=0;
		for(int i=1; i<=6; i++) judg+=inpt[i];
		if(!judg) break;
		
		LL ans=(LL)inpt[6]+(LL)inpt[5]+(LL)inpt[4];
		if(inpt[5]>0) inpt[1]-=11*inpt[5];
		if(inpt[4]>0) inpt[2]-=5*inpt[4];
		redc();
		
		if(inpt[3]>0)
		{
			ans+=inpt[3]/4;
			inpt[3]%=4;
		}
		if(inpt[3]>0) ans++;
		
		if(inpt[3]==1)
		{
			inpt[2]-=5;
			redc();
			inpt[1]-=7;
		}
		else if(inpt[3]==2)
		{
			inpt[2]-=3;
			redc();
			inpt[1]-=6;
		}
		else if(inpt[3]==3)
		{
			inpt[2]-=1;
			redc();
			inpt[1]-=5;
		}
		
		if(inpt[2]>0)
		{
			ans+=inpt[2]/9;
			inpt[2]%=9;
		}
		if(inpt[2]>0)
		{
			ans++;
			inpt[2]-=9;
			redc();
		}
		
		if(inpt[1]>0)
		{
			ans+=inpt[1]/36;
			inpt[1]%=36;
		}
		if(inpt[1]>0) ans++;
		
		printf("%lld\n", ans);
	}
	return 0;
}

void redc()
{
	LL left=0;
	if(inpt[2]<0) 
	{
		left=-4*inpt[2];
		inpt[2]=0;
	}
	inpt[1]-=left;
}
