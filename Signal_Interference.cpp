/*
HDU - 5130
求圆与简单多边形的面积交

从圆心将多边形剖分成若干个三角形
然后求每个三角形与圆的面积交
为了方便其间，先将多边形每条边与圆的交点加入多边形上
这样每条边与圆的关系只有两种，要么都在圆内，要么都在圆外
所以只要求相应的三角形与扇形面积即可
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

const DBL eps=1e-9, PI=acos(-1.0);
int sgn(DBL x){return x>eps?1:(x<-eps?-1:0);}

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
	void pri(){printf("%.3f %.3f\n", x, y);}
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
	Circle(){}
	Circle(Point _o, DBL _r):o(_o),r(_r){}
};

int N;
DBL K;
Point in[510], A, B, P[1510];

DBL Vlen(Vector);
DBL distPointToLine(Point,Line);
Vector Normal(Vector);
Point GetLineIntSec(Line,Line);
bool ifSegIntSecCircle(Line,Circle);
int SegIntSecCircle(Line,Circle,Point&,Point&);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int ck=0;
	while(~scanf("%d%lf", &N, &K))
	{
		ck++;
		for(int i=0; i<N; i++) in[i].read();
		in[N] = in[0];
		A.read(); B.read();
		
		DBL temp[4];
		temp[0] = (B.x-K*K*A.x)/(1-K*K);
		temp[1] = (B.y-K*K*A.y)/(1-K*K);
		temp[2] = (SQR(B.x)-SQR(K*A.x))/(1-K*K);
		temp[3] = (SQR(B.y)-SQR(K*A.y))/(1-K*K);
		Circle C( Point(temp[0],temp[1]), sqrt(SQR(temp[0])-temp[2]+SQR(temp[1])-temp[3]));
		
		int cnt=0;
		Point x,y;
		for(int i=0; i<N; i++)
		{
			Line L(in[i], in[i+1]);
			P[cnt++] = in[i];
			if(ifSegIntSecCircle(L,C))
			{
				int stat = SegIntSecCircle(L,C,x,y);
				if(stat & 1) P[cnt++] = x;
				if(stat & 2) P[cnt++] = y;
			}
		}
		
		DBL ans=0;
		P[cnt] = P[0];
		for(int i=0; i<cnt; i++)
		{
			x=P[i]-C.o, y=P[i+1]-C.o;
			if( sgn(Vlen(x)-C.r) > 0 || sgn(Vlen(y)-C.r) > 0 ) 
			{
				DBL ang = acos( (x*y)/(Vlen(x)*Vlen(y)) );
				ans += sgn(x^y)*C.r*acos((x*y)/Vlen(x)/Vlen(y))*C.r*0.5;
			}
			else ans += 0.5*(x^y);
		}
		printf("Case %d: %.7f\n", ck, abs(ans));
	}
	return 0;
}

DBL Vlen(Vector v)
{
	return sqrt(SQR(v.x) + SQR(v.y));
}

DBL distPointToLine(Point P, Line L)
{
	return abs((P-L.u)^L.s)/Vlen(L.s);
}

Vector Normal(Vector vec)
{
	return Vector(-vec.y, vec.x);
}

Point GetLineIntSec(Line l1, Line l2)
{
	DBL a = (l1.v-l1.u)^(l2.u-l1.u), b = (l1.u-l1.v)^(l2.v-l1.v);
	if(sgn(a+b)==0) return Point(1e9,1e9);
	return Point((l2.u.x * b + l2.v.x * a) / (a + b), (l2.u.y * b + l2.v.y * a) / (a + b));
}

bool ifSegIntSecCircle(Line L, Circle C)
{
	DBL t1 = Vlen(L.u-C.o)-C.r, t2 = Vlen(L.v-C.o)-C.r;
	if(sgn(t1)<=0 || sgn(t2)<=0) return sgn(t1)>=0 || sgn(t2)>=0;
	Point t = C.o + Normal(L.v-L.u);
	return sgn( ((L.u-t)^(C.o-t))*((L.v-t)^(C.o-t)) ) <=0 && sgn( distPointToLine(C.o, L) - C.r)<=0;
}

int SegIntSecCircle(Line L, Circle C, Point &x, Point &y)
{
	Point p = C.o + Normal(L.s);
	p = GetLineIntSec(Line(p,C.o), L);
	DBL t = sqrt(SQR(C.r) - SQR(Vlen(C.o-p))) / Vlen(L.s);
	int cnt=0;
	x = p + L.s*t, y = p - L.s*t;
	if(sgn(Vlen(x-L.u)-Vlen(y-L.u))>0) swap(x,y);
	if(sgn( (L.u-x)*(L.v-x) ) <= 0) cnt |= 1;
	if(sgn( (L.u-y)*(L.v-y) ) <= 0) cnt |= 2; 
	return cnt;
}
