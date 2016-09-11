/*
Codeforces - 166B
判断任意多边形 B是否严格在凸多边形 A内部

点在凸多边形内部试板题
如果 B的所有顶点在 A内，则 B在 A内
由于 A的顶点有 1e5个，B的顶点有 1e4个
所以不能用 O(n)的暴力判断
有一个 O(logn)的二分做法
基本原理是用对角线将凸多边形剖成以 cor[0]为公共顶点的若干个三角形
然后二分出点 p在哪两条对角线中，最后再用这个三角形的第三条边判断是否在三角形内
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

const DBL eps = 1e-11;
int sgn(DBL x){return x>eps?1:(x<-eps?-1:0);}
struct Vector
{
	DBL x,y;
	Vector(DBL _x=0, DBL _y=0):x(_x),y(_y){}
	Vector operator + (const Vector &rhs) const {return Vector(x+rhs.x, y+rhs.y);}
	Vector operator - (const Vector &rhs) const {return Vector(x-rhs.x, y-rhs.y);}
	Vector operator * (const DBL &rhs) const {return Vector(x*rhs, y*rhs);}
	Vector operator / (const DBL &rhs) const {return Vector(x/rhs, y/rhs);}
	DBL operator * (const Vector &rhs) const {return x*rhs.x + y*rhs.y;}
	DBL operator ^ (const Vector &rhs) const {return x*rhs.y - rhs.x*y;}
	int read(){return scanf("%lf%lf", &x, &y);}
	int pri(){return printf("P:%.2f %.2f\n", x, y);}
};
typedef Vector Point;

struct Polygon
{
	int siz;
	vector<Point> cor;
	vector<Vector> tx;
	void init(){cor.clear(); tx.clear(); siz=0;}
	void read(int _n)
	{
		siz=_n;
		cor.resize(siz);
		for(int i=0; i<siz; i++)
		{
			cor[i].read();
			tx.push_back(cor[i]-cor[0]);
		}
	}
};

int N;
Polygon A;

bool PointInPolygon(Point&,Polygon&);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		A.init(); A.read(N);
		scanf("%d", &N);
		Point tem;
		bool ok=1;
		for(int i=0; i<N; i++)
		{
			tem.read();
			ok &= PointInPolygon(tem, A);
		}
		puts(ok?"YES":"NO");
	}
	return 0;
}

bool PointInPolygon(Point &p, Polygon &poly)
{
	if(poly.siz<3) return 0;
	Vector tp = p-poly.cor[0];
	if(sgn(tp^poly.tx[1]) <= 0) return 0;
	if(sgn(tp^poly.tx[poly.siz-1]) >= 0) return 0;
	
	int l=1,r=poly.siz-2,mid;
	while(l<r)
	{
		mid = (l+r+1)>>1;
		if(sgn(tp^poly.tx[mid]) >= 0) l = mid;
		else r = mid-1;
	}
	return sgn((p-poly.cor[l])^(poly.cor[l+1]-poly.cor[l])) > 0;
}
