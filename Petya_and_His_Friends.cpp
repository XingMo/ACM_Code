/*
Codeforces - 66D
构造 N个数，使得其中任意两个不互质，
任意两个不相等，并且所有数的GCD=1

如果构造的方法不机智，那么做法就是错的
我原来的做法是，构造前 N-1个数为 2乘以一个质数
2*3、2*5、2*7……然后最后一个数是 3*5*7……
这样前 N-1个数互相不互质，第 N个数与前面的数也都不互质
并且所有数的 GCD=1

但是这样太蠢了，最后一个数要用高精度
尤其在CF这种地方，手写一个高精度简直是致命的

接下来是lcy的机智做法
前三个数分别是 2*3、3*5、2*5，这样前三个数已经互质了
剩下的数全是 2*3*5的倍数
无论从编程复杂度，时间复杂度，空间复杂度都完爆了我的做法……
*/
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
#include <bitset>
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("----------")

const int maxn=5e2;
bool sieve[maxn];
vector<int> prime;
void init();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	init();
	
	int N;
	scanf("%d", &N);
	if(N==2){puts("-1"); return 0;}
	printf("%d\n%d\n%d\n", 6, 10, 15);
	for(int i=4; i<=N; i++) printf("%d\n", 30*(i-2));
	return 0;
}

void init()
{
	for(int i=2; i<maxn; i++) if(!sieve[i])
	{
		prime.push_back(i);
		for(int j=i*i; j<maxn; j+=i) sieve[j]=1;
	}
}

