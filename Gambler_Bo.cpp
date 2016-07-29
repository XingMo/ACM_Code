/*
HDU - 5755
给定一个 N*M的矩阵，每个格子都有一个数，
并且这些数都是 mod 3的
每次选一个格子操作，可以在这个格子加 2 mod 3
在周围 4个格子加 1 mod 3
问如何操作使得所有格子均为 0

类似于开关问题，但是这个 N，M比较大
所以没办法状压dp
但是可以用列方程组用高斯消元求解
但是这个方程最多有 900个，并且消元复杂度是 O(N^3)的
看起来要 T，实际上跑得还挺快的，我 500ms左右就跑出来了

据大爷的讲解，是因为这个方程组里，
每个方程涉及到的变量较少，所以实际上消元的次数并不会很多
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

LL GCD(LL a,LL b){return b?GCD(b,a%b):a;}
LL Pow(LL x,LL n,LL p)
{
	LL res=1;
	while(n)
	{
		if(n&1) res=res*x%p;
		x=x*x%p;
		n>>=1;
	}
	return res;
}

const int MOD=3;
const int maxn=40;
const int dir[4][2]={0,1,0,-1,1,0,-1,0};
struct AMatrix
{
	static const int size = maxn*maxn;
	static const int MOD = 3;
	int row, col, n[size][size+1], x[size];
	void construct();
	int gauss();
	void pri()
	{
		for(int i=0; i<row; i++,puts("")) for(int j=0; j<=col; j++)
			printf("%d ", n[i][j]);
	}
};

int N,M;
int inpt[maxn][maxn];
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
		scanf("%d%d", &N, &M);
		for(int i=0; i<N; i++) for(int j=0; j<M; j++) scanf("%d", &inpt[i][j]);
		am.construct();
		am.gauss();
		int ans=0;
		for(int i=0; i<am.row; i++) ans += am.x[i];
		
		printf("%d\n", ans);
		for(int i=0; i<am.row; i++) for(int j=0; j<am.x[i]; j++)
			printf("%d %d\n", i/M+1, i%M+1);
	}
	return 0;
}

void AMatrix::construct()
{
	CLR(n);
	row = 0; col = N*M;
	for(int i=0; i<N; i++) for(int j=0; j<M; j++)
	{
		n[row][col] = -inpt[i][j]+MOD;
		n[row][i*M+j] = 2;
		for(int k=0; k<4; k++)
		{
			int x = i+dir[k][0], y = j+dir[k][1];
			if(x>=0 && x<N && y>=0 && y<M) n[row][x*M+y] = 1;
		}
		row++;
	}
}

int AMatrix::gauss()
{
	int r,c;
	for(r=0,c=0; r<row && c<col; c++)
	{
		int tmax = r;
		for(int i=r+1; i<row; i++) if( abs(n[i][c]) > abs(n[tmax][c]) ) tmax=i;
		if(tmax != r) for(int i=c; i<col+1; i++) swap( n[r][i], n[tmax][i] );
		if( !n[r][c] ) continue;
		for(int i=r+1; i<row; i++) if( n[i][c] )
		{
			// MOD is a prime
			int lcm = n[r][c] *Pow(GCD(n[r][c], n[i][c]), MOD-2, MOD) *n[i][c];
			int ti = lcm *Pow(n[i][c], MOD-2, MOD), tr = lcm *Pow(n[r][c], MOD-2, MOD);
			for(int j=c; j<col+1; j++)
				n[i][j] = ( (n[i][j]*ti%MOD - n[r][j]*tr%MOD) + MOD)%MOD;
		}
		r++;
	}
	for(int i=r; i<row; i++) if(n[i][col]) return -1;
	
	for(int i=r-1; i>=0; i--)
	{
		x[i] = n[i][col];
		for(int j=i+1; j<col; j++)
		{
			x[i] = ( (x[i] - n[i][j]*x[j])%MOD + MOD)%MOD;
		}
		x[i] = x[i]*Pow(n[i][i], MOD-2, MOD)%MOD;
	}
	return row-r-1; // return the number of free variable
}
