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

char inpt[2][110];
void solve(char*);

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
		scanf("%s %s", inpt[0], inpt[1]);
		solve(inpt[0]);
		solve(inpt[1]);
		if(!strcmp(inpt[0], inpt[1])) puts("Yes");
		else puts("No");
	}
	return 0;
}

void solve(char str[])
{
	int len=strlen(str);
	for(int i=0; i<len; i++)
	{
		if('A'<=str[i] && str[i]<='Z')
		{
			str[i]=str[i]-'A'+'a';
		}
		if(str[i]=='p') str[i]='b';
		if(str[i]=='i') str[i]='e';
	}
}
