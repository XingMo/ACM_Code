/*
HDU - 5784
几何题，给定平面上若干个不重复的点，
求这些点能组成多少个锐角三角形

我刚开始的时候想的是枚举钝角和直角
然后计算每三个点能组成的三角形的个数
减去共线的，再减去钝角和直角的个数，即为答案
而且我在极角排序之后，我试图用二分来确定上下界
这样也不是不能做，但是比较麻烦

题解的方法就比较好
统计锐角的个数，设为 A，钝角和直角的个数，设为 B
每个锐角三角形有三个锐角，每个钝角和直角三角形均贡献两个锐角
所以答案即为 (A-2B)/3
然后题解在对每个点极角排序之后，采用 two pointers的方式来找上下界
比二分好写多了，也很方便，时间复杂度 O(N^2logN)

统计锐角个数的时候，要考虑和当前枚举的点共线的那些点
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

const DBL eps=1e-12, PI=acos(-1.0);
const int maxn=2e3+10;
int sgn(DBL x){return x>eps?1:(x<-eps?(-1):0);}
struct Vector
{
	DBL x,y;
	Vector operator - (const Vector &v) const {return {x-v.x, y-v.y};}
	DBL operator * (const Vector &v) const {return x*v.x + y*v.y;}
	int read() {return scanf("%lf%lf", &x, &y);}
};
typedef Vector Point;

int N;
Point P[maxn];
DBL ang[2*maxn];

int Cnt(DBL);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	printf("%.12f\n", atan2(1,1e9));
	while(~scanf("%d", &N))
	{
		for(int i=0; i<N; i++) P[i].read();
		LL ans = 0, nans=0;
		for(int i=0; i<N; i++)
		{
			Vector L;
			for(int j=i+1; j<i+N; j++)
			{
				int id=j%N;
				L = P[id]-P[i];
				ang[j-i-1] = atan2(L.y, L.x);
			}
			sort(ang, ang+N-1);
			memcpy(ang+N-1, ang, sizeof(DBL)*(N-1));
			for(int j=N-1; j<2*N-2; j++) ang[j] += 2.0*PI;
			int res = Cnt(PI*0.5);
			ans += res;
			nans += Cnt(PI) - res;
		}
		printf("%lld\n", (ans-2*nans)/3);
	}
	return 0;
}

int Cnt(DBL A)
{
	int r=0, res=0;
	for(int l=0; l<N-1; l++)
	{
		int ecnt=0;
		while( sgn(ang[l+ecnt]-ang[l]) == 0) ecnt++;
		l = l+ecnt-1;
		r = max(r, l+1);
		while( r-l+1 <= N-1 && sgn(ang[r]-ang[l] - A) < 0) r++;
		res += (r-l-1)*ecnt;
	}
	return res;
}
