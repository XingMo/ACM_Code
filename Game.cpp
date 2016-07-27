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
#include <sstream>
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

int K,N,M,Q;
vector<string> inpt;
map<string,map<string,int>> colec;
map<string,int> purch[110];
map<string,int> have[110];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	string buff, equi, subequi, num;
	scanf("%d%d%d%d", &K, &N, &M, &Q);
	for(int i=0; i<N; i++) cin >> buff;
	cin.get();
	for(int i=0; i<M; i++)
	{
		getline(cin, buff);
		int stp=-1;
		for(int i=0; i<(int)buff.size(); i++) if(buff[i]==':' || buff[i]==',') buff[i]=' ';
		stringstream sinpt(buff);
		sinpt >> equi;
		while(sinpt >> subequi >> num)
		{
			colec[equi].insert( {subequi, stoi(num)});
		}
	}
	for(int i=0; i<Q; i++)
	{
		cin >> num >> equi;
		int id=stoi(num)-1;
		purch[id][equi] ++;
		for(auto &pr:colec) if(pr.second.find(equi) != pr.second.end())
		{
			int cnt=0x3f3f3f3f;
			for(auto &pr2:pr.second)
			{
				cnt = min(cnt, purch[id][pr2.first]/pr2.second);
			}
			if(cnt)
			{
				have[id][pr.first] += cnt;
				for(auto &pr2:pr.second) purch[id][pr2.first] -= pr2.second*cnt;
			}
		}
	}
	for(int i=0; i<K; i++)
	{
		for(auto &pr:purch[i]) if(pr.second > 0)
		{
			have[i][pr.first] += pr.second;
		}
		cout << have[i].size() << '\n';
		for(auto &pr:have[i]) cout << pr.first << " " << pr.second << '\n';
	}
	return 0;
}

