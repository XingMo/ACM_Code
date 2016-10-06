
//
//  Created by Running Photon
//  Copyright (c) 2015 Running Photon. All rights reserved.
//
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <complex>
#include <queue>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <stack>
#define ALL(x) x.begin(), x.end()
#define INS(x) inserter(x, x,begin())
#define ll __int128
#define CLR(x) memset(x, 0, sizeof x)
using namespace std;
const ll inf = 0x5fffffffffffffff;
const ll P = 180143985094819841LL;
const ll G = 6;
const int maxn = 1e6 + 5000;
const int maxv = 1e3 + 10;
const long double eps = 1e-9;
const long double PI = acos(-1);

inline ll Pow(ll x, ll n) {
    ll ret = 1;
    while(n)
    {
        if(n&1) ret = ret*x%P;
        x = x*x%P;
        n >>= 1;
    }
    return ret;
}

void ntt(ll A[], int n, int dir)
{
	for(int i=0,j=0; i<n; i++)
	{
		if(i<j) swap(A[i], A[j]);
		for(int k=n>>1; (j^=k)<k; k>>=1);
	}
	
	for(int len=2; len<=n; len<<=1)
	{
		int m = len>>1;
		ll wn = Pow(G, (P-1)/len);
		if(dir==-1) wn = Pow(wn, P-2);
		for(int i=0; i<n; i+=len)
		{
			ll w = 1;
			for(int j=0; j<m; j++)
			{
				ll z = A[i+m+j]*w%P;
				A[i+m+j] = (A[i+j] - z)%P;
				A[i+j] = (A[i+j] + z)%P;
				w = w*wn%P;
			}
		}
	}
	if(dir==-1)
	{
		ll inv=Pow(n, P-2);	
		for(int i=0; i<n; i++) A[i] = A[i]*inv%P;
	}
}

void conv(ll A[], ll B[], int n)
{
	int len = 1;
	while(len < n << 2) len <<= 1;
	ntt(A, len, 1);
	ntt(B, len, 1);
	for(int i = 0; i < len; i++) A[i] = A[i]*B[i]%P;
	ntt(A, len, -1);
}

ll A[maxn], B[maxn];
int main() {
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	
	#endif
	// ios_base::sync_with_stdio(0);
	int T; scanf("%d", &T);
	for(int ck=1; ck<=T; ck++){
		CLR(A); CLR(B);
		int n; scanf("%d", &n);
		for(int i = n - 1, x; i>=0; i--){
			scanf("%d", &x);
			A[i] = x;
		}
		for(int i = 0, x; i < n; i++) {
			scanf("%d", &x);
			B[i+n] = B[i] = x;
		}
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			ans += A[i]*A[i] + B[i]*B[i];
		}
		conv(A,B,n);
		ll res = 0;
		for(int i = 0; i < n; i++) {
			res = max(res, A[i+n-1]);
		}
		long long outp = (ans - res * 2 % P + P) % P;
		printf("%lld\n", outp);
	}

	return 0;
}

