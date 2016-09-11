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
const int maxn = 1e5 + 4;
const int maxm = 1e5 + 4;

ll n, K, num[maxn], S[maxn], T[maxn], hath[maxn], Num[maxn];
vector<int> G[maxn];
bool in[maxn];
int u, v, m, ind, rot, cnt, val[maxn * 30], lson[maxn * 30], rson[maxn * 30], Ti[maxn];
inline int get(ll num){
	return lower_bound(hath+1, hath+m, num) - hath;
}
void dfs(int u){
	S[u] = ind++;
	Num[ind - 1] = num[u];
	for (int i = 0; i < (int)G[u].size(); ++i){
//		cout << "from " << u << ' ' << "  to  " << G[u][i] << endl;
		dfs(G[u][i]); 
	}
	T[u] = ind-1;
	return;
} 
int build(int l, int r){
	int root = cnt++;
	val[root] = 0;
	if (l != r){
		lson[root] = build(l, (l+r)/2);
		rson[root] = build((l+r)/2+1, r);
	}
	return root;
}
int update(int root, int pos){
	int l = 1, r = m - 1;
	int newroot = cnt++;
	int ans = newroot;
	val[newroot] = val[root] + 1;
	while(l < r){
		int mid = (l + r) / 2;
		if (pos <= mid){
			rson[newroot] = rson[root];
			lson[newroot] = cnt;
			newroot = cnt++;
			root = lson[root];
			r = mid;
		}else{
			lson[newroot] = lson[root];
			rson[newroot] = cnt;
			newroot = cnt++;
			root = rson[root];
			l = mid + 1;
		}
		val[newroot] = val[root] + 1;
	} 
	return ans;
}
ll query(int pos, int l, int r, int lft, int rght){
	if (l <= lft && r >= rght) return val[pos];
	if (l  > rght || r < lft) return 0;
	return query(lson[pos], l, r, lft, (lft + rght) / 2) 
		+ query(rson[pos], l, r, (lft + rght) / 2 + 1, rght);
}
ll Query(int s, int t, ll num){
	int id = get(num);
	if (hath[id] != num) id--;
//	cout << query(T)
//	cout << s << ' ' << t << endl;
//	cout << Ti[s-1] << ' ' << Ti[t] << endl; 
	return query(Ti[t], 1, id, 1, m-1) - query(Ti[s-1], 1, id, 1, m-1);
}
int main(){
//必须编译过才能交 
	freopen("in.txt", "r", stdin);
	ios::sync_with_stdio(false);
	int ik, i, j, k, kase;
	cin >> kase;
	while(kase--){
		cin >> n >> K;
		for (i = 1; i <= n; ++i) G[i].clear();
		for (i = 1; i <= n; ++i) cin >> num[i];
		memcpy(hath, num, sizeof hath);
		
		hath[n+1] = INF;
		sort(hath+1, hath+2+n);
		m = unique(hath+1, hath+2+n) - hath;
//		cout << m << endl;
//		for (i = 1; i < m; ++i) cout << hath[i] << ' ';
		memset(in, false, sizeof in);
		for (i = 1; i < n; ++i){
			cin >> u >> v;
			G[u].push_back(v);
			in[v] = true;
		}
		for (i = 1; i <= n; ++i) if (!in[i]) rot = i;
		ind = 1;
		dfs(rot);
		
		cnt = 0;
		Ti[0] = build(1, m-1);
		for (i = 1; i <= n; ++i){
			Ti[i] = update(Ti[i-1], get(Num[i]));
		}
		ll ans = 0;
		for (i = 1; i <= n; ++i){
//			cout << "node " << i << ' ' << S[i] << ' ' << T[i] << endl;
			if (S[i] == T[i]) continue;
			ans += Query(S[i]+1, T[i], K / num[i]);
		}
		cout << ans << endl;
	}
	return 0;
}
/*
1
9 13
3 4 2 1 3 3 1 5 2
1 2
1 3
2 4
2 5
4 6
4 9
6 7
7 8
*/





