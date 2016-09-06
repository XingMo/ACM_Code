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

const int maxn=20;
int N;
char str[maxn];

const int dx[10]={3,0,0,0,1,1,1,2,2,2};
const int dy[10]={1,0,1,2,0,1,2,0,1,2};
int sque[2][20];
int valid(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%s", &N, str))
	{
		int cnt=0;
		for(int i=0; i<=9; i++)
		{
			cnt += valid(dx[i], dy[i]);
		}
		if(cnt==1) puts("YES");
		else puts("NO");
	}
	return 0;
}

int valid(int ox,int oy)
{
	int num[20];
	for(int i=0; str[i]; i++) num[i] = str[i]-'0';
	for(int i=0,j,x,y; str[i]; i++)
	{
		x = ox + dx[num[i]]-dx[num[0]];
		y = oy + dy[num[i]]-dy[num[0]];
		for(j=0; j<10; j++) if(dx[j]==x && dy[j]==y) break;
		if(j==10) return 0;
	}
	return 1;
}
