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
#include <string>
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

const int maxn=1e5+10;
struct data
{
	char name[30];
	int a;
	bool operator < (const data &v) const
	{
		if(a != v.a) return a > v.a;
		return strcmp(name, v.name) < 0;
	}
} inpt[maxn], temp[maxn];
int point[maxn];
char me[maxn];

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int N, M;
	scanf("%d", &N);
	for(int i=0; i<N; i++)
	{
		scanf(" %s %d", inpt[i].name, &inpt[i].a);
	}
	scanf("%d", &M);
	for(int i=0; i<M; i++)
	{
		scanf("%d", &point[i]);
	}
	sort(point, point+N);
	scanf("%s", me);
	for(int i=0; i<N; i++) if(!strcmp(me, inpt[i].name))
	{
		if(i!=N-1) swap(inpt[N-1], inpt[i]);
		break;
	}
	sort(inpt+1, inpt+N);
	
	int high, low;
	for(int i=0; i<N; i++) temp[i] = inpt[i];
	for(int i=0; i<N; i++) temp[i].a += point[i];
	sort(temp, temp+N);
	for(int i=0; i<N; i++) if(!strcmp(temp[i].name, me)) {high = i+1; break;}
	
	for(int i=0; i<N; i++) temp[i] = inpt[i];
	for(int i=0; i<N; i++) temp[i].a += point[N-i-1];
	sort(temp, temp+N);
	for(int i=0; i<N; i++) if(!strcmp(temp[i].name, me)) {low = i+1; break;}
	
	printf("%d %d\n", high, low);
	
	return 0;
}

