#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) (a*a)

int N;
//bool mem[1000000];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
//		CLR(mem);
		int L,R, ans[2];
		char p=0, stat=0;
		scanf("%d%d", &L, &R);
		L--; R--;
		for(int i=0; i<N; i++)
		{
			scanf("%d%d", &ans[0], &ans[1]);
//			mem[ ans[0]-1 ]=1; mem[ ans[1]-1 ]=1;
		}
		for(int i=L; i<=R; i++)
		{
//			stat^=mem[i];
//			if(!mem[i] && !stat) ans[p++]=i+1;
			if(p>1) break; 
		}
		printf("%d %d\n", ans[0], ans[1]);
	}
	return 0;
}

