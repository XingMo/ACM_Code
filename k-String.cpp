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

const int maxn=1e3+10;
int K;
char str[maxn];
int cnt[26], num[26];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d %s", &K, str))
	{
		CLR(cnt); CLR(num);
		int len=strlen(str);
		for(int i=0; i<len; i++) cnt[ str[i]-'a' ]++;
		bool ok=1;
		for(int i=0; i<26; i++) 
		{
			if(cnt[i]%K) ok=0;
			num[i] = cnt[i]/K;
		}
		if(ok)
		{
			for(int i=0; i<K; i++)
			{
				for(int j=0; j<26; j++)
				{
					for(int k=0; k<num[j]; k++) putchar(j+'a');
				}
			}
			puts("");
		}
		else puts("-1");
	}
	return 0;
}

