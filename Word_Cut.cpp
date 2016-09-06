/*
Codeforces - 176B
给定一个 A串，每次可以将其从分为两个非空子串
然后交换这两个串的位置，得到一个新串
问这样操作 K次以后得到 B串的方案数

实际上可以将 A串看成一个循环的串
每次切的操作实际上就是改变起始位置
并且相邻的两次起始位置不能相同
比如 ababaab，我从第一个 b后面切开，就变成 abaab|ab
实际上只不过是换了一个起始位置而已
由 |ababaab|ababaab...变成了 ab|abaabab|abaab
所以切割的序列实际上就是一个原串起始位置的序列
所以这样一来，问题就转化为给定一个长度为 K+1的序列
填入 [0,len-1]的数，使得相邻两个数不相等，并且第一个数是 0的方案数

所以首先做一次 KMP，找出 B串能在 A串的哪些位置被匹配
然后做一次 dp，dp[i][0]表示第 i个数是 0的方案数，dp[i][1]表示不是 0的方案数
由于开始已经固定是 0了，所以除了 0以外，剩下的数地位相同，方案数是对称的
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

const int maxn=1e3+10, MOD=1e9+7;
struct KMP
{
	char *patn;
	int plen,fail[maxn];
	int m0,m1;
	void init(char*,int);
	void match(char*,int);
};

int len,K;
char A[2*maxn],B[maxn];
KMP kmp;
int dp[2][2];

LL Pow(LL,LL,LL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%s%s%d", A, B, &K))
	{
		if(K==0)
		{
			if(!strcmp(A,B)) puts("1");
			else puts("0");
			continue;
		}
		len=strlen(A);
		for(int i=len; i>=0; i--) A[i+len] = A[i];
		kmp.init(B,len);
		kmp.match(A,2*len-1);
		CLR(dp);
		dp[1][0] = 0; dp[1][1] = len-1;
		int inv = Pow(len-1, MOD-2, MOD);
		for(int i=2,cur,las; i<=K; i++)
		{
			cur=i&1, las=(i-1)&1;
			CLR(dp[cur]);
			dp[cur][0] = dp[las][1];
			dp[cur][1] = ((LL)dp[las][0]*(len-1)%MOD + (LL)dp[las][1]*(len-2)%MOD)%MOD;
		}
		int res=0;
		if(kmp.m0) res = dp[K&1][0];
		res = (res + (LL)dp[K&1][1]*inv%MOD*kmp.m1%MOD)%MOD;
		printf("%d\n", res);
	}
	return 0;
}

void KMP::init(char str[], int len)
{
	m0 = m1 = 0;
	plen=len; patn=str;
	fail[0] = fail[1] = 0;
	for(int i=1; i<plen; i++)
	{
		int fp = fail[i];
		while(fp && patn[fp] != patn[i]) fp=fail[fp];
		if(patn[fp] == patn[i]) fail[i+1] = fp+1;
		else fail[i+1] = 0;
	}
}

void KMP::match(char str[], int len)
{
	int np=0,res=0;
	for(int i=0; i<len; i++)
	{
		while(np && patn[np] != str[i]) np = fail[np];
		if(patn[np] == str[i]) np++;
		if(np==plen)
		{
			if(i == plen-1) m0++;
			else m1++;
			np = fail[np];
		}
	}
}

LL Pow(LL x, LL n, LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=res*x%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}
