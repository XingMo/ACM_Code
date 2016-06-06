/*
PKU - 1182
有三种动物 A、B、C，A吃 B，B吃 C，C吃 A
给出 K条陈述，描述 1, X与 Y同类，2, X吃 Y
问其中有多少条假话，即与之前的真话矛盾

种类并查集经典题！基本是抄的题解 orz
维护一个eval[x]，表示 x连向其父亲的向量值对3取模
eval[x]==0，则 x与其父亲同类
eval[x]==1，则 x吃其父亲
eval[x]==2，则 x被其父亲吃
得到一条陈述后，我们先进行判断
如果 x，y不在一个集合，说明之前没有建立过联系，于是我们当这句话是真话
如果建立过联系，就对 x，y查找一下根，得到 fx，fy
然后根据向量关系建立并查集即可
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

const int maxn=5e4+10;
struct Union
{
	int n;
	int unin[maxn], eval[maxn];
	void init(int tn){n=tn; for(int i=1; i<=n; i++){unin[i]=i;eval[i]=0;}}
	int find(int x)
	{
		if(unin[x]==x) return x;
		int ox=unin[x];
		unin[x]=find(unin[x]);
		eval[x]=(eval[x]+eval[ox])%3;
		return unin[x];
	}
	void join(int opt,int x,int y)
	{
		int fx=find(x), fy=find(y);
		if(fx==fy) return;
		unin[fx]=fy;
		eval[fx]=(eval[y]+opt-eval[x])%3;
		eval[fx]=(eval[fx]+3)%3;
	}
	int judge(int opt,int x,int y)
	{
		if(((opt==1)&&(x==y)) || x>n || y>n) return 0;
		int fx=find(x), fy=find(y);
		if( fx != fy) return 1;
		else
		{
			if(eval[x]==(opt+eval[y])%3) return 1;
			else return 0;
		}
	}
};
int N,K;
Union U;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d%d", &N, &K);
	int ans=0;
	U.init(N);
	for(int i=1; i<=K; i++)
	{
		int d,x,y;
		scanf("%d%d%d", &d, &x, &y);
		d--;
		if(U.judge(d,x,y)) U.join(d,x,y);
		else ans++;
	}
	printf("%d\n", ans);
	return 0;
}

