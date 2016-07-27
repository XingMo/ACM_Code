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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))



int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	int t;cin >> t;
	while(t--){
		int n;cin >> n;
		int cnt = 0;
		long long cnt1 = 0;
		for(int i=1;i<=n;i++){
			int a;cin >> a;
			cnt1 += a/2;
			cnt += a&1;
		}
		if(cnt){
			cout << cnt1/cnt*2+1 << '\n';
		}
		else cout << cnt1*2 << '\n';
	}
	return 0;
}

