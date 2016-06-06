#include <cstdio>
using namespace std;  
int unin[50005]={0};  
int eval[50005]={0};  
int n;  
void init()  
{  
    for(int i=1;i<=n;i++)  
    {  
        unin[i]=i; eval[i]=0;  
    }  
}  
int find(int x)  
{  
    if(x==unin[x])  return x;  
    int ox = unin[x];  
    unin[x]=find(unin[x]);  
    eval[x]=(eval[x]+eval[ox])%3;
    return unin[x];  
}  
void join(int opt,int x,int y)  
{  
    int fx,fy;  
    fx=find(x); fy=find(y);  
    if(fx==fy) return;  
    unin[fx]=fy;  
    eval[fx]=(eval[y]+opt-eval[x]+3)%3;
    return;
}  
int judge(int opt,int x,int y)  
{  
    int fx,fy,r;  
    if(x>n || y>n || ((x==y)&&(opt==1)) )  
        return 0;
    fx=find(x); fy=find(y);  
    if(fx!=fy)  return 1;
    else  
    {  
    	if(eval[x]==(opt+eval[y])%3) return 1;
		else  return 0;  
	}  
}  
int main()  
{  
    int k,i,x,y,d; int ans=0;  
    scanf("%d%d",&n,&k);  
    init();  
    for(i=1;i<=k;i++)  
    {  
        scanf("%d%d%d",&d,&x,&y);  
        d--;
        if( !judge(d,x,y) )  
            ans++;  
        else  
            join(d,x,y);  
    }  
    printf("%d\n",ans);  
    return 0;  
}  
