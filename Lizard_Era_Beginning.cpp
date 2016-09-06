/*
Codeforces - 585D
有三个开始为 0的数，有 N次选择，每次改变其中两个
问最后使得三个数相等且最大的选择方案
其中 N<=25

一看 N<=25，就可以暴力算一算
直接状压是不行的，所以折半状压
先用三进制压前一半，每一位表示不选的那个人
然后把后两个人对第一个人价值的差当作 key
存一下第一个人的最大价值，以及此时的状态
然后枚举后一半，就可以 log(3^(N/2))找出使三个人相等的最优合法状态
时间复杂度为 (3^(N/2)*log(3^(N/2)))

如果将最后的前一半和后一半的状态搞在一起的话
要注意 3^25爆 int这个问题 （调了一年orz）
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

const char name[]="LMW";
const int INF=0x3f3f3f3f;
int N, W[3][30], pow3[15];
map<Pii,Pii> stor;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	pow3[0]=1;
	for(int i=1; i<15; i++) pow3[i]=3*pow3[i-1];
	while(~scanf("%d", &N))
	{
		stor.clear();
		int hl=N>>1, le=N-hl, ans=-INF;
		LL mask=0;
		for(int i=0; i<N; i++) for(int j=0; j<3; j++) scanf("%d", &W[j][i]);
		if(N==1)
		{
			int cnt=0; char res[3]={0};
			for(int i=0; i<3 && cnt<2; i++) if(!W[i][0]) res[cnt++] = name[i];
			if(cnt<2) puts("Impossible");
			else puts(res);
			continue;
		}
		for(int m=0,res[3],tem; m<pow3[hl]; m++)
		{
			tem = m;
			CLR(res);
			for(int i=0; i<hl; i++)
			{
				for(int j=0; j<3; j++) if(j!=tem%3) res[j] += W[j][i];
				tem /= 3;
			}
			res[1] -= res[0]; res[2] -= res[0];
			auto it = stor.find(Pii(res[1],res[2]));
			if(it == stor.end()) stor.insert( make_pair(Pii(res[1],res[2]), Pii(res[0],m)) );
			else if(it->second.first < res[0]) it->second = Pii(res[0], m);
		}
		for(int m=0,res[3],tem; m<pow3[le]; m++)
		{
			tem = m;
			CLR(res);
			for(int i=hl; i<N; i++)
			{
				for(int j=0; j<3; j++) if(j!=tem%3) res[j] += W[j][i];
				tem /= 3;
			}
			res[1] -= res[0]; res[2] -= res[0];
			auto it = stor.find(Pii(-res[1], -res[2]));
			if(it != stor.end() && it->second.first+res[0] > ans)
			{
				ans = it->second.first+res[0];
				mask = (LL)m*pow3[hl] + it->second.second;
			}
		}
		if(ans==-INF) puts("Impossible");
		else
		{
			char res[3]={0};
			for(int i=0; i<N; i++,mask/=3,puts(res)) for(int j=0,cnt=0; j<3 && cnt<2; j++) if(j!=mask%3) res[cnt++] = name[j];
		}
	}
	return 0;
}
