/*
HDU - 5414
给定A，B两个字符串，每次可以选择A中一个字符，
然后在其后添加一个与选择的那个字符不同的字符
问 A串是否可能构造成 B串

这是一个构造题，
看起来在 A中构造 aaaa这样连着的字符串是不行的
但实际上，假设有 A串 baaa，B串 baaaa，
我可以选择在字符 b后面添加一个 a
意识到这点以后，可以发现几乎可以任意添加字符
只要满足以下条件：
1. A字符串的开头与 B字符串的开头相等
2. A字符窜开头连续个数要大于等于 B字符串

1条件是因为只能在一个字符后面添加
所以开头如果不相同就无法构造
2条件是因为如果 A开头的连续个数大于等于 B的
那么可以在其中加一个字符把连续的断开，使之与 B的相同
而如果 B的长于 A的，那么就无法构造出来（不能添加与前面相同的）

最后判断一下 A剩下的部分是不是 B剩下部分一个不连续的子串即可
*/
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
char A[maxn], B[maxn];

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
		int lena=strlen(A), lenb=strlen(B);
		char x=B[0];
		int cnta=0, cntb=0;
		for(int i=0; i<lena && x==A[i]; i++) cnta++;
		for(int i=0; i<lenb && x==B[i]; i++) cntb++;
		if(A[0]!=B[0] || cnta<cntb) {puts("No"); continue;}
		int np=cntb;
		for(int i=cntb; i<lenb; i++)
		{
			if(B[i] == A[np]) np++;
			if(np>=lena) break;
		}
		if(np>=lena) puts("Yes");
		else puts("No");
	}
	return 0;
}

