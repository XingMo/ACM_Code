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

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int cnt[3]={0};
	int k=0;
	char x;
	while((x=getchar()) != EOF)
	{
		if(x=='\n') {k++; continue;}
		if(x=='a' || x=='e' || x=='i' || x=='o' || x=='u') cnt[k]++;
	}
	if(cnt[0]==5 && cnt[1]==7 && cnt[2]==5) puts("YES");
	else puts("NO");
	return 0;
}

