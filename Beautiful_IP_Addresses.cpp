/*
Codeforces - 292C
给定若干个数字，构造出所有的 IP地址
使得去掉 '.'后其为回文串，且每个至少被使用了一次

刚开始直接一位一位的枚举，结果超时了
意识到这样构造出来很多不是回文串后，
费尽心思写了一个剪枝，依旧是 TLE
第二次面向回文串来构造，就过了

先枚举回文串长度，然后构造出前半段，再对称到后半段
然后再对这个回文串打上 '.'
这样保证构造出来的都是回文串，所以跑得飞快

有一个限制条件是，由于每个数字都要用上，所以 N>=7的时候肯定无解
但是不判这个好像也能过，不得不说 CF机子真是好
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
#include <complex>
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

int N, fmask, digt[10];
char buff[50], tans[50];
set<string> ans;

void dfs(int,int,int);
void dotstr(char*,int,int,int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		fmask = (1<<N)-1;
		ans.clear();
		for(int i=0; i<N; i++) scanf("%d", &digt[i]);
		if(N>=7) 
		{
			puts("0");
			continue;
		}
		sort(digt, digt+N);
		for(int i=4; i<=12; i++) dfs(0,i,0);
		printf("%d\n", (int)ans.size());
		for(auto &str:ans) cout << str << "\n";
	}
	return 0;
}

void dfs(int np, int size, int have)
{
	if((size&1) && np==size/2+1)
	{
		if(have==fmask)
		{
			int l,r;
			l=r=np-1;
			for(; l>=0; r++,l--) buff[r] = buff[l]; 
			buff[size]=0;
			dotstr(buff,0,0,-1,0);
		}
		return;
	}
	if(!(size&1) && np==size/2)
	{
		if(have==fmask)
		{
			int l,r;
			l=np-1, r=np;
			for(; l>=0; r++,l--) buff[r] = buff[l]; 
			buff[size]=0;
			dotstr(buff,0,0,-1,0);
		}
		return;
	}
	for(int i=0; i<N; i++)
	{
		buff[np] = digt[i]+'0';
		dfs(np+1,size,have|(1<<i));
	}
}

void dotstr(char str[], int np, int tp, int left, int scnt)
{
	if(scnt>3) return;
	if(!str[np])
	{
		if(scnt==3)
		{
			tans[tp] = 0;
			ans.insert(string(tans));
		}
		return;
	}
	int num = left, tem;
	if(num==-1) num=0;
	if(left!=0)
	{
		tem = num*10 + str[np]-'0';
		if(tem<256)
		{
			tans[tp] = str[np];
			dotstr(str,np+1,tp+1,tem,scnt);
		}
	}
	if(left!=-1)
	{
		tans[tp] = '.';
		dotstr(str,np,tp+1,-1,scnt+1);
	}
}
