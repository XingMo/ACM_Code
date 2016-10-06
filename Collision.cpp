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

const DBL eps= 1e-8, PI=acos(-1.0);
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
	DBL operator ^ (const Vector &rhs) const {return x*rhs.y - y*rhs.x;}
	
	int read(){return scanf("%lf%lf", &x, &y);}
	void pri(){printf("%.4f %.4f\n", x, y);}
};
typedef Vector Point;
struct Line
{
	Vector u,v,s;
	Line(){};
	Line(Point _u, Point _v):u(_u),v(_v),s(_v-_u){}
};
struct Circle
{
	Point o; DBL r;
	Circle(){}
	Circle(Point _o, DBL _r):o(_o),r(_r){}
};

Circle C1, C2;
Vector P, V;

DBL Vlen(Vector);
Vector Normal(Vector);
DBL distPointToLine(Point, Line);
Point GetLineIntSec(Line, Line);
int HLineIntSecCircle(Line, Circle, Point&, Point&);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	C1.o = C2.o = Point(0,0);
	DBL R;
	while(~scanf("%lf%lf%lf", &C1.r, &C2.r, &R))
	{
		C1.r += R; C2.r += R;
		P.read(); V.read();
		Line L(P, P+V);
		Point x,y,z,w;
		DBL ans=0;
		
		if(sgn(distPointToLine(C1.o, L) - C1.r) >= 0)
		{
			if(sgn(distPointToLine(C2.o,L) - C2.r) < 0)
			{
				int stat = HLineIntSecCircle(L, C2, x, y);
				if(stat) ans += Vlen(y-x);
				
			}
		}
		else
		{
			int stat = HLineIntSecCircle(L, C1, x, y);
			if(stat)
			{
				Vector Nor = Normal(x)/Vlen(x)*distPointToLine(P, Line(C1.o, x));
				if(sgn(V*Nor) < 0) Nor = Nor*(-1);
				y = P + Nor*2;
				if(HLineIntSecCircle(Line(x,y), C2, z, w) == 1) ans += Vlen(z-x);
				else ans += Vlen(w-x);
				if(HLineIntSecCircle(Line(x,P), C2, z, w) == 1) ans += Vlen(z-x);
				else ans += Vlen(w-x);
			}
		}
		printf("%.4f\n", ans/Vlen(V));
	}
	return 0;
}

DBL Vlen(Vector vec)
{
	return sqrt(SQR(vec.x) + SQR(vec.y));
}

Vector Normal(Vector vec)
{
	return Vector(-vec.y, vec.x);
}

DBL distPointToLine(Point P, Line L)
{
	return abs((P-L.u)^L.s)/Vlen(L.s);
}

Point GetLineIntSec(Line l1, Line l2)
{
	DBL a = (l1.v-l1.u)^(l2.u-l1.u), b = (l1.u-l1.v)^(l2.v-l1.v);
	return Point( (l2.u.x*b + l2.v.x*a)/(a+b), (l2.u.y*b + l2.v.y*a)/(a+b) );
}

int HLineIntSecCircle(Line L, Circle C, Point &p1, Point &p2)
{
	Point p = C.o + Normal(L.s);
	p = GetLineIntSec(Line(p,C.o), L);
	DBL t = sqrt( SQR(C.r) - SQR(Vlen(C.o-p)) ) / Vlen(L.s);
	p1 = p + L.s*t; p2 = p - L.s*t;
	
	int stat = 0;
	if(sgn(Vlen(p1-L.u) - Vlen(p2-L.u)) > 0) swap(p1, p2);
	if(sgn(L.s*(p1-L.u)) > 0) stat |= 1;
	if(sgn(L.s*(p2-L.u)) > 0) stat |= 2;
	return stat;
}

