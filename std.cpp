#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
  
int N,K;  
double dp[1010][16];  
  
double f(int n,int k)//确定区间长度为N的X，有k个蛋，返回的是扔的次数的期望  
{  
    if(dp[n][k]>0) return dp[n][k];  
    if(n==1) return 0;  
    if(k==0) return 0x3f3f3f3f;  
    double ans=0x3f3f3f3f;  
    for(int i=1;i<n;i++)//假设这次我从i扔下去  
    {  
        double p1=(double)i/n;//有p1的几率会烂  
        double exception=f(i,k-1)*p1//烂了，然后下楼  
                        +f(n-i,k)*(1-p1);//没烂，上楼  
        ans=min(ans,exception);  
    }  
    //printf("f(%d,%d)=%.5f\n",n,k,ans+1);  
    return dp[n][k]=ans+1;  
}  
int main()  
{  
	freopen("in.txt", "r", stdin);
    memset(dp,0,sizeof(dp));  
    scanf("%d%d",&N,&K);  
    printf("%.5lf\n",f(N,K));  
    return 0;  
} 
