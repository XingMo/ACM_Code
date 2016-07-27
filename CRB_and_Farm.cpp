/*
HDU - 5408
给定一个N个点的凸包，凸包内有 K个点
求问是否能从凸包上选择不超过 2*K个点
使得他们连成的凸包能完全包住这 K个点
如果能，则逆时针输出构造凸包的顶点编号

对内部的 K个点求一次凸包，此内凸包顶点不超过 K
问题就转化为求一个凸包包裹内部的凸包
将 K个点组成的内凸包的每个顶点投射到外凸包上
投影点连成的凸包必定包裹内凸包
选择投影点所在线段的两个端点，作为构造凸包的顶点
构造凸包必定包裹投影凸包，从而包裹内凸包
并且选择的点数不会超过 2*K

所以一定能构造出符合要求的凸包
具体构造方式就是在内凸包内部任意取一个点 O，然后对所有内凸包的顶点 A_i
作射线 OA_i，把交外凸包的线段端点记录下来即可
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int maxn=2e5+10;
const DBL eps=1e-9;
int sgn(DBL x){return x>eps? 1: (x<-eps? -1: 0);}

struct Vector
{
	int id;
	DBL x,y;
	Vector(DBL _x=0, DBL _y=0){x=_x; y=_y;}
	Vector operator - (const Vector &v) const {return Vector(x-v.x,y-v.y);}
	DBL operator * (const Vector &v) const {return x*v.x+y*v.y;}
	DBL operator ^ (const Vector &v){return x*v.y-y*v.x;}
	
	bool operator < (const Vector &v) const {return id < v.id;}
	bool operator == (const Vector &v) const {return id==v.id;}
	void read(int _id){id=_id; scanf("%lf%lf", &x, &y);}
	void pri(){printf("%d %.2f %.2f\n", id, x, y);}
};
typedef Vector Point;
struct Segment
{
	Point u,v;
	Segment(){};
	Segment(Point _u, Point _v){u=_u; v=_v;}
};
int N,K;
Point poly[maxn], barns[maxn], inner[maxn];
Segment Seg[maxn];

int ConvexHull(int, Point*, Point*);
bool InterSection(Segment,Point,Point);

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
		int edge=0;
		scanf("%d", &N);
		for(int i=0; i<N; i++)
		{
			poly[i].read(i+1);
			if(i) Seg[edge++] = Segment(poly[i-1], poly[i]);
		}
		Seg[edge++] = Segment(poly[0], poly[N-1]);

		scanf("%d", &K);
		for(int i=0; i<K; i++) barns[i].read(i);
		int siz=ConvexHull(K, barns, inner);
		
		Point o=inner[0];
		for(int i=1; i<siz; i++) o.x=(o.x+inner[i].x)/2, o.y=(o.y+inner[i].y)/2;
//		o.x = (inner[0].x + inner[1].x)/2;
//		o.y = (inner[0].y + inner[1].y)/2;
//		o.x = (o.x + inner[2].x)/2;
//		o.y = (o.y + inner[2].y)/2;
		
		int np=0;
		vector<Point> res;
		for(int i=0; i<siz; i++)
		{
			while(!InterSection(Seg[np], o, inner[i])) np=(np+1)%edge;
			res.push_back(Seg[np].u);
			res.push_back(Seg[np].v);
		}
		sort(res.begin(),res.end());
		siz=unique(res.begin(), res.end())-res.begin();
		puts("Yes");
		printf("%d\n", siz);
		for(int i=0; i<siz; i++) printf("%d ", res[i].id);
		puts("");
	}
	return 0;
}

bool InterSection(Segment l, Point o, Point t)
{
	DBL v0=(t-o)^(l.u-o), v1=(t-l.u)^(l.v-l.u), v2=(t-l.v)^(o-l.v);
	if(sgn(v0)<0 && sgn(v1)<0 && sgn(v2)<0) return 1;
	if(sgn(v0)>0 && sgn(v1)>0 && sgn(v2)>0) return 1;
	return 0;
}

bool chcmp(Point u, Point v){if(!sgn(u.x-v.x))return u.y<v.y;return u.x<v.x;}
int ConvexHull(int pn, Point *p, Point *res)
{
	sort(p,p+pn,chcmp);
	int bp=0,mid;
	for(int i=0; i<pn; i++)
	{
		while( bp>1 && sgn( (res[bp-1]-res[bp-2])^(p[i]-res[bp-2]) )<=0) bp--;
		res[bp++]=p[i];
	}
	mid=bp;
	for(int i=pn-2; i>=0; i--)
	{
		while( bp>mid && sgn( (res[bp-1]-res[bp-2])^(p[i]-res[bp-2]) )<=0) bp--;
		res[bp++]=p[i];
	}
	if(pn>1) bp--;
	return bp;
}

