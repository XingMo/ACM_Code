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

const DBL eps = 1e-12;
int sgn(DBL x){return x>eps? 1 : ( x<-eps? -1 : 0 );}
struct Vector
{
	DBL x,y;
	Vector(DBL tx=0, DBL ty=0):x(tx),y(ty){};
	Vector operator + (const Vector &v){return Vector(x+v.x, y+v.y);}
	Vector operator - (const Vector &v){return Vector(x-v.x, y-v.y);}
	Vector operator * (DBL v) {return Vector(x*v, y*v);}
	Vector operator / (DBL v) {return Vector(x/v, y/v);}
	double operator * (const Vector &v){return x*v.x + y*v.y;}
	double operator ^ (const Vector &v){return x*v.y - y*v.x;}
	int read(){return scanf("%lf%lf", &x, &y);}
	int pri(){return printf("%.2f %.2f\n", x, y);}
};
typedef Vector Point;
struct Line
{
	Vector u,v,s;
	Line(){};
	Line(Point tu, Point tv):u(tu),v(tv),s(tv-tu){};
	void pri(){u.pri(); v.pri();}
};
struct Polygon
{
	int siz;
	vector<Point> cor;
	void init(){cor.clear(); siz=0;}
	void add(Point p){cor.push_back(p); siz=cor.size();}
};

Point GetLineIntSec(Line&,Line&);
int PointInPolygon(Point& , Polygon&);
int PointOnSeg(Point&, Line&);
int ConvexHull(int,Point*, Point*);
DBL area2(int,Point*);

Polygon S,T;
Point P[20], res[20];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int x[10], y[10];
	while(~scanf("%d%d%d%d", &x[1], &y[1], &x[2], &y[2]))
	{
		S.init(); T.init();
		
		T.add( Point(x[1], y[1]) );
		T.add( Point(x[1], y[2]) );
		T.add( Point(x[2], y[1]) );
		scanf("%d%d%d%d", &x[3], &y[3], &x[4], &y[4]);
		S.add( Point(x[3], y[3]) );
		S.add( Point(x[3], y[4]) );
		S.add( Point(x[4], y[4]) );
		S.add( Point(x[4], y[3]) );
		
		int pcnt=0,rcnt;
		for(int i=0; i<T.siz; i++) if(PointInPolygon(T.cor[i], S)) P[pcnt++] = T.cor[i];
		for(int i=0; i<S.siz; i++) if(PointInPolygon(S.cor[i], T)) P[pcnt++] = S.cor[i];
		for(int i=0; i<T.siz; i++)
		{
			Line l1 = Line(T.cor[i], T.cor[(i+1)%T.siz]);
			for(int j=0; j<S.siz; j++)
			{
				Line l2 = Line(S.cor[j], S.cor[(j+1)%S.siz]);
				Point np = GetLineIntSec(l1,l2);
				if(sgn(np.x)>=0 && sgn(np.y)>=0)
				{
					P[pcnt++] = np;
//					l1.pri(); l2.pri();
//					np.pri();
//					puts("---");
				}
			}
		}
//		printf("%d\n", pcnt);
//		for(int i=0; i<pcnt; i++) P[i].pri();
		
		rcnt = ConvexHull(pcnt,P, res);
//		printf("%d\n", rcnt);
//		for(int i=0; i<rcnt; i++) res[i].pri();
		printf("%.10f\n", area2(rcnt, res) );
//		PCUT;
	}
	return 0;
}

Point GetLineIntSec(Line &u, Line &v)
{
	if(!sgn(u.s^v.s)) return Point(-1,-1);
	Vector tv = u.u-v.u;
	DBL k = (v.s^tv)/(u.s^v.s);
	Point p = u.u + u.s*k;
	if(PointOnSeg(p,u) && PointOnSeg(p,v)) return p;
	else return Point(-1,-1);
}

int PointOnSeg(Point &p, Line &l)
{
	return sgn( (l.u-p)^(l.v-p) )==0 && sgn( (l.u-p)*(l.v-p) )<=0;
}

int PointInPolygon(Point &np, Polygon &poly)
{
	int cnt1=0, cnt2=0;
	for(int i=0; i<poly.siz; i++)
	{
		Vector s = np-poly.cor[i];
		Vector v = poly.cor[(i+1)%poly.siz] - poly.cor[i];
		DBL res = (s^v);
		if(sgn(res)<=0) cnt1++;
		if(sgn(res)>=0) cnt2++;
	}
	if(cnt1==poly.siz || cnt2==poly.siz) return 1;
	return 0;
}

bool chcmp(Point u, Point v) {if(!sgn(u.x-v.x)) return u.y<v.y; return u.x<v.x;}
int ConvexHull(int pn, Point p[], Point res[])
{
	sort(p, p+pn, chcmp);
	int bp=0,mid;
	for(int i=0; i<pn; i++)
	{
		while( bp>1 && sgn( (res[bp-1]-res[bp-2])^(p[i]-res[bp-2]) )<=0 ) bp--;
		res[bp++] = p[i];
	}
	mid = bp;
	for(int i=pn-2; i>=0; i--)
	{
		while( bp>mid && sgn( (res[bp-1]-res[bp-2])^(p[i]-res[bp-2]) )<=0 ) bp--;
		res[bp++] = p[i];
	}
	if(pn>1) bp--;
	return bp;
}

DBL area2(int siz, Point p[])
{
	DBL res=0;
	for(int i=1; i<siz; i++) res += (p[i-1]^p[i]);
	res += (p[siz-1]^p[0]);
	return res*0.5;
}
