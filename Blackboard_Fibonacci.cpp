/*
Codeforces - 217B
递推一个菲波那契数列，开始时有上下两个数分别为 0 和 1
然后一个 T操作是将上面的数替换成两数之和
B操作是将下面的数替换成两数之和
这样一来 T和 B是交替进行的，但是过程中出了错，
在 N次操作以后，得到一个数 R
问最少错几次能得到最后一个数，并输出操作序列
其中 1<=N,R<=1e6

一看 N和 R都是 1e6级别的，还要求最小
所以我就老是往贪心构造那方面想，结果想破了头也毫无办法

正确的解法是一个暴力
知道了最后一个数 R，枚举另一个数
由于数列必然是递增的，所以这个数的取值范围是 [1,R]
如果最后两个数确定了，那么操作的序列也就唯一确定了
所以我们倒着推回去，每次用大的那个减去小的
这样看起来复杂度是 O(RN)的，实际上这个减的过程是一个更相减损术
这样一来就可以用辗转相除的方式优化这个减的过程
所以每次递推序列长度不会超过 logR
但实际上好像数据比较水，直接用减的也能过
另外可行性的判断有两个：
1. 由于数列是严格递增的，倒推到起始位置前，上面的数不能等于下面的数
2. 倒推到起始位置的时候，两个数都要等于 1
时间复杂度 O(RlogR)
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

const int maxn=1e6+10, INF=0x3f3f3f3f;
int N,R,ans;
char buff[maxn], res[maxn];

void solve(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &R))
	{
		ans=INF;
		for(int i=1; i<=R; i++)
		{
			solve(i,R);
			solve(R,i);
		}
		if(ans==INF) puts("IMPOSSIBLE");
		else printf("%d\n%s\n", ans, res);
	}
	return 0;
}

void solve(int top, int bot)
{
	for(int i=N-1; i>0; i--)
	{
		if(top==bot) return;
		if(top>bot)
		{
			top-=bot;
			buff[i]='T';
		}
		else
		{
			bot-=top;
			buff[i]='B';
		}
	}
	if(top!=1 || bot!=1 ) return;
	buff[0] = 'T';
	int cnt=0;
	for(int i=1; i<N; i++) if(buff[i-1]==buff[i]) cnt++;
	if(cnt<ans)
	{
		ans = cnt;
		memcpy(res, buff, sizeof(buff[0])*N);
		res[N]=0;
	}
}
