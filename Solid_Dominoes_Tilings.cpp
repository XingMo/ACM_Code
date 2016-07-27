/*
HDU - 5731
多米诺骨牌的矩形完全覆盖，
要求统计没有横切割线和竖切割线的方案数

第一部分就是轮廓线DP的入门裸题
预处理出任意矩形大小的方案数 RES[i][j]
不过我怀疑这部分不提前打表的过不了

第二部分是一个容斥
先对列容斥，用状压的方式枚举出所有列的分割情况
然后计算，当前列分割情况下，行没有分割的方案数 dp[n]
然后再用容斥，奇加偶减即能得出答案

而 dp[n]的求法为，设当前分割下，宽度为 x的无限制覆盖为 cnt[x]
cnt[x] = RES[x][bsiz_1]*RES[x][bsiz_2]*...*RES[x][bsiz_t]
其中 bsiz_1 ... bsiz_t为列分割线分割出的每一块的横向大小
dp[i] = cnt[i] - sigma_{j=0}^{i-1} dp[j]*cnt[i-j]
其中 cnt[i]为宽度为 i的任意覆盖，
减去每一个前 j个无行分割线，后 i-j个有行分割线的方案
减去这些互斥的非法方案，剩下的即为宽度为 i的无行分割线的合法覆盖
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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const int MOD=1e9+7;
LL RES[20][20];
LL dp[2][1<<16];

void init(int,int);
void VAL();
LL solve(int,int);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
//	for(int i=1; i<=16; i++) for(int j=1; j<=16; j++) init(i,j);
//	for(int i=1; i<=16; i++) for(int j=1; j<=16; j++) printf("RES[%d][%d] = %lld;\n", i, j, RES[i][j]);
	VAL();
	
	int N,M;
	while(~scanf("%d%d", &N, &M))
	{
		printf("%lld\n", solve(N,M));
	}
	return 0;
}

LL solve(int n, int m)
{
	LL res=0;
	int bcnt, bsiz, block[25];
	int dp[25];
	for(int cut=0; cut<(1<<m-1); cut++)
	{
		bcnt=0, bsiz=0;
		for(int i=0; i<m-1; i++)
		{
			if(cut&(1<<i))
			{
				block[bcnt++] = bsiz+1;
				bsiz=0;
			}
			else bsiz++;
		}
		block[bcnt++] = bsiz+1;
		for(int i=1; i<=n; i++)
		{
			for(int j=0; j<i; j++)
			{
				LL cnt=1;
				for(int k=0; k<bcnt; k++) cnt = (cnt * RES[i-j][block[k]]) % MOD;
				if(!j) dp[i] = cnt;
				else dp[i] = (dp[i]-cnt*dp[j])%MOD;
			}
		}
		if(bcnt&1) res = (res+dp[n])%MOD;
		else res = (res-dp[n])%MOD;
	}
	return (res+MOD)%MOD;
}

void init(int n, int m)
{
	int fmask=(1<<m)-1;
	CLR(dp);
	dp[0][fmask]=1;
	int cur=0, las=1;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
		{
			las=cur, cur^=1;
			CLR(dp[cur]);
			for(int ms=0; ms<1<<m; ms++) if(dp[las][ms])
			{
				if(!(ms&(1<<m-1))) 
				{
					dp[cur][( (ms<<1)|1 )&fmask] += dp[las][ms];
					dp[cur][( (ms<<1)|1 )&fmask] %= MOD;
				}
				else
				{
					dp[cur][ (ms<<1)&fmask ] += dp[las][ms];
					dp[cur][ (ms<<1)&fmask ] %= MOD;
					if(j && !(ms&1))
					{
						dp[cur][ ((ms<<1)|3)&fmask ] += dp[las][ms];
						dp[cur][ ((ms<<1)|3)&fmask ] %= MOD;
					}
				}
			}
		}
	}
	RES[n][m] = dp[cur][fmask];
}

void VAL()
{
	RES[1][1] = 0;
	RES[1][2] = 1;
	RES[1][3] = 0;
	RES[1][4] = 1;
	RES[1][5] = 0;
	RES[1][6] = 1;
	RES[1][7] = 0;
	RES[1][8] = 1;
	RES[1][9] = 0;
	RES[1][10] = 1;
	RES[1][11] = 0;
	RES[1][12] = 1;
	RES[1][13] = 0;
	RES[1][14] = 1;
	RES[1][15] = 0;
	RES[1][16] = 1;
	RES[2][1] = 1;
	RES[2][2] = 2;
	RES[2][3] = 3;
	RES[2][4] = 5;
	RES[2][5] = 8;
	RES[2][6] = 13;
	RES[2][7] = 21;
	RES[2][8] = 34;
	RES[2][9] = 55;
	RES[2][10] = 89;
	RES[2][11] = 144;
	RES[2][12] = 233;
	RES[2][13] = 377;
	RES[2][14] = 610;
	RES[2][15] = 987;
	RES[2][16] = 1597;
	RES[3][1] = 0;
	RES[3][2] = 3;
	RES[3][3] = 0;
	RES[3][4] = 11;
	RES[3][5] = 0;
	RES[3][6] = 41;
	RES[3][7] = 0;
	RES[3][8] = 153;
	RES[3][9] = 0;
	RES[3][10] = 571;
	RES[3][11] = 0;
	RES[3][12] = 2131;
	RES[3][13] = 0;
	RES[3][14] = 7953;
	RES[3][15] = 0;
	RES[3][16] = 29681;
	RES[4][1] = 1;
	RES[4][2] = 5;
	RES[4][3] = 11;
	RES[4][4] = 36;
	RES[4][5] = 95;
	RES[4][6] = 281;
	RES[4][7] = 781;
	RES[4][8] = 2245;
	RES[4][9] = 6336;
	RES[4][10] = 18061;
	RES[4][11] = 51205;
	RES[4][12] = 145601;
	RES[4][13] = 413351;
	RES[4][14] = 1174500;
	RES[4][15] = 3335651;
	RES[4][16] = 9475901;
	RES[5][1] = 0;
	RES[5][2] = 8;
	RES[5][3] = 0;
	RES[5][4] = 95;
	RES[5][5] = 0;
	RES[5][6] = 1183;
	RES[5][7] = 0;
	RES[5][8] = 14824;
	RES[5][9] = 0;
	RES[5][10] = 185921;
	RES[5][11] = 0;
	RES[5][12] = 2332097;
	RES[5][13] = 0;
	RES[5][14] = 29253160;
	RES[5][15] = 0;
	RES[5][16] = 366944287;
	RES[6][1] = 1;
	RES[6][2] = 13;
	RES[6][3] = 41;
	RES[6][4] = 281;
	RES[6][5] = 1183;
	RES[6][6] = 6728;
	RES[6][7] = 31529;
	RES[6][8] = 167089;
	RES[6][9] = 817991;
	RES[6][10] = 4213133;
	RES[6][11] = 21001799;
	RES[6][12] = 106912793;
	RES[6][13] = 536948224;
	RES[6][14] = 720246619;
	RES[6][15] = 704300462;
	RES[6][16] = 289288426;
	RES[7][1] = 0;
	RES[7][2] = 21;
	RES[7][3] = 0;
	RES[7][4] = 781;
	RES[7][5] = 0;
	RES[7][6] = 31529;
	RES[7][7] = 0;
	RES[7][8] = 1292697;
	RES[7][9] = 0;
	RES[7][10] = 53175517;
	RES[7][11] = 0;
	RES[7][12] = 188978103;
	RES[7][13] = 0;
	RES[7][14] = 124166811;
	RES[7][15] = 0;
	RES[7][16] = 708175999;
	RES[8][1] = 1;
	RES[8][2] = 34;
	RES[8][3] = 153;
	RES[8][4] = 2245;
	RES[8][5] = 14824;
	RES[8][6] = 167089;
	RES[8][7] = 1292697;
	RES[8][8] = 12988816;
	RES[8][9] = 108435745;
	RES[8][10] = 31151234;
	RES[8][11] = 940739768;
	RES[8][12] = 741005255;
	RES[8][13] = 164248716;
	RES[8][14] = 498190405;
	RES[8][15] = 200052235;
	RES[8][16] = 282756494;
	RES[9][1] = 0;
	RES[9][2] = 55;
	RES[9][3] = 0;
	RES[9][4] = 6336;
	RES[9][5] = 0;
	RES[9][6] = 817991;
	RES[9][7] = 0;
	RES[9][8] = 108435745;
	RES[9][9] = 0;
	RES[9][10] = 479521663;
	RES[9][11] = 0;
	RES[9][12] = 528655152;
	RES[9][13] = 0;
	RES[9][14] = 764896039;
	RES[9][15] = 0;
	RES[9][16] = 416579196;
	RES[10][1] = 1;
	RES[10][2] = 89;
	RES[10][3] = 571;
	RES[10][4] = 18061;
	RES[10][5] = 185921;
	RES[10][6] = 4213133;
	RES[10][7] = 53175517;
	RES[10][8] = 31151234;
	RES[10][9] = 479521663;
	RES[10][10] = 584044562;
	RES[10][11] = 472546535;
	RES[10][12] = 732130620;
	RES[10][13] = 186229290;
	RES[10][14] = 274787842;
	RES[10][15] = 732073997;
	RES[10][16] = 320338127;
	RES[11][1] = 0;
	RES[11][2] = 144;
	RES[11][3] = 0;
	RES[11][4] = 51205;
	RES[11][5] = 0;
	RES[11][6] = 21001799;
	RES[11][7] = 0;
	RES[11][8] = 940739768;
	RES[11][9] = 0;
	RES[11][10] = 472546535;
	RES[11][11] = 0;
	RES[11][12] = 177126748;
	RES[11][13] = 0;
	RES[11][14] = 513673802;
	RES[11][15] = 0;
	RES[11][16] = 881924366;
	RES[12][1] = 1;
	RES[12][2] = 233;
	RES[12][3] = 2131;
	RES[12][4] = 145601;
	RES[12][5] = 2332097;
	RES[12][6] = 106912793;
	RES[12][7] = 188978103;
	RES[12][8] = 741005255;
	RES[12][9] = 528655152;
	RES[12][10] = 732130620;
	RES[12][11] = 177126748;
	RES[12][12] = 150536661;
	RES[12][13] = 389322891;
	RES[12][14] = 371114062;
	RES[12][15] = 65334618;
	RES[12][16] = 119004311;
	RES[13][1] = 0;
	RES[13][2] = 377;
	RES[13][3] = 0;
	RES[13][4] = 413351;
	RES[13][5] = 0;
	RES[13][6] = 536948224;
	RES[13][7] = 0;
	RES[13][8] = 164248716;
	RES[13][9] = 0;
	RES[13][10] = 186229290;
	RES[13][11] = 0;
	RES[13][12] = 389322891;
	RES[13][13] = 0;
	RES[13][14] = 351258337;
	RES[13][15] = 0;
	RES[13][16] = 144590622;
	RES[14][1] = 1;
	RES[14][2] = 610;
	RES[14][3] = 7953;
	RES[14][4] = 1174500;
	RES[14][5] = 29253160;
	RES[14][6] = 720246619;
	RES[14][7] = 124166811;
	RES[14][8] = 498190405;
	RES[14][9] = 764896039;
	RES[14][10] = 274787842;
	RES[14][11] = 513673802;
	RES[14][12] = 371114062;
	RES[14][13] = 351258337;
	RES[14][14] = 722065660;
	RES[14][15] = 236847118;
	RES[14][16] = 451896972;
	RES[15][1] = 0;
	RES[15][2] = 987;
	RES[15][3] = 0;
	RES[15][4] = 3335651;
	RES[15][5] = 0;
	RES[15][6] = 704300462;
	RES[15][7] = 0;
	RES[15][8] = 200052235;
	RES[15][9] = 0;
	RES[15][10] = 732073997;
	RES[15][11] = 0;
	RES[15][12] = 65334618;
	RES[15][13] = 0;
	RES[15][14] = 236847118;
	RES[15][15] = 0;
	RES[15][16] = 974417347;
	RES[16][1] = 1;
	RES[16][2] = 1597;
	RES[16][3] = 29681;
	RES[16][4] = 9475901;
	RES[16][5] = 366944287;
	RES[16][6] = 289288426;
	RES[16][7] = 708175999;
	RES[16][8] = 282756494;
	RES[16][9] = 416579196;
	RES[16][10] = 320338127;
	RES[16][11] = 881924366;
	RES[16][12] = 119004311;
	RES[16][13] = 144590622;
	RES[16][14] = 451896972;
	RES[16][15] = 974417347;
	RES[16][16] = 378503901;
}

