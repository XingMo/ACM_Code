#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#pragma comment(linker,"/STACK:102400000,102400000")

using namespace std;
#define   MAX           100005
#define   MAXN          1000005
#define   maxnode       205
#define   sigma_size    2
#define   lson          l,m,rt<<1
#define   rson          m+1,r,rt<<1|1
#define   lrt           rt<<1
#define   rrt           rt<<1|1
#define   middle        int m=(r+l)>>1
#define   LL            long long
#define   ull           unsigned long long
#define   mem(x,v)      memset(x,v,sizeof(x))
#define   lowbit(x)     (x&-x)
#define   pii           pair<int,int>
#define   bits(a)       __builtin_popcount(a)
#define   mk            make_pair
#define   limit         10000

//const int    prime = 999983;
const int    INF   = 0x3f3f3f3f;
const LL     INFF  = 0x3f3f;
//const double pi    = acos(-1.0);
const double inf   = 1e18;
const double eps   = 1e-9;
const LL     mod   = 1e9+7;
const ull    mx    = 133333331;

/*****************************************************/
inline void RI(int &x) {
      char c;
      while((c=getchar())<'0' || c>'9');
      x=c-'0';
      while((c=getchar())>='0' && c<='9') x=(x<<3)+(x<<1)+c-'0';
 }
/*****************************************************/

struct Edge{
    int v,next,num,c;
}edge[MAX*2];

struct Node{
    int id,val;
    bool operator<(const Node &a)const{
        return val>a.val;
    }
}x;

int head[MAX];
LL dis[MAX*2];
int vis[MAX*2];
int tot;

void add_edge(int a,int b,int c,int d){
    edge[tot]=(Edge){b,head[a],c,d};
    head[a]=tot++;
    edge[tot]=(Edge){a,head[b],c,d};
    head[b]=tot++;
}

LL dijkstra(int s,int t){
    priority_queue<Node> q;
    for(int i=0;i<tot;i++){
        dis[i]=1e18;
        vis[i]=0;
    }
    for(int i=head[s];i!=-1;i=edge[i].next){
        x=(Node){i,edge[i].c};
        dis[i]=edge[i].c;
        q.push(x);
    }
    LL ans=1e18;
    while(!q.empty()){
        x=q.top();
        q.pop();
        int p=x.id;
        if(vis[p]) continue;
        vis[p]=1;
        int u=edge[p].v;
        if(u==t) ans=min(ans,dis[p]);
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].v;
            if(!vis[i]&&dis[i]>dis[p]+edge[i].c+abs(edge[i].num-edge[p].num)){
                dis[i]=dis[p]+edge[i].c+abs(edge[i].num-edge[p].num);
                q.push((Node){i,dis[i]});
            }
        }
    }
    return ans;
}
int main() {
	freopen("in.txt", "r", stdin);
    int n,m;
    while(cin>>n>>m){
        tot=0;
        for(int i=1;i<=n;i++) head[i]=-1;
        for(int i=0;i<m;i++){
            int a,b,c,d;
            RI(a);RI(b);RI(c);RI(d);
            add_edge(a,b,c,d);
        }
        cout<<dijkstra(1,n)<<endl;
    }
    return 0;
}
