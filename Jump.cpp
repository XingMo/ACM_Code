/*
Codeforces - Gym100851J (NEERC15 - J)
交互题，有一个隐藏的长度为 N的 01串 S
每次可以询问一个 01串 Q，如果两串有一半相等或者全部相等
将会返回 N/2或者 N，否则都返回 0
最多可以询问 N+500次，如何得到这个隐藏串 S

构造好题！
做法就是先随机构造串，直到返回 N/2
实验证明随机下返回 N基本不可能，返回 N/2大概有 0.02的概率
所以期望 50次就能得到一个 N/2匹配的串

然后翻转 0的位置，再分别翻转后面一个位置，再询问
那么 0这个位置要么是匹配的，要么是不匹配的
如果同时翻转 0和 i，发现返回 N/2，说明 0和 i的正确性相反
那么找到所有正确性与 0相同的位置，同时翻转 0和这些位置
如果返回 N，那么说明 0是不匹配的，而且已经猜对了
如果返回 0, 说明 0本来就是匹配的，那么再全部翻转就行了
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
#define PCUT puts("\n----------")

const int maxl=1e3+10;
int N;
char A[maxl];
bool tag[maxl];

void rever(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	srand(time(0));
	scanf("%d", &N);
	int res=0;
	while(1)
	{
		for(int i=0; i<N; i++) A[i] = rand()%2+'0'; A[N]=0;
		puts(A);
		fflush(stdout);
		scanf("%d", &res);
		if(res==N/2 || res==N) break;
	}
	if(res==N/2)
	{
		rever(0);
		for(int i=1; i<N; i++)
		{
			rever(i);
			puts(A);
			fflush(stdout);
			scanf("%d", &res);
			if(res==0) tag[i] = 1;
			rever(i);
		}
		for(int i=1; i<N; i++) if(tag[i]) rever(i);
		puts(A);
		fflush(stdout);
		scanf("%d", &res);
		if(res!=N)
		{
			for(int i=0; i<N; i++) rever(i);
			puts(A);
			fflush(stdout);
		}
	}
	return 0;
}

void rever(int np) {A[np] = (1- (A[np]-'0')) + '0';}

