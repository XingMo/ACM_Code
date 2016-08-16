/*
HDU - 5818
给定两个栈 A和 B，开始栈为空，有三种操作
向某个栈里 push一个数，从某个栈里 pop一个数
将两个栈 merge到一个栈，按时间顺序将所有元素压入这个栈

这题队友赛上写了个线段树的做法
虽说也不是毫无思维难度，但是比起题解就显得很蠢了
题解的做法是开一个新栈 C
每次 merge的时候，按时间顺序归并地压入新栈 C
之后 push不变，只不过 pop的时候
因为题目保证不会 pop一个空栈，所以当 pop一个空栈的时候
说明这个栈里本来是有数据的，所以直接 pop C栈里的内容
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

const int maxn=1e5+10;

int N;
Pii stak[3][maxn];
int skt[3];
char opt[10], fir, sec;
int num;

void move(int);
void pri(int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int ck=0;
	while(~scanf("%d", &N))
	{
		if(!N) break;
		printf("Case #%d:\n", ++ck);
		CLR(skt);
		for(int i=0; i<N; i++)
		{
			scanf(" %s", opt);
			if(!strcmp(opt, "push"))
			{
				scanf(" %c%d", &fir, &num);
				stak[fir-'A'][skt[fir-'A']++] = Pii(num, i+1);
			}
			if(!strcmp(opt, "pop"))
			{
				scanf(" %c", &fir);
				int tp = fir-'A';
				if(!skt[fir-'A']) tp=2;
				printf("%d\n", stak[tp][--skt[tp]].first);
			}
			if(!strcmp(opt, "merge"))
			{
				scanf(" %c %c", &fir, &sec);
				int now = skt[2];
				while(skt[0] || skt[1])
				{
					if(skt[0] && !skt[1]) move(0);
					else if(!skt[0] && skt[1]) move(1);
					else if(stak[0][skt[0]-1].second > stak[1][skt[1]-1].second) move(0);
					else move(1);
				}
				reverse(stak[2]+now, stak[2]+skt[2]);
			}
		}
	}
	return 0;
}

void move(int tp)
{
	stak[2][skt[2]++] = stak[tp][--skt[tp]];
}
