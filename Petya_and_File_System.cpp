/*
Codeforces - 66C
给若干个文件路径，问子文件夹以及子文件最多为多少

模拟题，可以直接用文件的绝对路径来表示一个文件
这样就不用担心不同路径文件的重名问题，也不用建树了
其次子文件夹和子文件数最多的肯定是根目录下的文件夹
用set维护一下这些文件夹的情况即可，set的好处是不用去重
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


int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	string root, buff;
	map<string, set<string>> folder, files;
	while(cin >> buff)
	{
		int flr=0;
		for(int i=0; i<(int)buff.size(); i++)
		{
			if(buff[i]=='\\')
			{
				flr++;			
				if(flr==2) root = buff.substr(0,i);
				else if(flr>2) folder[root].insert(buff.substr(0,i));
			}
		}
		files[root].insert(buff);
	}
	int ans0=0, ans1=0;
	for(auto &pr:folder) ans0 = max(ans0, (int)pr.second.size());
	for(auto &pr:files)  ans1 = max(ans1, (int)pr.second.size());
	printf("%d %d\n", ans0, ans1);
	return 0;
}

