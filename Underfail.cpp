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
const int maxn = 5e2 + 4;
const int maxm = 1e2 + 4;

bool can[maxn][maxm];
char s[maxm][maxn];
char ori[maxn];
int n, m, x;
int val[maxm], len[maxm];
int dp[maxn], pre[maxn];
int get(){
	memset(dp, 0, sizeof dp);
	int i, j;
	for (i = 1; i <= n; ++i){
		dp[i] = dp[i-1];
		pre[i] = -1;
		for (j = 1; j <= m; ++j) if (can[i][j]){
			if (dp[i] < dp[i - len[j]] + val[j]){
				pre[i] = j;
				dp[i] = dp[i - len[j]] + val[j];
			}
		}
	}
	int pos = n;
	while(pos){
		if (pre[pos] == -1) pos--;
		else{
			can[pos][pre[pos]] = false;
			pos -= len[pre[pos]];
		}
	}
//	cout << dp[n] << endl; 
	return dp[n];
}
int main(){
//必须编译过才能交 
	freopen("in.txt", "r", stdin);
	ios::sync_with_stdio(false);
	int ik, i, j, k, kase;
	while(cin >> n >> ori+1)
	{
		memset(can, 0, sizeof(can));
		cin >> m;
		for (i = 1; i <= m; ++i){
			cin >> s[i] + 1 >> val[i];
			len[i] = strlen(s[i] + 1);
		}
//		for(i=1; i<=m; i++) for(j=i+1; j<=m; j++) if(!strcmp(s[i]+1, s[j]+1))
//		{
//			val[i] = max(val[j], val[i]);
//			s[j][1] = 'T';
//		}
		for (i = 1; i <= n; ++i){
			for (j = 1; j <= m; ++j){
				if (len[j] > i) continue;
				int cnt = 0;
				while(cnt < len[j] && ori[i - cnt] == s[j][len[j] - cnt]) cnt++;
				if (cnt == len[j]) can[i][j] = true;
			}
	 	}
		int ans = 0;
		cin >> x;
		for (i = 1; i <= x; ++i) ans += get();
		cout << ans << endl;
	}
	return 0;
}

