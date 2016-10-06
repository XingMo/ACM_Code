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

const DBL eps = 1e-7;
int sgn(DBL x){return x>eps?1:(x<-eps?-1:0);}

struct Vector
{
	DBL x,y;
	Vector(DBL _x=0,DBL _y=0):x(_x),y(_y){};
	Vector operator + (const Vector &rhs) const {return Vector(x+rhs.x, y+rhs.y);}
	Vector operator - (const Vector &rhs) const {return Vector(x-rhs.x, y-rhs.y);}
	Vector operator * (const DBL &rhs) const {return Vector(x*rhs, y*rhs);}
	Vector operator / (const DBL &rhs) const {return Vector(x/rhs, y/rhs);}
	DBL operator * (const Vector &rhs) const {return x*rhs.x + y*rhs.y;}
	DBL operator ^ (const Vector &rhs) const {return x*rhs.y - y*rhs.x;}
	int read(){return scanf("%lf%lf", &x, &y);}
	int pri(){return printf(":%.2f %.2f\n", x, y);}
};
typedef Vector Point;

int N;
Point in[310];

DBL Vlen(Vector);
Vector Normal(Vector);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N) && N)
	{
		for(int i=0; i<N; i++) in[i].read();
		if(N==1){puts("1"); continue;}
		Vector v, o;
		DBL dist;
		int cnt, ans=0;
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++) if(j!=i && sgn(Vlen(in[i]-in[j])-2.0) < 0)
			{
				
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

DBL Vlen(Vector v)
{
	return sqrt(SQR(v.x) + SQR(v.y));
}
Vector Normal(Vector v)
{
	return Vector(-v.y, v.x);
}
