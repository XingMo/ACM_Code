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


int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N;
	scanf("%d", &N);
	for(int i=1; i<N; i+=2)
	{
		int l=(N-i)/2;
		for(int j=0; j<l; j++) putchar('*');
		for(int j=0; j<i; j++) putchar('D');
		for(int j=0; j<l; j++) putchar('*');
		puts("");
	}
	for(int i=N; i>=1; i-=2)
	{
		int l=(N-i)/2;
		for(int j=0; j<l; j++) putchar('*');
		for(int j=0; j<i; j++) putchar('D');
		for(int j=0; j<l; j++) putchar('*');
		if(i!=1) puts("");
	}
	return 0;
}

