#pragma comment(linker, "/STACK:102400000,102400000")
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define LL long long
using namespace std;
const int M = 5005, INF = 0x3f3f3f3f,mod=1e9+7;
int dp[M][M];
int sum[M][M];
int A[M];
int nxt[M][M],pre[M];
int maxx[M],tot[M];
void compress(int n){
    vector<int>C;
    for(int j=1;j<=n;j++) C.push_back(A[j]);
    sort(C.begin(),C.end());
    C.erase(unique(C.begin(),C.end()),C.end());
    for(int j=1;j<=n;j++) A[j]=lower_bound(C.begin(),C.end(),A[j])-C.begin()+1;
}
int main(){
	freopen("in.txt", "r", stdin);
//	freopen("stdout.txt", "w", stdout);
    int n;
    while(scanf("%d",&n)!=EOF){
        memset(sum,0,sizeof(sum));
        memset(dp,0,sizeof(dp));
        memset(maxx,0,sizeof(maxx));
        memset(tot,0,sizeof(tot));
        for(int j=1;j<=n;j++) scanf("%d",&A[j]);
        compress(n);
        for(int j=n;j>=0;j--){
            for(int k=1;k<=n;k++) nxt[j][k]=nxt[j+1][k];
            nxt[j][A[j]]=j;
        }
        vector<int>B;
        for(int j=1;j<=n;j++){
            dp[j][j]=1;
            sum[j][j]=1;
        }
        for(int j=n;j>=1;j--){
            memset(pre,0,sizeof(pre));
            int tot=1,maxx=0;
            for(int k=j+1;k<=n;k++){
                if(A[j]==A[k]){
                    if(maxx+2>dp[j][k]){
                        dp[j][k]=maxx+2;
                        sum[j][k]=tot;
                    }
                    else if(maxx==dp[j][k]) sum[j][k]=(sum[j][k]+tot)%mod;
                }
                if(A[k]<=A[j]){
                    int t=nxt[j+1][A[k]];
                    if(!t) continue;
                    //if(j==1) printf("t = %d k = %d dp = %d sum = %d\n",t,k,dp[t][k],sum[t][k]);
                    if(dp[t][k]>maxx){
                        maxx=dp[t][k];
                        tot=sum[t][k];
                    }
                    else if(dp[t][k]==maxx){
                        int p=pre[A[k]];
                        //if(j==1) printf("k = %d pre = %d %d %d %d\n",k,p,dp[t][k],dp[t][p]);
                        if(p&&dp[t][k]==dp[t][p]) tot-=sum[t][p];
                        if(tot<0) tot+=mod;
                        tot=(tot+sum[t][k])%mod;
                    }
                }
                pre[A[k]]=k;
                //if(j==1&&k==5) printf("%d %d\n",maxx,tot);
            }
        }
        //printf("sum = %d\n",sum[2][4]);
        int ans=0,ans1=0;
        for(int j=1;j<=n;j++){
            int l=-1,r=-1;
            for(int k=n;k>=1;k--){
                if(A[k]==j){
                    r=k;
                    break;
                }
            }
            for(int k=1;k<=n;k++){
                if(A[k]==j){
                    l=k;
                    break;
                }
            }
            if(l==-1||r==-1)continue;
            if(dp[l][r]>ans){
                ans=dp[l][r];
                ans1=sum[l][r];
            }
            else if(dp[l][r]==ans) ans1=(sum[l][r]+ans1)%mod;
//            printf("%d %d %d %d\n",ans,sum[l][r],l,r);
        }
        printf("%d %d\n",ans,ans1);
    }
    return 0;
}
