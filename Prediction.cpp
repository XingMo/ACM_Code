#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <cctype>
#include <bitset>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int ,int> pii;
#define MEM(a,b) memset(a,b,sizeof a)
#define CLR(a) memset(a,0,sizeof a);
#define pi acos(-1.0)
#define maxn 10004
#define maxm 504
#define maxv 100005
const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
std::vector<bitset<maxm> > v[maxn];
int To[maxn][maxm], minv[maxn][maxm], id[maxn][maxm];
vector<int> G[maxn];
int fa, n, m;
int U[maxn], V[maxn];
int find(int u, int v){
	if (minv[u][v] == v) return v;
	else return minv[u][v] = find(u, minv[u][v]);
}
void dfs(int u, int f){
    v[u].clear();
    if (u == 1){
        for (int i = 1; i <= n; ++i)
            minv[u][i] = i;
        int a = U[1], b = V[1];
        minv[1][a] = minv[1][b] = min(minv[1][a], minv[1][b]);
    }else{
        memcpy(minv[u], minv[f], sizeof minv[f]);
        int a = U[u], b = V[u];
        int Minva = minv[f][a], Minvb = minv[f][b];
        int Minv = min(Minva, Minvb);
        minv[u][a] = minv[u][b] = Minv;
        for (int i = 1; i <= n; ++i) find(u, i);
    }
    for (int i = 0; i < G[u].size(); ++i){
        int to = G[u][i];
        dfs(to, u);
    }
}
int q, K, u;
struct Link{
    int val;
    Link *nxt;
};
struct List{
    Link* head;
    Link* tail;
    List(){
        head = new Link;
        tail = head;
        head->nxt = NULL;
    }
  //  void insert(){

    //}
};
int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
//    freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    int i, j, k, kase, ik;
    cin >> kase;
    for (ik = 1; ik <= kase; ++ik){
        cout << "Case #" << ik << ':' <<'\n';
        cin >> n >> m;
        for (int i = 1; i < maxn; ++i) G[i].clear();
        for (i = 2; i <= m; ++i){
            cin >> fa;
            G[fa].push_back(i);
        }
        for (i = 1; i <= m; ++i) cin >> U[i] >> V[i];
        dfs(1, -1);
        cin >> q;
        int Minv[maxm];
        while(q--){
            cin >> K;
            for (i = 1; i <= n; ++i) Minv[i] = i;
            for (i = 1; i <= K; ++i){
                cin >> u;
                for (j = 1; j <= n; ++j) Minv[j] = min(Minv[j], minv[u][j]);
            }
            int cnt = 0;
            for (i = 1; i <= n; ++i){
            	if (i-1) cout << ' ';
            	cout << Minv[i];
            }cout << endl;
            for (i = 1; i <= n; ++i) if (i == Minv[i]) cnt++;
            cout << cnt << endl;
        }
    }
    return 0;
}
