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

const int dir[4][2]={1,0,-1,0,0,1,0,-1};
int slen;
struct data
{
	int body[2][10], t;
	bool operator < (const data &v) const
	{
		for(int i=1; i<=slen; i++)
		{
			if(body[0][i] != v.body[0][i]) return body[0][i] < v.body[0][i];
			if(body[1][i] != v.body[1][i]) return body[1][i] < v.body[1][i];
		}
		return 0;
	}
};
int N,M;
char Map[20][20];

bool check(data&,int,int);
void move(data&,data&,int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	while(~scanf("%d%d", &N, &M))
	{
		data stp;
		slen=0;
		for(int i=1; i<=N; i++)
		{
			scanf("%s", Map[i]+1);
			for(int j=1; j<=M; j++)
			{
				if(isdigit(Map[i][j]))
				{
					int num=Map[i][j]-'0';
					slen = max(num, slen);
					stp.body[0][num] = i;
					stp.body[1][num] = j;
				}
			}
		}
		
		stp.t=0;
		queue<data> que;
		set<data> vis;
		que.push(stp);
		vis.insert(stp);
		int ux, uy, x, y,  k;
		data tem;
		int ans=-1;
		while(que.size())
		{
			data &u=que.front();
			ux = u.body[0][1], uy = u.body[1][1], tem.t = u.t+1;
//			printf("ux:%d uy:%d\n", ux, uy);
			for(k=0; k<4; k++)
			{
				x = dir[k][0] + ux;
				y = dir[k][1] + uy;
				if(Map[x][y] == '@') {ans=tem.t; goto BP;}
				if(check(u,x,y)) continue;
				move(u,tem,x,y);
				if(vis.find(tem) == vis.end())
				{
					vis.insert(tem);
					que.push(tem);
				}
			}
			que.pop();
		}
		BP:;
		printf("%d\n", ans);
	}
	return 0;
}

bool check(data &u, int x, int y)
{
	if(x<=0 || x>N || y<=0 || y>M || Map[x][y]=='#') return 1;
	for(int i=2; i<slen; i++) if(u.body[0][i]==x && u.body[1][i]==y) return 1;
	return 0;
}

void move(data &u, data &v, int x, int y)
{
	v.body[0][1] = x;
	v.body[1][1] = y;
	for(int i=2; i<=slen; i++)
	{
		v.body[0][i] = u.body[0][i-1];
		v.body[1][i] = u.body[1][i-1];
	}
}
