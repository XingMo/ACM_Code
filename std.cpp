#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MOD 12345678
using namespace std;
const int dx[]={-1,-1,-1,0,0,1,1,1,0};
const int dy[]={-1,0,1,-1,1,-1,0,1,0};
int n,m,ans;
char s[10][10];
int Calculate()
{
    static pair<int,int> stack[10];
    static int cnt[1<<8],f[30][1<<8];
    int i,j,k,sta,top=0;
    memset(cnt,0,sizeof cnt);
    memset(f,0,sizeof f);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(s[i][j]=='X')
                stack[++top]=pair<int,int>(i,j);
    for(sta=0;sta<1<<top;sta++)
    {
        static bool unfilled[10][10];
        memset(unfilled,0,sizeof unfilled);
        for(i=1;i<=top;i++)
            if(~sta&(1<<i-1))
                unfilled[stack[i].first][stack[i].second]=true;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                for(k=0;k<9;k++)
                    if(unfilled[i+dx[k]][j+dy[k]])
                        break;
                if(k==9)
                    cnt[sta]++;
            }
    }
    f[0][0]=1;
    for(i=1;i<=n*m;i++)
        for(sta=0;sta<1<<top;sta++)
        {
            (f[i][sta]+=(long long)f[i-1][sta]*max(cnt[sta]-i+1,0))%=MOD;
            for(j=1;j<=top;j++)
                if(sta&(1<<j-1))
                    (f[i][sta]+=f[i-1][sta^(1<<j-1)])%=MOD;
        }
    return f[n*m][(1<<top)-1];
}
void DFS(int x,int y,int cnt)
{
    int i;
    if(y==m+1)
    {
        DFS(x+1,1,cnt);
        return ;
    }
    if(x==n+1)
    {
        (ans+=Calculate()*(cnt&1?-1:1))%=MOD;
        return ;
    }
    DFS(x,y+1,cnt);
    for(i=0;i<9;i++)
        if(s[x+dx[i]][y+dy[i]]=='X')
            break;
    if(i==9)
    {
        s[x][y]='X';
        DFS(x,y+1,cnt+1);
        s[x][y]='.';
    }
}
int main()
{
	freopen("in.txt", "r", stdin);
	freopen("stdout.txt", "w", stdout);
    int i,j,k;
    cin>>n>>m;
    for(i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(s[i][j]=='X')
                for(k=0;k<8;k++)
                    if(s[i+dx[k]][j+dy[k]]=='X')
                        return puts("0"),0;
    DFS(1,1,0);
    cout<<(ans+MOD)%MOD<<endl;
}
