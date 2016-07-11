#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <stack>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <string>
#include <cmath>
using namespace std;
#define ll long long
#define rep(i,n) for(int i =0; i < n; ++i)
#define CLR(x) memset(x,0,sizeof x)
#define MEM(a,b) memset(a,b,sizeof a)
#define pr(x) cout << #x << " = " << x << " ";
#define prln(x) cout << #x << " = " << x <<  endl; 
#define ull unsigned long long
const int maxn = 1100;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;
const int N = 8000;
int main(){
	freopen("in.txt", "w",stdout);
	ull  n, m, x, y;
    int t = 0;
	for(int i = 2; i <= N; i = i*2){
		t++;
	}
//    t+=2;
	printf("%d\n",t);
	for(int i = 2; i <= N; i = i*2){
		printf("%d %d\n", i, i);
		for(int j = 0; j < i; ++j){
			x = rand()%MOD;
			y = rand()%MOD;
			printf("%llu", (x<<32)+y);
			if(j == i-1) printf("\n");
			else printf(" ");
		}
		for(int j = 1; j <= i; ++j){
			int z = rand()%i;
			z = z;
			z = min(i, z+j);
			printf("%d %d\n", j, z);
		}
	}
//    printf("%d %d\n", N, N);
//    for(int i = 1; i <= N; ++i){
//        printf("%d%c", i, (i==N?'\n':' '));
//    }
//    for(int i = 1; i <= N; ++i){
//        printf("%d %d\n", i, N);
//    }

//    printf("%d %d\n", N, N);
//    for(int i = 1; i <= N; ++i){
//        printf("%d%c", i, (i==N?'\n':' '));
//    }
//    for(int i = 1; i <= N; ++i){
//        printf("%d %d\n", 1, i);
//    }
	return 0;
}
