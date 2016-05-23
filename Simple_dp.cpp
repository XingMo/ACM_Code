/*
SCU - 4514
给定 N个点，每个点的权值表示以此点为根的子树中节点的个数
每个非叶子节点至少有两个儿子，问给定的 N个点能否组成满足条件的树

这题我是贪心构造，虽然正确性无法保证
但由于N比较小，最多24，所以难以构造数据把我卡掉

先将点从小到大排序，然后从大到小选择根
然后在小于它的为标记的点中选择它的儿子，
保证儿子的权值尽可能大，然后打上标记
然后依次循环，如果中间某点为根无法构造出子树，则返回

以上方法并不能够通过，这是因为这个办法是错误的
但是可以反过来做，也就是说从小到大选择根
然后在小于它的为标记的点中选择它的儿子，其余操作基本相同

以上方法依旧不可能通过，但是如果你两种贪心顺序都判一下
如果两个顺序都无解，就输出无解，否则输出有解，就能够得到 AC
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

int N;
int nval[30];
bool ban[30];

int check1();
int check2();

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
		scanf("%d", &N);
		for(int i=1; i<=N; i++) scanf("%d", &nval[i]);
		sort(nval+1,nval+1+N);

		if(check1()||check2()) puts("YES");
		else puts("NO");
	}
	return 0;
}

int check1()
{
	CLR(ban);
	ban[N]=1;
	for(int i=N; i>0; i--)
	{
		if(!ban[i]) return 0;
		if(nval[i]==1) continue;
		
		int val=nval[i]-1, cnt=0;
		for(int j=i-1; j>0; j--)
		{
			if(ban[j] || val < nval[j]) continue;
			val-=nval[j];
			ban[j]=1;
			cnt++;
		}
		if(cnt<2 || val!=0) return 0;
	}
	
	return 1;
}

int check2()
{
	CLR(ban);
	for(int i=1; i<=N; i++)
	{
		if(nval[i]==1) continue;
		
		int val=nval[i]-1, cnt=0;
		//printf("%d: \n", nval[i]);
		for(int j=i-1; j>0; j--)
		{
			if(!cnt && val==nval[j]) continue;
			if(ban[j] || val < nval[j]) continue;
			val-=nval[j];
			ban[j]=1;
			cnt++;
			//printf("ban: %d\n", nval[j]);
		}
		if(cnt<2 || val!=0) return 0;
	}
	ban[N]=1;
	for(int i=1; i<=N; i++) if(!ban[i]) return 0;
	return 1;
}

