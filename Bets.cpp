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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

struct data
{
	int id,pro,tim;
	bool operator < (const data &v) const 
	{
		if(tim != v.tim) return tim < v.tim;
		return id < v.id; 
	}
};

int N,M;
vector<data> sect[110];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%d%d", &N, &M);
	data x;
	for(int i=1; i<=M; i++)
	{
		int l,r;
		scanf("%d%d%d%d", &l, &r, &x.tim, &x.pro);
		x.id=i;
		for(int j=l; j<=r; j++) sect[j].push_back(x);
	}
	LL ans=0;
	for(int i=1; i<=N; i++)
	{
		if(!sect[i].size()) continue;
		sort(sect[i].begin(), sect[i].end());
		ans += sect[i][0].pro;
	}
	cout << ans << endl;
	return 0;
}

