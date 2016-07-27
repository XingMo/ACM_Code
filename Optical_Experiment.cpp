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

const int maxn=1e6+10;
struct BIT
{
	int bit[maxn],siz;
	void init(int _n){siz=_n; CLR(bit);}
	void add(int p, int x){for(int i=p; i<=siz; i+=i&-i) bit[i] = max(bit[i], x);}
	int sum(int p){int res=0; for(int i=p; i>0; i-=i&-i) res = max(bit[i], res); return res;}
};
int N;
int inpt[maxn];
int pos[maxn];
BIT bit;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d", &N);
	bit.init(N);
	for(int i=1; i<=N; i++) scanf("%d", &inpt[i]), pos[inpt[i]] = i;
	int ans=0;
	for(int i=1; i<=N; i++)
	{
		int x;
		scanf("%d", &x);
		int nxt = pos[x];
		int sum = bit.sum(N-nxt+1) + 1;
		ans = max(sum, ans);
		bit.add(N-nxt+1, sum);
//		printf("pos:%d ans:%d sum:%d\n", pos[x], ans, sum);
//		for(int i=1; i<=N; i++) printf("%d ", bit.sum(i)); puts("");
	}
	printf("%d\n", ans);
	return 0;
}

