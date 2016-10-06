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


struct Edge{
	int to, tme, cost;
	Edge(int _to, int _tme, int _cost):to(_to), tme(_tme), cost(_cost){
	}
};
vector<Edge> G[maxn]; 

struct State{
	int u, bag, k, Time;
	bool operator < (const State& rhs) const{
		return Time < rhs.Time;
	}
	State(int _u, int _bag, int _k, int _Time):u(_u), bag(_bag), k(_k), Time(_Time){
	}
};
priority_queue<State> q;



int n, m, b, K, r, t;
int dp[maxn][5][5][maxn << 1];
bool in[maxn][5][5][maxn << 1];
int price[maxn][5];
int u, v, Time, Cost; 

void spfa(){
	dp[1][0][0][t] = r;
	while(q.size()) q.pop();
	q.push(State(1, 0, 0, t));
	in[1][0][0][t] = true;
	while(q.size()){
		State top = q.top(); q.pop();
		int u = top.u, bag = top.bag, k = top.k, Time = top.Time;
		int val = dp[u][bag][k][Time];
//		cout << u << ' ' << bag << ' ' << k << ' ' << Time << endl;
		in[u][bag][k][Time] = false;
		if (u == n) continue;
		//不买不卖
		for (int i = 0; i < (int)G[u].size(); ++i){
			int to = G[u][i].to, cost = G[u][i].cost, tme = G[u][i].tme;
			if ((to == n || to == 1) && k != 0) continue;
			if (cost > val) continue;
			if (tme > Time) continue;
			if (val - cost > dp[to][bag][k][Time - tme]){
				dp[to][bag][k][Time - tme] = val - cost;
				if (!in[to][bag][k][Time - tme]){
					in[to][bag][k][Time - tme] = true;
					q.push(State(to, bag, k, Time - tme));
				}
			}
		} 
		
		
		if (u != 1 && u != n){
			int nk = (k + 1) % K;
			if (Time == 0) continue;
			if (dp[u][bag][nk][Time - 1] < val){
				dp[u][bag][nk][Time - 1] = val;
				if (!in[u][bag][nk][Time - 1]){
					in[u][bag][nk][Time - 1] = true;
					q.push(State(u, bag, nk, Time - 1));
				}
			}
		}
		
		
		if (u == 1 || u == n) continue;
		
		//卖出一个
		if (bag > 0){
			int nbag = bag - 1;
			int nval = val + price[u][k];
			for (int i = 0; i < (int)G[u].size(); ++i){
				int to = G[u][i].to, cost = G[u][i].cost, tme = G[u][i].tme;
				if ((to == n || to == 1) && k != 0) continue;
				if (cost > nval) continue;
				if (tme > Time) continue;
				if (nval - cost > dp[to][nbag][k][Time - tme]){
					dp[to][nbag][k][Time - tme] = nval - cost;
					if (!in[to][nbag][k][Time - tme]){
						in[to][nbag][k][Time - tme] = true;
						q.push(State(to, nbag, k, Time - tme));
					}
				}
			} 
			if (u != 1 && u != n){
				int nk = (k + 1) % K;
				if (Time == 0) continue;
				if (dp[u][nbag][nk][Time - 1] < nval){
					dp[u][nbag][nk][Time - 1] = nval;
					if (!in[u][nbag][nk][Time - 1]){
						in[u][nbag][nk][Time - 1] = true;
						q.push(State(u, nbag, nk, Time - 1));
					}
				}
			}
			
			
		} 
		
		//买入一个
		if(bag < b && val >= price[u][k]){
			int nbag = bag + 1;
			int nval = val - price[u][k];
			for (int i = 0; i < (int)G[u].size(); ++i){
				int to = G[u][i].to, cost = G[u][i].cost, tme = G[u][i].tme;
				if ((to == n || to == 1) && k != 0) continue;
				if (cost > nval) continue;
				if (tme > Time) continue;
				if (nval - cost > dp[to][nbag][k][Time - tme]){
					dp[to][nbag][k][Time - tme] = nval - cost;
					if (!in[to][nbag][k][Time - tme]){
						in[to][nbag][k][Time - tme] = true;
						q.push(State(to, nbag, k, Time - tme));
					}
				}
			} 
			if (u != 1 && u != n){
				int nk = (k + 1) % K;
				if (Time == 0) continue;
				if (dp[u][nbag][nk][Time - 1] < nval){
					dp[u][nbag][nk][Time - 1] = nval;
					if (!in[u][nbag][nk][Time - 1]){
						in[u][nbag][nk][Time - 1] = true;
						q.push(State(u, nbag, nk, Time - 1));
					}
				}
			}
		} 
		
	}
	return;
}

int main(){
//必须编译过才能交 
	freopen("in.txt", "r", stdin);
	ios::sync_with_stdio(false);
	int ik, i, j, k, kase;
	cin >> kase;
	for (int ik = 1; ik <= kase; ++ik){
		cin >> n >> m >> b >> K >> r >> t;
		memset(dp, -1, sizeof dp);
		memset(in, false, sizeof in);
		for (i = 0; i < K; ++i) 
			for (j = 1; j <= n; ++j) cin >> price[j][i];
		for (i = 1; i <= n; ++i) G[i].clear();
		for (i = 1; i <= m; ++i){
			cin >> u >> v >> Time >> Cost;
			G[u].push_back(Edge(v, Time, Cost));
		}
		spfa();
		int ans = -1;
		for (i = 0; i <= t; ++i) ans = max(ans, dp[n][0][0][i]);
		cout << "Case #" << ik << ": ";
		if (ans == -1) cout << "Forever Alone" << endl;
		else cout << ans << endl; 
	}
	
	return 0;
}
