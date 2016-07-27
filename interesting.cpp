/*
SCU - 4532
a_1*b_1 + a_2*b_2 ... + a_n*b_n = B
给定 a_1...a_n，B_max、B_min
问有多少个 B_min <= B <= B_max，
使得 b_1 ... b_n存在非负整数解

首先问题可以转化为在区间 [0,B_max]有多少个 B满足条件
如果能解决这个，原问题的用 [0,B_max]的答案减去 [0,B_min-1]的即可

接下来有一个很关键的步骤，也是这题的神来之笔
之所以说神，是因为目前我还没深刻理解这么做的道理 (2016.7.14)
将等式两边 mod a_1（a序列中的任意一个数）
这样使得[0, B_max]中的数按 mod a_1的余数划分成若干个等价类
于是题目就转化为了求每个等价类中最小的那个数
因为知道了最小的数 x，那么这个等价类的大小就可以用 (B_max-x)/a_1 + 1来计算
然后把每个等价类的答案累加起来即为结果

设 dp[m] = b，即 B%a_1=m 这个等价类中，最小的那个数是 b
初始条件 dp[0]=0，在当前数 u的基础上不断增加 a_i，去更新 dp[(u+a_i)%a_1]的状态
转移方程为 for i=2..n: dp[(u+a_i)%a_1] = min( dp[u] + a_i ) 
由于这个 dp过程可能有环，所以采用 SPFA的方式进行转移
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=20, maxa=5e5+10;
const LL INF=0x3f3f3f3f3f3f3f3f;
int N;
LL bmin, bmax;
LL A[maxn];
LL dp[maxa];
bool inq[maxa];

LL Get(LL,LL,int);

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
		scanf("%d%lld%lld", &N, &bmin, &bmax);
		for(int i=1; i<=N; i++) scanf("%lld\n", &A[i]);
		sort(A+1, A+1+N);
		if(A[1]==0)
		{
			puts("0");
			continue;
		}
		MST(dp,0x3f);
		CLR(inq);
		dp[0]=0;
		inq[0]=1;
		queue<LL> que;
		que.push(0);
		while(que.size())
		{
			LL u=que.front(); que.pop();
			for(int i=2; i<=N; i++)
			{
				LL v = (u+A[i])%A[1];
				if(dp[v] > dp[u]+A[i])
				{
					dp[v] = dp[u]+A[i];
					if(!inq[v])
					{
						inq[v]=1;
						que.push(v);
					}
				}
			}
			inq[u]=0;
		}
//		for(int i=0; i<A[1]; i++) printf("%lld ", dp[i]); puts("");
		LL ans=0;
		for(int i=0; i<A[1]; i++)
		{
			ans += Get(bmax,dp[i],A[1]) - Get(bmin-1,dp[i],A[1]);
		}
		cout << ans << '\n';
	}
	return 0;
}

LL Get(LL R, LL L, int r)
{
	if(R<L) return 0;
	return (R-L)/r+1;
}

