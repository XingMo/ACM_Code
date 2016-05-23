/*
POJ - 1201
有数轴上的若干个区间，要求从数轴上选最少的点，
使得第 i个区间内至少有 c_i个点

对区间右端点排序，可以发现尽量选右边的点比较优
然后用树状数组维护一下区间内点的数量，
如果未达到要求，则从右端点开始向左选择未选择的数
由于选的数必然是连续的，所以可以记录一下某个选区的左端点位置
当碰到上一个选区的右端点时，直接跳过

时间复杂度 O(N*log(N))
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

const int maxn=5e4+10;
struct data
{
	int l,r,c;
	bool operator < (const data &v) const {return r < v.r;}
};
struct BIT
{
	int *bit, siz;
	BIT(int tsiz):siz(tsiz){bit=new int[tsiz+1];memset(bit,0,sizeof(int)*(tsiz+1));}
	~BIT(){delete []bit;}
	int lowbit(int x){return x&-x;}
	void add(int x, int v)
	{
		while(x<=siz)
		{
			bit[x]+=v;
			x+=lowbit(x);
		}
	}
	int sum(int x)
	{
		int res=0;
		while(x>0)
		{
			res+=bit[x];
			x-=lowbit(x);
		}
		return res;
	}
};
int N;
data inpt[maxn];
bool used[maxn];
int L[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		CLR(used); CLR(L);
		for(int i=0; i<N; i++) 
		{
			scanf("%d%d%d", &inpt[i].l, &inpt[i].r, &inpt[i].c);
			inpt[i].l++;
			inpt[i].r++;
		}
		sort(inpt, inpt+N);
		
		BIT bit(maxn);
		int ans=0;
		
		for(int i=0; i<N; i++)
		{
			int rem=inpt[i].c-(bit.sum(inpt[i].r)-bit.sum(inpt[i].l-1));
			if(rem<=0) continue;
			ans+=rem;
			int np=inpt[i].r;
			while(rem>0)
			{
				if(!used[np])
				{
					rem--;
					bit.add(np,1);
					used[np]=1;
				}
				else
				{
					np=L[np];
					continue;
				}
				np--;
			}
			L[inpt[i].r]=np;
		}
		
		printf("%d\n", ans);
	}
	return 0;
}

