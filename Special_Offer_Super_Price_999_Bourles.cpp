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

LL D;
char A[25], B[25], C[25];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%s%lld", A, &D))
	{
		memcpy(B, A, sizeof(A));
		memcpy(C, A, sizeof(A));
		int len = strlen(A), ans=0;
		for(int i=len-1; i>=0 && A[i]=='9'; i--) ans++;
		for(int i=len-1; i>0; i--)
		{
			B[i] = '9';
			for(int j=8; j>=0; j--)
			{
				B[i-1] = j+'0';
				if(strcmp(B,A)<=0)
				{
					LL na = atoll(A), nb=atoll(B);
					if(ans < len-i && na-nb<=D)
					{
						ans = len-i;
						memcpy(C, B, sizeof(B));
					}
				}
			}
		}
		printf("%lld\n", atoll(C));
	}
	return 0;
}

