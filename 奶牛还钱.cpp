#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)

const int tval[6]={100,50,20,10,5,1};
struct data
{
	int sta[3];
	int have[3][6];
};

bool operator < (const data &u, const data &v)
{
	for(int i=0; i<3; i++) if(u.sta[i]!=v.sta[i]) return u.sta[i] < v.sta[i];
	for(int i=0; i<3; i++) for(int j=0; j<6; j++) if(u.have[i][j]!=v.have[i][j]) return u.have[i][j] < v.have[i][j];
	return 0;
}

map<data,int> dp;

int update(const data&,int);
bool check(const data&);

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
		dp.clear();
		data orin;
		for(int i=0; i<3; i++) scanf("%d", &orin.sta[i]);
		for(int i=0; i<3; i++) for(int j=0; j<6; j++) scanf("%d", &orin.have[i][j]);
		
		queue<data> que;
		que.push(orin);
		update(orin,0);
		int ans=-1;
		
		while(que.size())
		{
			data u=que.front(); que.pop();
			int step=dp[u];
			if(check(u)){ans=step;break;}
			for(int p=0; p<3; p++)
			{
				int lp=(p-1+3)%3;
				for(int i=0; i<6; i++)
				{
					if(!u.have[p][i]) continue;
					u.have[p][i]--;
					u.sta[p]-=tval[i];
					if(update(u,step+1)) que.push(u);
					u.have[p][i]++;
					u.sta[p]+=tval[i];
					
					u.have[p][i]--;
					u.sta[lp]+=tval[i];
					if(update(u,step+1)) que.push(u);
					u.have[p][i]++;
					u.sta[lp]-=tval[i];
				}
			}
		}
		
		if(~ans) printf("%d\n", ans);
		else puts("impossible");
	}
	return 0;
}

int update(const data &x, int val)
{
	map<data,int>::iterator it=dp.find(x);
	if(it==dp.end()) 
	{
		dp.insert(make_pair(x,val));
		return 1;
	}
	if(it->second > val)
	{
		it->second=val;
		return 1;
	}
	return 0;
}

bool check(const data &x)
{
	for(int i=1; i<3; i++) if(x.sta[i]!=x.sta[0]) return 0;
//	for(int i=0; i<3)if(x.sta[])
	return 1;
}

