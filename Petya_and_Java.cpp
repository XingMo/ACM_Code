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

char str[110];

bool tr(const char*,const char*,int,char*);

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	scanf("%s", str);
	int stp=0,len=strlen(str);
	if(str[0]=='-') stp++, len--;
	if(len<=3)
	{
		if(tr("128","127",stp,str+stp)) puts("byte");
		else puts("short");
	}
	else if(len<=5)
	{
		//- 32768 to 32767
		if(tr("32768","32767",stp,str+stp)) puts("short");
		else puts("int");
	}
	else if(len<=10)
	{
		//- 2147483648 to 2147483647
		if(tr("2147483648","2147483647",stp,str+stp)) puts("int");
		else puts("long");
	}
	else if(len<=19)
	{
		//- 9223372036854775808 to 9223372036854775807
		if(tr("9223372036854775808", "9223372036854775807",stp,str+stp)) puts("long");
		else puts("BigInteger");
	}
	else puts("BigInteger");
	return 0;
}

char buff[2][110];
bool tr(const char down[], const char up[], int neg,char str[])
{
	CLR(buff);
	for(int i=0; i<100; i++) buff[0][i] = buff[1][i] = '0';
	int len=strlen(str);
	for(int i=0; i<len; i++) buff[0][100-len+i] = str[i];
	if(!neg)
	{
		int nlen=strlen(up);
		for(int i=0; i<nlen; i++) buff[1][100-nlen+i] = up[i];
		if(strcmp(buff[1],buff[0])>=0) return 1;
		else return 0;
	}
	else
	{
		int nlen=strlen(down);
		for(int i=0; i<nlen; i++) buff[1][100-nlen+i] = down[i];
		puts(buff[1]);
		puts(buff[0]);
		if(strcmp(buff[1],buff[0])>=0) return 1;
		else return 0;
	}
}

