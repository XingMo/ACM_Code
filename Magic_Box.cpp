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
#define PCUT puts("\n----------")

const DBL eps=1e-8;
int sgn(DBL x){return x<-eps?-1:(x>eps?1:0);}
struct Vector
{
	DBL x,y,z;
	Vector operator - (const Vector &v) {return {x-v.x, y-v.y, z-v.z};}
	DBL length(){return sqrt(SQR(x)+SQR(y)+SQR(z));}
	int read(){return scanf("%lf%lf%lf", &x, &y, &z);}
};
typedef Vector Point;
Point chr, vct;
Point pos[6];
int num[6];
DBL dist[6];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~chr.read())
	{
		vct.read();
		for(int i=0; i<6; i++) scanf("%d", &num[i]);
		pos[0] = {vct.x/2, 0.0, vct.z/2};
		pos[1] = {vct.x/2, vct.y, vct.z/2};
		pos[2] = {vct.x/2, vct.y/2, 0.0};
		pos[3] = {vct.x/2, vct.y/2, vct.z};
		pos[4] = {0.0, vct.y/2, vct.z/2};
		pos[5] = {vct.x, vct.y/2, vct.z/2};
		int ans=0;
		for(int i=0; i<6; i+=2)
		{
			Vector x=chr-pos[i], y=chr-pos[i+1];
			DBL dx = x.length();
			DBL dy = y.length();
			if(sgn(dx-dy) > 0) ans += num[i+1];
			if(sgn(dx-dy) < 0 && ) ans += num[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}

