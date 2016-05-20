 #include <cstdio>
 #include <map>
 #include <algorithm>
 
 using namespace std;  
	const int MAXN = 50;  
      
    struct Node  
    {  
        int x;  
        Node (int x) : x(x) {}  
        bool operator< (const Node& rhs) const  
        {  
            return x > rhs.x;  
        }  
    };  
    int ipt[MAXN];  
    map<Node, int>mp;  
    map<Node, int>::iterator it;  
      
      
    bool dfs(map<Node, int>::iterator it, int& v)  
    {  
        if (it == mp.end())  
        {  
            if (v == 0) return true;  
            return false;  
        }  
        int n = it->first.x;  
        int num = min(v / n, it->second);  
        FED(i, num, 0)  
        {  
            it->second -= i;  
            v -= i * n;  
            if (dfs(++it, v))  
                return true;  
            v += i * n;  
            it--;  
            it->second += i;  
        }  
        return false;  
    }  
      
    int main()  
    {  
        //    freopen("in.txt", "r", stdin);  
        int n;  
        while (~RI(n))  
        {  
            mp.clear();  
            bool ok = true;  
            int cnt = 0;  
            REP(i, n)  
            {  
                int t;  
                RI(t);  
                if (t == 1) mp[Node(t)]++;  
                else ipt[cnt++] = t;  
            }  
            sort(ipt, ipt + cnt);  
            REP(i, cnt)  
            {  
                int t = ipt[i] - 1;  
                it = mp.upper_bound(Node(t));  
                if (!dfs(it, t))  
                {  
                    ok = false;  
                    break;  
                }  
                it = mp.begin();  
                while (it != mp.end())  
                {  
                    if (it->second == 0)  
                        mp.erase(it++);  
                    else  
                        it++;  
                }  
                mp[Node(ipt[i])]++;  
            }  
            if (mp.size() != 1 || mp.begin()->second != 1) ok = false;  
            if (ok) puts("YES");  
            else puts("NO");  
        }  
        return 0;  
    }  
