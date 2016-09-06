/*
Codeforces - 460D
从区间 [l,r]内选出最多 k个数，使得他们的异或和最小


YY一下发现，如果一个偶数 2x 和 2x+1 异或，可以得到 1，挺小的
如果2x、2x+1、2x+2、2x+3异或就得到了 0，这意味这 k>= 4的时候
都只需取这样的 4个数，就能得到一个最小的 0
所以只需考虑 k<4的情况即可

1. 如果 k=1，那么只能选 l

2. 如果 k=2, 可以选一个2x和2x+1,这样异或和为 1,最小
因为两个不同的数异或和不可能为 0

3. 如果 k=3就比较麻烦了，首先知道可以只选两个，所以异或和最多为 1
现在来考虑是否可能为 0
首先考虑最高位，这三个数从大到小排列，必然是 1..., 1..., 0...
然后是次高位，有三种情况 
	1. 11..., 10..., 01...
	2. 11..., 11..., 00...
	3. 10..., 10..., 00...

	发现后两种情况如果是合法解，那么用最高位替换次高位，
	然后将最高位置 0，这样得到的三个数同样在区间 [l,r]中
所以最高位一定是这样的情况： 11..., 10..., 01...
然后让最小的数尽量大，最大的数尽量小，这样才尽可能地满足范围，所以三个数一定长这样
1100000..., 1011111..., 0111111...
枚举最小的那个数，找到第一个大于等于 l 的，然后再找最大的那个数，检查是否小于等于 r

当然以上做法都是在保证能取到这么多数的情况下成立的
如果区间比较小，那么就不能这么取了
为了编程方便，当 r-l+1<=4时直接暴力枚举
这样保证了区间内至少有 5个数可以取
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

LL L,R,K;
vector<LL> outp;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(cin >> L >> R >> K)
	{
		outp.clear();
		LL res=0;
		if(R-L+1<=4)
		{
			int Lim=1<<(R-L+1);
			res=0x3f3f3f3f3f3f3f3f;
			for(int m=1; m<Lim; m++) if(__builtin_popcount(m)<=K)
			{
				LL tem=0;
				for(int j=0; j<R-L+1; j++) if((m>>j)&1) tem ^= L+j;
				if(tem < res)
				{
					res = tem;
					outp.clear();
					for(int j=0; j<R-L+1; j++) if((m>>j)&1) outp.push_back(L+j); 
				}
			}
		}
		else if(K==1) res = L, outp.push_back(L);
		else if(K==2)
		{
			res = 1;
			if(!(L&1)) outp.push_back(L), outp.push_back(L+1);
			else outp.push_back(L+1), outp.push_back(L+2);
		}
		else if(K==3)
		{
			LL l=1, r;
			while(l<L) l=l<<1|1;
			r = (l<<1|1)^(l>>1);
			if(r<=R)
			{
				res = 0;
				outp.push_back(l); outp.push_back((l+1)^(l>>1)); outp.push_back(r);
			}
			else
			{
				res = 1;
				if(!(L&1)) outp.push_back(L), outp.push_back(L+1);
				else outp.push_back(L+1), outp.push_back(L+2);
			}
		}
		else
		{
			res = 0;
			if(!(L&1)) for(LL i=L; i<L+4; i++) outp.push_back(i);
			else for(LL i=L+1; i<L+5; i++) outp.push_back(i);
		}
		cout << res << "\n";
		cout << outp.size() << "\n";
		for(int i=0; i<(int)outp.size(); i++) cout << outp[i] << " ";
		puts("");
	}
	return 0;
}

