#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define ml m
#define mr m + 1
#define Error(x) cout << #x << " = " << x << endl
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;
const int maxm = 1e6 + 15;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int head[maxn], ecnt, m, deg[maxn];

struct Edge {
	int to, cost, next;
} edge[maxm];

void add(int u, int v) {
	edge[ecnt].to = v;
	edge[ecnt].next = head[u];
	head[u] = ecnt++;
}

ll b[maxn];

int gethash(int x) { 
	if(x > b[m]) return m + 1;
	return lower_bound(b + 1, b + 1 + m, x) - b; 
}

struct Query {
	int l, r;
	ll num;
};

ll n, k, root, a[maxn], que[maxn];
int dfst, dfsn[maxn];

int T[maxn], tot, val[maxn * 32], lson[maxn * 32], rson[maxn * 32];

vector<Query> q;

void dfs(int u, int fa) {
	dfsn[u] = ++dfst;
	que[dfst] = a[u];
	for(int i = head[u]; ~i; i = edge[i].next) { 
		int v = edge[i].to;
		if(v == fa) continue; 
		dfs(v, u);
	}
	if(dfsn[u] != dfst) q.push_back({dfsn[u], dfst, a[u]});
}

int build(int l, int r) {
	int rt = ++tot;
	val[rt] = 0;
	int m = l + r >> 1;
	if (l != r){
		lson[rt] = build(l, ml);
		rson[rt] = build(mr, r);
	}
	return rt;
}
int update(int pre, int pos, int l, int r){
	int rt = ++tot;
	val[rt] = val[pre] + 1;
	if(l == r) return rt;
	int m = l + r >> 1;
	if (pos <= m) lson[rt] = update(lson[pre], pos, l, ml);
	if (pos  > m) rson[rt] = update(rson[pre], pos, mr, r);
	return rt;
}
ll query(int pos, int L, int R, int l, int r){
	if (L <= l and r <= R) return val[pos];
	int m = l + r >> 1;
	ll res = 0;
	if(L <= m) res += query(pos, L, R, l, ml); 	
	if(R  > m) res += query(pos, L, R, mr, r);
	return res;
}

int main() {
#ifdef NEKO
//	freopen("C:\\Nya.txt", "r", stdin);
#endif
	int t; scanf("%d", &t);
	while(t--) {
		scanf("%lld %lld", &n, &k); q.clear();
		ecnt = 0; memset(head, -1, sizeof head);
		for(int i = 1; i <= n; i++) 
			scanf("%lld", &a[i]), b[i] = a[i];

		for(int i = 1; i < n; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			add(u, v); deg[v]++;
		}
		sort(b + 1, b + 1 + n);
		m = unique(b + 1, b + 1 + n) - b - 1;		
		
		for(int i = 1; i <= n; i++) 
			if(!deg[i]) { root = i; break; }
		dfst = 0; memset(dfsn, 0, sizeof dfsn);
		dfs(root, 0); tot = 0;
		T[0] = build(1, m);
		for(int i = 1; i <= n; i++) 
			T[i] = update(T[i - 1], gethash(que[i]), 1, m);
		b[m + 1] = inf;
		ll ans = 0;
		for(int i = 0; i < (int)q.size(); i++) {
			int id = gethash(k / q[i].num);
			if(b[id] != k / q[i].num) id--;
			ans += query(T[q[i].r], 1, id, 1, m) - query(T[q[i].l], 1, id, 1, m);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

