/*
HDU - 5738
集合的定义可以转化为
集合内点均在一条直线上
问满足条件集合的个数

貌似出题人很不厚道地卡了常数
原来赛上写的小常数 O(N^2logN)赛后过不了了
于是我又找人学习了一个常数更小的 O(N^2logN)

首先把所有重复位置的点缩起来
枚举一个点 i作为线段的一端，再枚举另外一个点 j形成一条射线
计算斜率，存到map里，然后统计答案

统计的方式是，对于每一条射线，i作为一端，射线上的其他点为另一端
设 i处有 x个点，射线上其他点有 y个，
则记入 i处至少选一个点，其他点至少选一个的答案 (2^x-1)*(2^y-1)
每个方案正好被计算了两次，所以最后除以 2
最后再记入重叠点内部自选的方案数
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

const int maxn=1e3+10;
const int MOD=1e9+7, inv2=500000004;
int GCD(int a,int b){return b?GCD(b,a%b):a;}
struct Vector
{
	int x,y,v;
	Vector(int _x=0, int _y=0, int _v=0){x=_x; y=_y; v=_v;}
	int read(){return scanf("%d%d", &x, &y);}
	int pri(){return printf("x:%d y:%d\n", x, y);}
};
typedef Vector Point;

int N;
map<Pii,int> vis;
Point pot[maxn];
LL pow2[maxn];

Pii calc(const Point&,const Point&);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	pow2[0]=1;
	for(int i=1; i<maxn; i++) pow2[i] = (pow2[i-1]<<1)%MOD;
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		vis.clear();
		scanf("%d", &N);
		Point x;
		if(N==1){x.read(); puts("0"); continue;}
		int ndn=0;
		for(int i=1; i<=N; i++)
		{
			x.read();
			auto it=vis.find(Pii(x.x, x.y));
			if(it != vis.end())
			{
				pot[it->second].v++;
			}
			else
			{
				x.v=1;
				vis.insert( make_pair(Pii(x.x,x.y), ++ndn) );
				pot[ndn]=x;
			}
		}
		
		LL ans=0;
		for(int i=1; i<=ndn; i++)
		{
			map<Pii,int> cnt;
			for(int j=1; j<=ndn; j++)
			{
				if(i==j) continue;
				Pii k = calc(pot[i],pot[j]);
				cnt[k] += pot[j].v;
			}
			for(auto &pr:cnt) ans = (ans + (pow2[ pot[i].v ]-1)*(pow2[ pr.second ]-1)%MOD )%MOD;
		}
		ans = ans*inv2%MOD;
		for(int i=1; i<=ndn; i++) ans = (ans + pow2[pot[i].v]-1-pot[i].v)%MOD;
		printf("%lld\n", (ans+MOD)%MOD);
	}
	return 0;
}

Pii calc(const Point &a, const Point &b)
{
	int dx=a.x-b.x, dy=a.y-b.y, d=GCD(dx,dy);
	d=abs(d);
	dx/=d; dy/=d;
	return Pii(dx,dy);
}
