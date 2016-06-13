//
//  Created by  CQU_CST_WuErli
//  Copyright (c) 2016 CQU_CST_WuErli. All rights reserved.
//
//#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <algorithm>
#include <sstream>
#define CLR(x) memset(x,0,sizeof(x))
#define OFF(x) memset(x,-1,sizeof(x))
#define MEM(x,a) memset((x),(a),sizeof(x))
#define BUG cout << "I am here" << endl
#define lookln(x) cout << #x << "=" << x << endl
#define SI(a) scanf("%d", &a)
#define SII(a,b) scanf("%d%d", &a, &b)
#define SIII(a,b,c) scanf("%d%d%d", &a, &b, &c)
const int INF_INT=0x3f3f3f3f;
const long long INF_LL=0x7f7f7f7f;
const long long MOD = 72807249;
const double eps=1e-10;
const double pi=acos(-1);
typedef long long  ll;
using namespace std;

int n;
struct Q
{
	int op;
	ll b;
	Q(int a, ll aa):op(a), b(aa) {}
	Q() {}
};
vector<Q> q;
ll sum[200020 * 6];

void push_up(int rt) {
	sum[rt] = sum[rt << 1] * sum[rt << 1 | 1] % MOD;
}

void build(int l, int r, int rt) {
	sum[rt] = 1;
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, rt << 1);
	build(mid + 1, r, rt << 1 | 1);
	push_up(rt);
}

void change(int o, ll v, int l, int r, int rt) {
	if (l == r) {
		sum[rt] = v % MOD;
		return;
	}
	int mid = (l + r) >> 1;
	if (o <= mid) change(o, v, l, mid, rt << 1);
	else change(o, v, mid + 1, r, rt << 1 | 1);
	push_up(rt);
}


int main(int argc, char const *argv[]) {
#ifdef LOCAL
    freopen("C:\\Users\\john\\Desktop\\in.txt","r",stdin);
    // freopen("C:\\Users\\john\\Desktop\\out.txt","w",stdout);
#endif
    int t; SI(t);
    while(t--) {
        SI(n);
        build(1, n, 1);
        int pos = 0;
        // BUG;
        for (int i = 1; i <= n; i++) {
        	int op;
        	SI(op);
        	if (op == 1) {
        		ll num; scanf("%lld", &num);
        		pos++;
        		change(pos, num, 1, n, 1);
        	}
        	else {
        		int cnt; SI(cnt);
        		change(cnt, 1LL, 1, n, 1);
        	}
        	printf("%lld\n", sum[1] % MOD);
        }
    }
	return 0;
}
