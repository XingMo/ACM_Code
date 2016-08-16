/*
HDU - 5782
给定两个长度相等的字符串
问他们的第 i个前缀是否循环相等
循环相等的定义是，两个长度相等的字符串
其中一个字符串能通过循环移位得到另一个

按照题解的说法，如果两个字符串循环相等
将 A串拆成前缀和后缀，交换位置就能得到 B串

然后我对着题解懵逼了一小时，没懂接下来怎么做
还好 lcy打野强力辅助，我终于懂了一点

利用一个 bitset，先预处理出 26个字母在 A，B串的分布
Ap[i][j]表示 A串长度为 i的前缀能在 B串的 j位置找到匹配
Bp同理，Bp[i][j]为 B串长度为 i的前缀能在 A串的 j位置匹配

接下在 A串中枚举后缀开始的位置 i，利用二分以及 Bp来判断
A串从 i位置开始，最远能在 B串中匹配到什么位置
然后把 Ap[i-1]的这些位置取出来，移位一下，就能得到从 i位置拆开
能对答案的哪些位置造成贡献，最后或到答案上即可

有几个注意点：
1. 二分要特判一下无解的情况
2. 要特判一下前 i位全部相等的情况
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
#define PCUT puts("\n----------")

const int maxn=1e4+10;
//const int maxn=10;

char A[maxn], B[maxn];
bitset<maxn> posA[26], posB[26], 
Ap[maxn], Bp[maxn], ans, tem, pre[maxn];

int main()
{
    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    #endif
    
    for(int i=1; i<maxn; i++) pre[i] = pre[i-1].set(i-1);
    while(~scanf(" %s %s", A, B))
    {
        int N=strlen(A);
        for(int i=0; i<26; i++) posA[i].reset(), posB[i].reset();
        
        for(int i=0; i<N; i++)
        {
            posA[A[i]-'a'][i] = 1;
            posB[B[i]-'a'][i] = 1;
        }
        
        Ap[0] = posB[A[0]-'a'];
        Bp[0] = posA[B[0]-'a'];
        for(int i=1; i<N; i++) Bp[i] = Bp[i-1] & (posA[B[i]-'a']>>i);
        
        ans.reset(); tem.reset();
        bool all = A[0]==B[0];
        if(all) ans[0]=1;
        for(int i=1; i<N; i++)
        {
            Ap[i] = Ap[i-1] & (posB[A[i]-'a']>>i);
            int l=0, r=N-1;
            while(l<r)
            {
                int mid=(l+r+1)>>1;
                if(!Bp[mid][i]) r=mid-1;
                else l=mid;
            }
			all &= A[i]==B[i];
			if(all) ans[i]=1;
            if(l==0 && A[i] != B[0]) continue;
            ans |= (Ap[i-1]&pre[l+1]) << (i-1);
        }
        for(int i=0; i<N; i++) putchar(ans[i]+'0');
        puts("");
    }
    return 0;
}

