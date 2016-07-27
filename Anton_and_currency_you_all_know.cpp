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

const int maxn=1e5+10;
struct data
{
	int p, w;
	data(){};
	data(int a,int b){p=a, w=b;}
	bool operator < (const data &v) const
	{
		return w > v.w;
	}
};
char A[maxn];
data ans[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int np=0;
	scanf("%s", A);
	int len=strlen(A);
	int tdgit=A[len-1]-'0';
	for(int i=0; i<len; i++)
	{
		int dgit=A[i]-'0';
		if(dgit&1) continue;
		ans[np++] = data(i, len-i-1);
		if(tdgit-dgit<0) ans[np-1].w *= -1;
	}
	if(!np) puts("-1");
	else
	{
		sort(ans, ans+np);
		swap(A[len-1], A[ans[0].p]);
		puts(A);
	}
	return 0;
}

