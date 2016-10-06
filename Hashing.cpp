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
const int maxm = 3e2 + 4;
int n;
ll num[maxn], maxv[maxm], dp[maxn][maxm], tmp[maxn], sum[maxn];
map<char, int> digit;
char Num[3];
inline ll get(){
	return digit[Num[0]] * 16 + digit[Num[1]];
}
int main(){
//必须编译过才能交 
	freopen("in.txt", "r", stdin);
//	ios::sync_with_stdio(false);
	int ik, i, j, k, kase;
	for (i = 0; i < 10; ++i) digit[i + '0'] = i;
	for (i = 0; i < 6; ++i) digit[i + 'A'] = 10 + i;
	cin >> n;
	for (i = 1; i <= n; ++i){
		cin >> Num;
		num[i] = get();
//		cout << num[i] << ' ';
	}
//	for(int i=1; i<=n; i++) printf("%lld ", num[i]); puts("");
	memset(maxv, 0, sizeof maxv);
	ll ans = 0;
	for (i = 1; i <= n; ++i){
		for (j = min(i, 256); j >= 1; --j){
			dp[i][j] = maxv[j] + (num[i] ^ (j-1));
//			cout << maxv[j] << "    ??" <<  ' ' << (num[i]^j) << endl;
//			cout << i << ' ' << j << ' ' << dp[i][j] << endl;
			ans = max(ans, dp[i][j]); 
			maxv[j+1] = max(maxv[j+1], dp[i][j]);
		}
	}
	sum[n+1] = tmp[n+1] = 0;
	memset(tmp, 0, sizeof tmp);
	for (i = n; i > 256; --i){
		if (i + 256 <= n+1){
			tmp[i] = tmp[i + 256];
			for (j = i; j < i + 256; ++j) tmp[i] += num[j] ^ (j - i); 
		}else{
			for (j = i; j <= n; ++j) tmp[i] += num[j] ^ (j - i); 
		}
	}
	for (i = 257; i <= n; ++i){
		ll res = n - i + 1;
		ll div = res / 256;
		sum[i] = tmp[i] + (1 + div) * (div) / 2 * 256 * 256;
		sum[i] += (div + 1) * 256 * (res - div * 256); 
	}
	for (i = 257; i <= n; ++i){
		ans = max(ans, dp[i-1][256] + sum[i]);
	}
	cout << ans << endl;
	return 0;
}

//#include <iostream>
//#include <cstring>
//#include <cstdio>
//#include <vector>
//#include <set>
//#include <map>
//#include <queue>
//#include <algorithm>
//#include <stack>
//#include <cctype>
//#include <cmath>
//#include <vector>
//#include <sstream>
//#include <bitset>
//#include <deque>
//#include <iomanip>
//using namespace std;
//#define pr(x) cout << "x = " << x << endl;
//#define bug cout << "bugbug" << endl;
//#define ppr(x, y) printf("(%d, %d)\n", x, y);
//#define pfun(a, b) printf("x = %d   f(x) = %d\n", a, b);

//typedef long long ll;
//typedef pair<int, int> P;
//typedef unsigned int uint;
//const int MOD = 1e9 + 7;
//const int inf = 0x3f3f3f3f;
//const ll INF = 0x3f3f3f3f3f3f3f3f;
//const int maxn = 1e5 + 4;
//const int maxm = 3e2 + 4;
//int n;
//ll num[maxn], maxv[2010], dp[2010][2010], tmp[maxn], sum[maxn];
//map<char, int> digit;
//char Num[3];
//inline ll get(){
//	return digit[Num[0]] * 16 + digit[Num[1]];
//}
//int main(){
////必须编译过才能交 
//	ios::sync_with_stdio(false);
//	freopen("in.txt", "r", stdin);
//	int ik, i, j, k, kase;
//	for (i = 0; i < 10; ++i) digit[i + '0'] = i;
//	for (i = 0; i < 6; ++i) digit[i + 'A'] = 10 + i;
//	cin >> n;
//	for (i = 1; i <= n; ++i){
//		cin >> Num;
//		num[i] = get();
////		cout << num[i] << ' ';
//	}
//	memset(maxv, 0, sizeof maxv);
//	
//	ll ans = 0;
//	for (i = 1; i <= n; ++i) ans += num[i] ^ (i-1);
//	for (i = 1; i <= min(n, 2000); ++i){
//		for (j = i; j >= 1; --j){
//			dp[i][j] = maxv[j] + (num[i] ^ (j-1));
////			cout << maxv[j] << "    ??" <<  ' ' << (num[i]^j) << endl;
////			cout << i << ' ' << j << ' ' << dp[i][j] << endl;
//			ans = max(ans, dp[i][j]); 
//			maxv[j+1] = max(maxv[j+1], dp[i][j]);
//		}
//	}
////	sum[n+1] = tmp[n+1] = 0;
////	memset(tmp, 0, sizeof tmp);
////	for (i = n; i > 256; --i){
////		if (i + 256 <= n+1){
////			tmp[i] = tmp[i + 256];
////			for (j = i; j < i + 256; ++j) tmp[i] += num[j] ^ (j - i); 
////		}else{
////			for (j = i; j <= n; ++j) tmp[i] += num[j] ^ (j - i); 
////		}
////	}
////	for (i = 257; i <= n; ++i){
////		ll res = n - i + 1;
////		ll div = res / 256;
////		sum[i] = tmp[i] + (1 + div) * (div) / 2 * 256 * 256;
////		sum[i] += (div + 1) * 256 * (res - div * 256); 
////	}
////	for (i = 257; i <= n; ++i){
////		ans = max(ans, dp[i-1][256] + sum[i]);
////	}
//	cout << ans << endl;
//	return 0;
//}

