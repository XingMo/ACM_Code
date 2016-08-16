/*
HDU - 5785
给定一个字符串 S，定义三元组 (i,j,k)，其中 1<=i<=j<k<=|S|
S[i..j]与 S[j+1..k]为回文串时，代价为 i*k
求所有三元组的代价和

首先对 S求一遍 manacher，然后就能求出所有回文半径
枚举 j，预处理出一个位置为回文串右端点时，其左端点 i的位置的和
同理为回文串左端点时，其右端点的 k位置的和
\sum{i} * \sum{k} = \sum\sum {i*k} 即为所求答案 

预处理的方式就是找到所有回文中心，对他回文半径内的点都加上它的贡献
这个区间更新看起来要用数据结构维护一下，实际上用差分的思想即可

在一段区间上加上一个数，只要在左端点加这个数，在右端点加一减去这个数
最后扫一遍整个区间就能得出结果
同理，加上一个等差数列就额外开一个数组维护公差 d
进入区间的时候加上公差，退出区间的时候减掉公差
不同的是值在退出区间的时候，由于加的数和左端点不一样了
所以减去的是左端点加的数 v，在减去它在区间上变化的值 (r-l+1)*d

这样就能在线性时间内预处理完，总的复杂度也是 O(N)的
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

const int maxn=1000000+10, MOD=1000000007;
struct Manacher
{
	char str[2*maxn];
	int mana[2*maxn], len, res;
	int solve(char*);
};
struct RangeUpdate
{
	char *debug;
	int siz;
	int arr[maxn], delt[maxn];
	void init(int _n) {siz=_n; CLR(arr); CLR(delt);};
	void add(int,int,int,int);
	void update();
};
char str[maxn];
Manacher M;
RangeUpdate L, R;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf(" %s", str))
	{
		M.solve(str);
		int len=strlen(str);
		L.init(len); R.init(len);
		for(int i=2, p, v, r; i<M.len; i++)
		{
			p = (i-1)/2, v=p+1;
			if(M.str[i]!='#')
			{
				r = (M.mana[i]+1)/2;
				L.add(p, p+r-1, v, -1);
				R.add(p-r+1, p, v+r-1, -1);
			}
			else
			{
				r = (M.mana[i]-1)/2;
				L.add(p, p+r-1, v-1, -1);
				R.add(p-r, p-1, v+r-1, -1);
			}
		}
		L.update(); R.update();
		LL ans=0;
		for(int i=0; i<len-1; i++)
		{
			ans = (ans + (LL)L.arr[i]*R.arr[i+1]%MOD)%MOD;
		}
		printf("%lld\n", (ans+MOD)%MOD);
	}
	return 0;
}

int Manacher::solve(char _str[])
{
	int tlen = strlen(_str);
	res = 0;
	str[0]='!';
	for(int i=0; i<tlen; i++)
	{
		str[2*i+1] = '#';
		str[2*i+2] = _str[i];
	}
	str[2*tlen+1]='#';
	str[2*tlen+2]=0;
	len = 2*tlen+2;
	mana[1]=1;
	int p=1, rm=1;
	for(int i=2; i<len; i++)
	{
		mana[i] = 1;
		if(rm>i)
		{
			mana[i] = min(rm-i+1, mana[2*p-i]);
		}
		while(str[i-mana[i]] == str[i+mana[i]] ) mana[i]++;
		if(i+mana[i]-1 > rm)
		{
			rm = i+mana[i]-1;
			p=i;
		}
		if(res < mana[i]) res = mana[i]-1;
	}
	return res;
}

void RangeUpdate::add(int l, int r, int x, int d)
{
	arr[l] = (arr[l]+x)%MOD; arr[r+1] = (arr[r+1] - (x+(LL)(r-l+1)*d%MOD)%MOD) %MOD;
	delt[l] = (delt[l]+d)%MOD; delt[r+1] = (delt[r+1]-d)%MOD;
}

void RangeUpdate::update()
{
	int sum=0, nd=0;
	for(int i=0; i<siz; i++)
	{
		sum = (sum+arr[i])%MOD;
		arr[i] = sum;
		nd = (nd + delt[i])%MOD;
		sum = (sum + nd)%MOD;
	}
}
