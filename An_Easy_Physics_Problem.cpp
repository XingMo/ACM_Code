/*
HDU - 5572
给定一个圆和圆外两个点 A和 B
现在有一个质点在 A处，有速度方向 V
其与圆的碰撞是弹性碰撞，问质点是否能经过 B

分情况讨论
1. 如果射线不与圆相交，直接判定点是否在射线上
2. 如果射线与圆相交，那么列方程解出与原交点
并得出反弹的法线方程，然后以法线方程作对称
最后判断点是否在一条线段和一条射线上

作对称的话可以将点 A以法线作对称，然后再用撞击点和对称点得到撞后轨迹
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

const DBL eps = 1e-8;
int sgn(DBL x){return x<-eps?-1:(x>eps?1:0);}
struct Vector
{
	DBL x, y;
	Vector(DBL _x=0, DBL _y=0):x(_x),y(_y){}
	Vector operator + (const Vector &rhs) const {return Vector(x+rhs.x, y+rhs.y);}
	Vector operator - (const Vector &rhs) const {return Vector(x-rhs.x, y-rhs.y);}
	Vector operator * (const DBL &rhs) const {return Vector(x*rhs, y*rhs);}
	Vector operator / (const DBL &rhs) const {return Vector(x/rhs, y/rhs);}
	DBL operator * (const Vector &rhs) const {return x*rhs.x + y*rhs.y;}
	DBL operator ^ (const Vector &rhs) const {return x*rhs.y - y*rhs.x;}
	int read(){return scanf("%lf%lf", &x, &y);}
	int pri(){cout << x << " " << y << endl; return 0;}
};
typedef Vector Point;
struct Line
{
	Vector u,v,s;
	Line(){}
	Line(Point _u, Point _v):u(_u),v(_v),s(_v-_u){}
};

struct Circle
{
	Point o; DBL r;
	Circle(){};
	void read(){o.read(); scanf("%lf", &r);}
};

int N;
Point A, B, V;
Circle O;

DBL Vlen(Vector);
Vector Normal(Vector);
Point SISC(Line,Circle);
bool PointOnHline(Point,Line);
bool PointOnSegment(Point,Line);
DBL PointToLine(Point,Line);

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
		O.read(); A.read(); V.read(); B.read();
		Line l1(A, A+V);
		DBL dist = PointToLine(O.o, l1);
		bool ok=0;
		if(sgn(dist-O.r)>=0 || sgn(V*(O.o-A))<=0) ok |= PointOnHline(B, l1);
		else
		{
			Line l2(O.o, SISC(l1,O));
			if(PointOnHline(O.o, l1)) ok |= PointOnHline(B, l2);
			else
			{
				Vector n = Normal(l2.s);
				if(sgn(n*V)<0) n=n*(-1);
				n = n/Vlen(n);
				ok |= PointOnSegment(B, Line(A, l2.v)) || PointOnHline(B, Line(l2.v, A+n*2*PointToLine(A, l2)));
			}
		}
		printf("Case #%d: %s\n", ck, ok?"Yes":"No");
	}
	return 0;
}

DBL Vlen(Vector v) { return sqrt(SQR(v.x) + SQR(v.y));}
Vector Normal(Vector v) {return Vector(-v.y, v.x);}

bool PointOnHline(Point p, Line l)
{
	Vector temp = p-l.u;
	return sgn(temp^l.s) == 0 && sgn(temp*l.s) >= 0;
}

bool PointOnSegment(Point p, Line l)
{
	return sgn( (l.u-p)^(l.v-p) )==0 && sgn( (l.u-p)*(l.v-p) )<=0;
}

DBL PointToLine(Point p, Line l)
{
	return abs((p-l.u)^l.s)/Vlen(l.s);
}

Point SISC(Line L, Circle C)
{
	Vector ou = L.u-C.o, s=L.s;
	DBL a = SQR(s.x) + SQR(s.y);
	DBL b = 2*(ou*s);
	DBL c = SQR(ou.x) + SQR(ou.y) - SQR(C.r);
	DBL d = b*b - 4*a*c;
	DBL t = (-b-sqrt(d))/(a+a);
	return L.u + s*t;
}
