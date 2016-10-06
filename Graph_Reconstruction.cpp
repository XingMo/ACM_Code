#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <stack>
#include <cctype>
#include <cmath>
#include <vector>
#include <sstream>
#include <bitset>
#include <deque>
#include <iomanip>
using namespace std;
#define pr(x) cout << "x = " << x << endl;
#define bug cout << "bugbug" << endl;
#define ppr(x, y) printf("(%d, %d)\n", x, y);
#define pfun(a, b) printf("x = %d   f(x) = %d\n", a, b);


typedef long long ll;
typedef pair<int, int> P;
typedef unsigned int uint;
const int MOD = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 1e2 + 4;
const int maxm = 1e3 + 4;

int n, degree[maxn];
priority_queue<P> q;
bool edge[maxn][maxn], E[maxn][maxn];
vector<P> v;

bool vis[maxn], stat[maxn];

void print(bool edge[maxn][maxn]){
	v.clear();
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) if (edge[i][j]) v.push_back(P(i, j));
	printf("%d %d\n", n, (int)v.size());
	for (int i = 0; i < (int)v.size(); ++i) printf("%d%c", v[i].first, i == (int)v.size() - 1 ? '\n': ' ');
	for (int i = 0; i < (int)v.size(); ++i) printf("%d%c", v[i].second, i == (int)v.size() - 1 ? '\n': ' ');
	if (v.size() == 0) puts("\n");
	return;
} 

void copyy()
{
	for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) E[i][j] = edge[i][j];
}

void dfs(int u, int f)
{
	vis[u] = 1;
	for(int v=1; v<=n; v++) if(u!=v)
	{
		
	}
}

int main(){
//必须编译过才能交 
//	ios::sync_with_stdio(false);
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	int ik, i, j, k, kase;
	while(~scanf("%d", &n)){
		for (i = 1; i <= n; ++i) cin >> degree[i];
		while(q.size()) q.pop();
		for (i = 1; i <= n; ++i) q.push(P(degree[i], i));
		memset(edge, false, sizeof edge);
		bool ok = true;
		while(true){
			P top = q.top(); q.pop();
			if (top.first == 0) break;
			int u = top.second;
//			cout << u << ' ' << degree[u] << endl;
			while(top.first--){
				degree[u]--;
				while(true){
				 	P tmp = q.top(); q.pop();
					if (tmp.first == 0){
						ok = false;
						break;
					}
					int v = tmp.second;
//					cout << v << endl;
//					system("pause");
					if (edge[u][v]) continue;
					degree[v]--;
					edge[u][v] = edge[v][u] = true;
					break;
				}
//				cout << top.first << ' ' << degree[u] << endl;
			}
			if (!ok) break;
			while(q.size()) q.pop();
			for (i = 1; i <= n; ++i) q.push(P(degree[i], i));
		}
//		bug; 
		if (!ok) printf("IMPOSSIBLE\n");
		else{
			int multi = dfs(1,0);
			if (multi){
				puts("MULTIPLE");
				print(E);
				print(edge);
			}
			else{
				puts("UNIQUE");
				print(edge);
			}
		}
	}
	
	return 0;
}

