/*
Codeforces - 451A
N根横向木棍，M根纵向木棍组成了一个网格图
每次可以选择一个交点，去掉所有通过这个交点的木棍
两个人交替进行这个游戏，问最后谁能胜利

每次选择的一个交点，必然去掉了一根横向木棍和纵向木棍
所以每次 N和 M都减一
当其中有一个为 0的时候，就是先手必败态
所以只和 N、M中较小的那个的奇偶性有关
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
#define PCUT puts("----------")

int N,M;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d%d", &N, &M);
	puts( min(N,M)&1?"Akshat":"Malvika");
	return 0;
}

