/*
LightOJ - 1342
有 N根棍子，每根棍子都有一个权值
其中有若干根可识别的，若干根不可识别的
抽到了可识别的棍子，就不放回，抽到了不可识别的，就要放回
问所有棍子都至少被抽过一次后的期望权值和

根据期望的线性性，E(CX) = CE(X)
所以可以对每根棍子求一下它被抽到的期望次数，再乘以它的权值
首先对于可识别的棍子，它被抽到的期望次数为定值 1
对于不可识别的棍子，由于它被抽到的概率满足几何分布
所以可以转化成一类经典模型，叫做邮票收集问题
所以它被抽到的期望次数直接就等于 H[n]
其中 n是棍子的总个数 （包括可识别的）
H[n]是调和级数的第 n项
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

const int maxn=5e3+10;
int N;
DBL H[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif

	for(int i=1; i<maxn; i++) H[i] = H[i-1] + 1.0/i;
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d", &N);
		DBL ans=0;
		for(int i=1,w,t; i<=N; i++)
		{
			scanf("%d%d", &w, &t);
			if(t==1) ans += w;
			else ans += H[N]*w;
		}
		printf("Case %d: %.5f\n", ck, ans);
	}
	return 0;
}

