/*
直线轨道上放着 N个球，他们有着初始速度和位置并进行弹性碰撞，
他们的加速度和速度满足关系 a*v = C，其中 C是常数
问 t秒后速度第 k小的球的速度

首先弹性碰撞交换速度，所以根本不必管位置
其次速度和时间的关系可以直接积出来
v=sqrt(2Ct+v_0^2)，其中 v_0是初速度
然后根据初速度排个序，就能算出 t秒后第 k小的球的速度
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

const int maxn=1e5+10;
int N, Q, V[maxn];
DBL C;

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
		scanf("%d%lf", &N, &C);
		for(int i=1; i<=N; i++) scanf("%d%*d%*d", &V[i]);
		sort(V+1, V+1+N);
		scanf("%d", &Q);
		for(int i=1, k, t; i<=Q; i++)
		{
			scanf("%d%d", &t, &k);
			printf("%.3f\n", sqrt(2.0*C*t+1.0*V[k]*V[k]));
		}
	}
	return 0;
}

