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

const int maxl=1e3+10;

char S[maxl], Q[maxl+500][maxl], fin[maxl];

int onemax(int,char*,char*);

int main()
{
	#ifdef LOCAL
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	srand(time(0));
	int ac=0, wa=0, T=100, N=1000;
	int fsum=0;
	for(int ck=1; ck<=T; ck++)
	{
		for(int i=0; i<N; i++) S[i] = rand()%2+'1'; S[N]=0;
		int nt=0, ok=0, firt=0x3f3f3f3f;
		for(int t=1; t<=N+499; t++)
		{
			for(int i=0; i<N; i++) Q[nt][i] = rand()%2+'1'; Q[nt][N]=0;
			int res = onemax(N, Q[nt], S);
			if(res==N/2)
			{
				nt++;
				firt = min(firt, t);
			}
			if(res==N) {ok=1; break;}
		}
		for(int i=0; i<N; i++)
		{
			int cnt0=0, cnt1=0;
			for(int j=0; j<nt; j++) if(Q[j][i]=='0') cnt0++; else cnt1++;
			if(cnt0>cnt1) fin[i] = '0';
			else fin[i]='1';
		}
		fin[N]=0;
		if(onemax(N, fin, S)) ok=1;
		
		if(ok) ac++;
		else wa++;
//		printf("%d\n", firt);
		fsum += firt;
	}
	printf("T:%d ac:%d wa:%d, faver:%.3f\n", T, ac, wa, (DBL)fsum/T);
	return 0;
}

int onemax(int len, char A[], char B[])
{
	int cnt=0;
	for(int i=0; i<len; i++) if(A[i]==B[i]) cnt++;
	if(cnt==len || cnt==len/2) return cnt;
	else return 0; 
}

