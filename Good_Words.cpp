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

char A[1010],B[10];
bool check(char*,char*);

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
		scanf(" %s %s", A, B);
		if(check(A,B)) puts("good");
		else
		{
			bool ag=0;
			for(int i=0; i<4; i++)
			{
				char C[10]; CLR(C);
				int np=0;
				for(int j=0; j<4; j++)
				{
					if(i==j) continue;
					C[np++]=B[j];
				}
				if(check(A,C)) 
				{
					puts("almost good");
					ag=1;
					break;
				}
			}
			if(!ag) puts("none");
		}
	}
	return 0;
}

bool check(char str[], char patn[])
{
	int plen=strlen(patn), len=strlen(str);
	for(int i=0; i<=len-plen; i++)
	{
		bool ok=1;
		for(int j=0; j<plen; j++)
		{
			if(str[i+j] != patn[j])
			{
				ok=0;
				break;
			}
		}
		if(ok) return 1;
	}
	return 0;
}

