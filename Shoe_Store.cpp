/*
Codeforces - 166D
WA
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

const int maxn=1e5+10;
struct data
{
	int c,s,id;
	data(){}
	data(int _c, int _s, int _id){c=_c; s=_s; id=_id;}
	bool operator < (const data &rhs) const
	{
		if(c != rhs.c) return c > rhs.c;
		return s > rhs.s;
	}
};

int N,M;
data shoe[maxn];
map<int,deque<data>> cust;

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d", &N))
	{
		cust.clear();
		for(int i=0; i<N; i++) scanf("%d%d", &shoe[i].c, &shoe[i].s), shoe[i].id=i+1;
		sort(shoe, shoe+N);
		scanf("%d", &M);
		for(int i=0,c,s; i<M; i++)
		{
			scanf("%d%d", &c, &s);
			cust[s].push_back(data(c,s,i+1));
		}
		for(auto &pr:cust) sort(pr.second.begin(), pr.second.end());
		LL res=0;
		vector<Pii> outp;
		for(int i=0,c,s,id; i<N; i++)
		{
			c = shoe[i].c, s = shoe[i].s, id = shoe[i].id;
			auto it = cust.find(s), it1 = cust.find(s-1);
			if(it1!=cust.end() && it1->second.size() && it1->second.front().c >= c)
			{
				res += c;
				outp.push_back(Pii(it1->second.front().id, id));
				it1->second.pop_front();
				continue;
			}
			if(it!=cust.end() && it->second.size() && it->second.front().c >= c)
			{
				res += c;
				outp.push_back(Pii(it->second.front().id, id));
				it->second.pop_front();
				continue;
			}
		}
		cout << res << "\n" << outp.size() << "\n";
		for(int i=0; i<(int)outp.size(); i++) printf("%d %d\n", outp[i].first, outp[i].second);
	}
	return 0;
}

