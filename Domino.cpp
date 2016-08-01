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

char Map[4][110];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	while(~scanf("%d", &N))
	{
		CLR(Map);
		if(N==1) {printf("a\na\nb\nb"); continue;}
		if(N==2) {printf("aa\nbb\naa\nbb"); continue;}
		if(N&1)
		{
			int cur=0;
			for(int i=0; i<N-1; i+=2)
			{
				Map[0][i] = Map[0][i+1] = 'a'+cur;
				Map[1][i] = Map[1][i+1] = 'c'+cur;
				Map[2][i+1] = Map[2][i+2] = 'e'+cur;
				Map[3][i+1] = Map[3][i+2] = 'g'+cur;
				cur ^= 1;
			}
			Map[2][0] = Map[3][0] = 'z';
			Map[0][N-1] = Map[1][N-1] = 'z';
		} 
		else
		{
			int cur=0;
			for(int i=0; i<N; i+=2)
			{
				Map[0][i] = Map[0][i+1] = Map[3][i] = Map[3][i+1] = 'a'+cur;
				cur^=1;
			}
			for(int i=1; i<N-1; i+=2)
			{
				Map[1][i] = Map[1][i+1] = 'c'+cur;
				Map[2][i] = Map[2][i+1] = 'e'+cur;
				cur^=1;
			}
			Map[1][0] = Map[2][0] = 'z';
			Map[1][N-1] = Map[2][N-1] = 'z';
		}
		for(int i=0; i<4; i++)
		{
			printf("%s", Map[i]);
			if(i<3) puts("");
		}
	}
	return 0;
}

