/*
HDU - 5816
牌堆里有 N张 A类卡，M张 B类卡
A类卡能让你从牌堆里抽两张卡
第 i张 B类卡能让你对对手造成 x_i点伤害
刚开始从牌堆抽 1张牌，并且对手有 P点生命值
问一回合内打倒对手的概率是多少

赛后看了下题解，感谢出题人让我 O(N*2^N)过了
做法就是状压一下每张牌抽到的情况，dp[mask]表示
走到牌的情况为 mask的状态的方案数
然后根据抽到了的 A类牌和一共抽到的牌可以判断还能不能抽牌
并且可以判断当前情况能否取得胜利
如果能够取得胜利，游戏直接结束，就再乘一下剩下没抽到的牌的排列
如果不能，并且还能抽牌，就接着枚举下一张牌抽什么，向下转移

题解的做法特别机智，它转化了一下思路
如果能抽牌，我就一直抽，直到不能抽牌为止，
我再把手里的伤害牌一次性打出
这样也不会有重复或者遗漏

这样一来，需要考虑的情况只有两种：
1. 牌堆里还有牌，A类牌抽了 k-1张，B类牌抽了 k张，这样不能再抽牌了，
如果此时伤害已经超过了 P，那么就记入答案
2. 整个牌堆都被抽完，这样也不能再抽牌了
同样如果此时伤害超过了 P，也记入答案

至于 A类牌抽了 i张、B类牌抽了 j张的方案数可以预处理出来
然后再对抽到的牌进行组合排列一下，对没抽到的牌也排列组合一下
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
#define PCUT puts("\n----------")

LL gcd(LL a, LL b){return b?gcd(b, a%b):a;}
int P,N,M,fmask,Amask,tot;
int dam[30];
LL dp[1<<20], fact[25];

bool check(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	fact[0]=1;
	for(int i=1; i<=20; i++) fact[i] = fact[i-1]*i;
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d%d", &P, &N, &M);
		for(int i=0; i<M; i++) scanf("%d", &dam[i]);
		fmask = (1<<(N+M))-1;
		Amask = (1<<N)-1;
		tot = N+M;
		LL ans=0;
		CLR(dp);
		for(int i=0; i<tot; i++) dp[1<<i] = 1;
		for(int m=0, left, have, haveA; m<=fmask; m++)
		{
			have = __builtin_popcount(m);
			left = tot-have;
			haveA= __builtin_popcount(m&Amask);
			if(check(m))
			{
				ans += dp[m]*fact[left];
				continue;
			}
			if(haveA*2+1-have<=0) continue;
			for(int i=0; i<tot; i++) if(!((m>>i)&1))
			{
				dp[m|(1<<i)] += dp[m];
			}
		}
		LL D=gcd(ans, fact[N+M]);
		printf("%lld/%lld\n", ans/D, fact[N+M]/D);
	}
	return 0;
}

bool check(int mask)
{
	mask>>=N;
	int res=0;
	for(int i=0; i<M; i++) if((mask>>i)&1)res += dam[i];
	if(res >= P) return 1;
	return 0;
}

/*
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
#define PCUT puts("\n----------")

LL GCD(LL a, LL b){return b?GCD(b,a%b):a;}
int P,N,M, A[1<<20], sum[1<<20], cnt[1<<20], fmask;
LL f[25][25], fact[25], C[25][25];

void init();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	f[0][0] = f[0][1] = 1;
	for(int i=1; i<=20; i++)
	{
		f[i][0]=1;
		for(int j=1; j<i; j++) f[i][j] = f[i-1][j] + f[i][j-1];
		f[i][i] = f[i][i+1] = f[i][i-1];
	}
	
	for(int i=1; i<(1<<20); i++) cnt[i] = cnt[i^(i&-i)] + 1;
	
	fact[0]=1;
	for(int i=1; i<=20; i++) fact[i] = fact[i-1]*i;
	
	for(int i=0; i<=20; i++)
	{
		C[i][0]=1;
		for(int j=1; j<=i; j++) C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d%d%d", &P, &N, &M);
		LL ans=0;
		fmask = (1<<M)-1;
		for(int i=0; i<M; i++) scanf("%d", &A[1<<i]);
		sum[0] = 0;
		for(int i=1; i<=fmask; i++) sum[i] = sum[i^(i&-i)] + A[i&-i];
		for(int i=0; i<=fmask; i++) if(sum[i]>=P && cnt[i] <= N+1)
		{
			ans += C[N][cnt[i]-1] * f[cnt[i]-1][cnt[i]] * fact[cnt[i]-1] * fact[cnt[i]] * fact[N+M-2*cnt[i]+1];
		}
		if(sum[fmask] >= P && cnt[fmask] < N+1) ans += f[N][M] * fact[N] * fact[M];
		LL D = GCD(ans, fact[N+M]);
		printf("%lld/%lld\n", ans/D, fact[N+M]/D);
	}
	return 0;
}
*/
