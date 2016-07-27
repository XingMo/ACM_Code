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
typedef pair<long long,long long> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))

const int maxn=1e3+10;
const int MOD=1e9+7;
LL GCD(LL a, LL b){return b?GCD(b,a%b):a;}

struct Vector
{
	LL x,y,v,id;
	Vector(LL _x=0, LL _y=0, LL _v=0){x=_x; y=_y; v=_v;}
	int read(){return scanf("%lld%lld", &x, &y);}
	int pri(){return printf("x:%lld y:%lld v:%lld\n", x, y, v);}
};
typedef Vector Point;
struct data
{
	LL A,B,C;
	Point u, v;
	data(){};
	bool operator < (const data &v) const
	{
		if(A != v.A) return A < v.A;
		if(B != v.B) return B < v.B;
		return C < v.C;
		return 0;
	}
	bool operator == (const data &v) const
	{
		if(A==v.A && B==v.B && C==v.C) return 1;
		return 0;
	}
	void init(Point _u, Point _v)
	{
		u=_u; v=_v;
		A=v.y-u.y;
		B=u.x-v.x;
		C=v.x*u.y-u.x*v.y;
		
		LL d = GCD(A,B);
		d = GCD(d,C);
		A/=d; B/=d; C/=d;
		if(A!=0)
		{
			if(A<0){A*=-1; B*=-1; C*=-1;}
		}
		else if(B!=0)
		{
			if(B<0){B*=-1; C*=-1;}
		}
		return;
	}
	int pri(){return printf("%lld %lld %lld\n", A, B, C);}
};

int N;
map<Pii,int> vis;
Point pot[maxn];
data lines[maxn*maxn/2];
int have[maxn];
LL ans[maxn*maxn/2];
LL Pow(LL,LL);

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
		vis.clear();
		scanf("%d", &N);
		if(N==1) {Point x; x.read(); puts("0"); continue;}
		int id=0;
		for(int i=1; i<=N; i++)
		{
			Point x;
			x.read();
			Pii cor(x.x, x.y);
			if(vis.find(cor) == vis.end())
			{
				vis.insert(make_pair(cor,++id));
				x.id=id;
				pot[id] = x;
				pot[id].v = 1;
			}
			else
			{
				pot[ vis[cor] ].v++;
			}
		}
		
		int linec=0;
		for(int i=1; i<=id; i++)
		{
			for(int j=i+1; j<=id; j++)
			{
				data now;
				now.init(pot[i],pot[j]);
				lines[linec++] = now;
			}
		}
		
		LL res=0;
		sort(lines, lines+linec);
		CLR(have); CLR(ans);
		int nowline=1;
		data now=lines[0];
		for(int i=0; i<linec; i++)
		{
			if(!(now==lines[i]))
			{
				nowline++;
				now=lines[i];
			} 
			if(have[ lines[i].u.id ] != nowline)
			{
				have[ lines[i].u.id ]=nowline;
				ans[ nowline ] += lines[i].u.v;
				if(lines[i].u.v>1) res = (res-(Pow(2,lines[i].u.v)-1-lines[i].u.v)%MOD+MOD)%MOD;
			}
			if(have[ lines[i].v.id ] != nowline)
			{
				have[ lines[i].v.id ]=nowline;
				ans[ nowline ] += lines[i].v.v;
				if(lines[i].v.v>1) res = (res-(Pow(2,lines[i].v.v)-1-lines[i].v.v)%MOD+MOD)%MOD;
			}
//			lines[i].pri();
//			printf("debug: %d %lld\n", nowline, ans[nowline]);
		}
//		printf("%lld\n", res);
		for(int i=1; i<=id; i++) if(pot[i].v>1) res = (res+(Pow(2,pot[i].v)-1-pot[i].v)%MOD)%MOD;
		for(int i=1; i<=nowline; i++)
		{
			LL now = ans[i];
			res = (res+Pow(2,now)-1-now)%MOD;
		}
		//if(id<=1) res = (res+Pow(2,pot[1].v)-1-pot[1].v)%MOD;
		printf("%lld\n", (res+MOD)%MOD);
//		puts("-----------");
	}
	return 0;
}

LL Pow(LL x, LL n)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=x*res%MOD;
		x=x*x%MOD;
		n>>=1;
	}
	return res;
}

