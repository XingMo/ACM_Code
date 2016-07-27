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
#define SQR(a) ((a)*(a))

const DBL eps=1e-7;
int sgn(DBL x)
{
	if(abs(x)<eps) return 0;
	if(x>eps) return 1;
	return -1;
}

struct Vector
{
	DBL x,y,z;
	Vector(DBL _x=0, DBL _y=0, DBL _z=0){x=_x;y=_y;z=_z;}
	Vector operator - (const Vector &rhs) const {return Vector(x-rhs.x, y-rhs.y, z-rhs.z);}
	DBL    operator * (const Vector &rhs) const {return x*rhs.x + y*rhs.y + z*rhs.z;}
	Vector operator ^ (const Vector &rhs) const {return Vector(y*rhs.z-z*rhs.y, z*rhs.x-x*rhs.z, x*rhs.y-y*rhs.x);}
	
	DBL length(){return sqrt( SQR(x)+SQR(y)+SQR(z) );}
	int read(){return scanf("%lf%lf%lf", &x, &y, &z);}
	int pri(){return printf("P: %.4f %.4f %.4f\n", x, y, z);}
};
typedef Vector Point;

Point pot[4];
DBL squr[4];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~pot[0].read())
	{
		for(int i=1; i<4; i++) pot[i].read();
		Vector AB=pot[1]-pot[0], AC=pot[2]-pot[0], AD=pot[3]-pot[0];
		if(sgn( (AB^AC)*AD ) == 0)
		{
			puts("O O O O");
			continue;
		}
		Vector BC=pot[2]-pot[1], BD=pot[3]-pot[1];
		Vector O;
		DBL R;
		
		squr[0] = (BC^BD).length();
		squr[1] = (AC^AD).length();
		squr[2] = (AB^AD).length();
		squr[3] = (AB^AC).length();
		DBL S=0;
		for(int i=0; i<4; i++) S += squr[i];
		for(int i=0; i<4; i++) O.x += squr[i]*pot[i].x;
		for(int i=0; i<4; i++) O.y += squr[i]*pot[i].y;
		for(int i=0; i<4; i++) O.z += squr[i]*pot[i].z;
		O.x /= S;
		O.y /= S;
		O.z /= S;
		Vector AO = O-pot[0];
		R = abs( ((AB^AC)*AO)/((AB^AC).length()) );
		printf("%.4f %.4f %.4f %.4f\n", O.x, O.y, O.z, R);
	}
	return 0;
}

