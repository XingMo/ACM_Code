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
#include <cassert>
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

int gcd(int a,int b){return b?gcd(b,a%b):a;}
const int maxn=110;
const DBL eps=1e-8;
struct AMatrix
{
	int row, col, first[maxn];
	DBL n[maxn][maxn+1], x[maxn];
	void construct(int*);
	int gauss();
	void pri()
	{
		for(int i=0; i<row; i++,puts("")) for(int j=0; j<=col; j++)
			printf("%.1f ", n[i][j]); 
	}
};
int to[maxn];
AMatrix am;

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
		CLR(to);
		int N;
		scanf("%d", &N);
		for(int i=1,f,t; i<=N; i++)
		{
			scanf("%d%d", &f, &t);
			to[f]=t;
		}
		am.construct(to);
		am.gauss();
		printf("Case %d: %.7f\n", ck, am.x[0]);
	}
	return 0;
}

void AMatrix::construct(int to[])
{
	CLR(n);
	row=0,col=100;
	for(int i=1; i<100; i++)
	{
		if(to[i]) 
		{
			n[row][row]=1, n[row][to[i]-1]=-1;
		}
		else
		{
			int cnt = min(6, 100-i);
			for(int j=1; j<=cnt; j++) n[row][row+j] = -1;
			n[row][row] = cnt;
			n[row][col] = 6;
		}
		row++;
	}
	n[row][row] = 1;
	row++;
}

int AMatrix::gauss()
{ 
	CLR(x); CLR(first);
	int r,c;
	for(r=0,c=0; r<row && c<col; c++)
	{
		int tmax = r;
		for(int i=r+1; i<row; i++) if( abs(n[i][c]) > abs(n[tmax][c]) ) tmax=i;
		if(tmax != r) for(int i=c; i<col+1; i++) swap( n[r][i], n[tmax][i] );
		if( abs(n[r][c])<eps ) continue;
		first[r] = c;
		for(int i=r+1; i<row; i++) 
		{
			if( abs(n[i][c])<=eps ) continue;
			DBL rate = n[i][c]/n[r][c];
			for(int j=c; j<col+1; j++)
				n[i][j] -= rate*n[r][j];
		}
		r++;
	}
	
	for(int i=r; i<row; i++) if( abs(n[i][col])>eps ) return -1;
	
	for(int i=r-1; i>=0; i--)
	{
		int p=first[i];
		x[p] = n[i][col];
		for(int j=p+1; j<col; j++) if( abs(n[i][j])>eps )
		{
			x[p] = x[p] - n[i][j]*x[j];
		}
		x[p] = x[p] /n[i][p];
	}
	return row-r;
}

