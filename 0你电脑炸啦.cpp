#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
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
#define Sqr(a) (a*a)

const int px[9]={0,0,0,1,1,1,2,2,2};
const int py[9]={0,1,2,0,1,2,0,1,2};
int perm[9];
char inpt[4][4];
char Map[4][4];

bool check();
bool cut(int);
void pause(){fflush(stdin);getchar();}

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		for(int i=0; i<4; i++) for(int j=0; j<4; j++) scanf(" %c", &inpt[i][j]);
		for(int i=0; i<9; i++) perm[i]=i;
		bool ok=0;
		while(1)
		{
			if(check()){ok=1; break;}
			if(!next_permutation(perm,perm+9)) break;
		}
		if(ok) puts("Lucky dog!");
		else puts("BOOM!");
	}
	
	return 0;
}

bool check()
{
	for(int i=0; i<4; i++) for(int j=0; j<4; j++) Map[i][j]=inpt[i][j];
	for(int i=0; i<9; i++)
	{
		bool ok=cut(perm[i]);
//		puts("cut");
//		for(int i=0; i<4; i++) {for(int j=0; j<4; j++) putchar(Map[i][j]);puts("");}
		if(!ok) return 0;
	}
	return 1;
}

bool cut(int num)
{
	for(int i=0; i<2; i++) for(int j=0; j<2; j++)
	{
		int x=px[num]+i, y=py[num]+j;
		if(Map[x][y]-'1'==num || Map[x][y]=='0') Map[x][y]='0';
		else return 0;
	}
	return 1;
}
