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

struct Point
{
	int x,y;
	int read(){return scanf("%d%d", &x, &y);}
	void pri(){printf("%d %d\n", x, y);}
};

int N;
Point P[40];
bool Map[210][210];
Point T[2][5];

bool cons(int,int,Point*);
bool intsec(Point,Point,Point,Point);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N) && N)
	{
		CLR(Map);
		int ans = -1;
		for(int i=0; i<N; i++) P[i].read(), Map[P[i].x][P[i].y] = 1;
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) for(int k=0; k<N; k++) for(int l=0; l<N; l++)
		{
			if(P[i].x == P[j].x || P[i].y == P[j].y) continue;
			if(P[k].x == P[l].x || P[k].y == P[l].y) continue;
			if( !cons(i,j,T[0]) ) continue;
			if( !cons(k,l,T[1]) ) continue;
			
			bool ok=1;
			for(int a=0; a<4 && ok; a++) for(int b=0; b<4 && ok; b++) 
				if( intsec(T[0][a], T[0][a+1], T[1][b], T[1][b+1]) ) ok=0;
			if(!ok) continue;
			
			int temp = abs(P[i].x-P[j].x)*abs(P[i].y-P[j].y) + abs(P[k].x-P[l].x)*abs(P[k].y-P[l].y);
			
			ok = 1;
			int x1, x2, y1, y2;
			x1=T[0][0].x, x2=T[0][2].x, y1=T[0][0].y, y2=T[0][2].y;
			for(int i=0; i<4 && ok; i++) ok &= x1<T[1][i].x && T[1][i].x<x2 && y1<T[1][i].y && T[1][i].y<y2;
			if(ok) temp -= temp - (x2-x1)*(y2-y1);
			
			ok = 1;
			x1=T[1][0].x, x2=T[1][2].x, y1=T[1][0].y, y2=T[1][2].y;
			for(int i=0; i<4 && ok; i++) ok &= x1<T[0][i].x && T[0][i].x<x2 && y1<T[0][i].y && T[0][i].y<y2;
			if(ok) temp -= temp - (x2-x1)*(y2-y1);
			
			ans = max(ans, temp);
 		}
 		if(~ans) printf("%d\n", ans);
 		else puts("imp");
	}
	return 0;
}

bool cons(int i, int j, Point T[])
{
	int x1=P[i].x, x2=P[j].x, y1=P[i].y, y2=P[j].y;
	if(!Map[x1][y1] || !Map[x1][y2] || !Map[x2][y1] || !Map[x2][y2]) return 0;
	if(x1 > x2) swap(x1, x2);
	if(y1 > y2) swap(y1, y2);
	T[0] = {x1,y1};
	T[1] = {x2,y1};
	T[2] = {x2,y2};
	T[3] = {x1,y2};
	T[4] = T[0];
	return 1;
}

bool intsec(Point a, Point b, Point c, Point d)
{
	bool st0, st1;
	if(a.x==b.x) st0=0;
	else st0=1;
	if(c.x==d.x) st1=0;
	else st1=1;
	if(a.x > b.x || a.y > b.y) swap(a,b);
	if(c.x > d.x || c.y > d.y) swap(c,d);
	if(st0==st1 && st0==0)
	{
		if(a.x != c.x) return 0;
		if(a.y > c.y) swap(a,c), swap(b,d);
		return c.y <= b.y;
	}
	else if(st0==st1 && st0==1)
	{
		if(a.y != c.y) return 0;
		if(a.x > c.x) swap(a,c), swap(b,d);
		return c.x <= b.x;
	}
	else 
	{
		if(st0 > st1) swap(a,c), swap(b,d);
		return a.y<=c.y && b.y>=c.y && c.x<=a.x && d.x>=a.x;
	}
}

