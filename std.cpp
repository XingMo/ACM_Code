#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <climits>
using namespace std;
     
    #define LEFT(x) (x << 1)
    #define RIGHT(x) ((x << 1) | 1)
    #define MID(x, y) ((x + y) >> 1)
    #define MAXN 200010
    enum Type
    {
    	WALL, BIRD
    };
     
    struct Distance
    {
    	int id, d;	// 距离最近的墙的id以及距离
    	Distance()
    	{
    		d = INT_MAX;	// 0x3f3f3f3f让我WA了无数次(┳＿┳)... 
    	}
    };
     
    Distance the_distance[MAXN];
     
    struct Wall
    {
    	int x1, y1, x2, y2;
    }wall[MAXN];
     
    struct Bird
    {
    	int x, y;
    }bird[MAXN];
     
    struct Object
    {
    	int x;
    	int y1, y2;
    	int id;
    	Type type;
    	Object(int x, int y1, int y2, int id, Type type) : x(x), y1(y1), y2(y2), id(id), type(type) {};
    	bool operator < (const Object& other) const
    	{
    		return x < other.x;
    	}
    };
     
    vector <int> listx;
    vector <int> listy;
    int result[MAXN];
    int N, M;
     
    struct SegmentTree
    {
    	int left[MAXN * 8], right[MAXN * 8], value[MAXN * 8];
    	void build(int p, int l, int r)
    	{
    		left[p] = l;
    		right[p] = r;
    		value[p] = 0;
    		if (l < r)
    		{
    			int mid = MID(l, r);
    			build(LEFT(p), l, mid);
    			build(RIGHT(p), mid + 1, r);
    		}
    	}
    	void set(int p, int l, int r, int v)
    	{
    		if (left[p] == l && right[p] == r)
    		{
    			value[p] = v;
    			return;
    		}
    		if (value[p] > 0)
    		{
    			value[LEFT(p)] = value[p];
    			value[RIGHT(p)] = value[p];
    			value[p] = 0;
    		}
    		int mid = MID(left[p], right[p]);
    		if (l > mid)
    		{
    			set(RIGHT(p), l, r, v);
    		}
    		else if (r <= mid)
    		{
    			set(LEFT(p), l, r, v);
    		}	
    		else
    		{
    			set(LEFT(p), l, mid, v);
    			set(RIGHT(p), mid + 1, r, v);
    		}
    	}
    	int get(int p, int l)
    	{
    		if (left[p] == right[p] && left[p] == l)
    		{
    			return value[p];
    		}
    		if (value[p] > 0)
    		{
    			value[LEFT(p)] = value[p];
    			value[RIGHT(p)] = value[p];
    			value[p] = 0;
    		}
    		if (l > MID(left[p], right[p]))
    		{
    			return get(RIGHT(p), l);
    		}
    		else
    		{
    			return get(LEFT(p), l);
    		}
    	}
    }tree;
     
    int get_distance(bool vertical, int x, int y)
    {
    	if (!vertical)
    	{
    		x = listx[x - 1];
    		y = listx[y - 1];
    	}
    	else
    	{
    		x = listy[x - 1];
    		y = listy[y - 1];
    	}
    	return abs(x - y);
    }
     
    void go(const vector<Object>& obj_array, bool vertical)
    {
    	tree.build(1, 1, max(listx.size(), listy.size()) + 10);
    	for (vector<Object>::const_iterator it = obj_array.begin(); it != obj_array.end(); ++it)
    	{
    		if (it->type == WALL)
    		{
    			tree.set(1, it->y1, it->y2, it->id);
    		}
    		else
    		{
    			int p = tree.get(1, it->y1);
    			if (p)
    			{
    				int d = vertical ? min(get_distance(1, wall[p].y1, it->x), get_distance(1, wall[p].y2, it->x)) : min(get_distance(0, wall[p].x1, it->x), get_distance(0, wall[p].x2, it->x));
    				if (d < the_distance[it->id].d)
    				{
    					the_distance[it->id].d = d;
    					the_distance[it->id].id  = p;
    				}
    			}
    		}
    	}
    }
     
    void fly_x()
    {
    	vector<Object> obj_array;
    	for (int i = 1; i <= N; ++i)
    	{
    		obj_array.push_back(Object(wall[i].x1, wall[i].y1, wall[i].y2, i, WALL));
    		if (wall[i].x1 != wall[i].x2)
    		{
    			obj_array.push_back(Object(wall[i].x2, wall[i].y1, wall[i].y2, i, WALL));
    		}
    	}
     
    	for (int i = 1; i <= M; ++i)
    	{
    		obj_array.push_back(Object(bird[i].x, bird[i].y, 0, i, BIRD));
    	}
    	sort(obj_array.begin(), obj_array.end());
    	go(obj_array, false);
    	reverse(obj_array.begin(), obj_array.end());
    	go(obj_array, false);
    }
     
    void fly_y()
    {
    	vector<Object> obj_array;
    	for (int i = 1; i <= N; ++i)
    	{
    		obj_array.push_back(Object(wall[i].y1, wall[i].x1, wall[i].x2, i, WALL));
    		if (wall[i].y1 != wall[i].y2)
    		{
    			obj_array.push_back(Object(wall[i].y2, wall[i].x1, wall[i].x2, i, WALL));
    		}
    	}
     
    	for (int i = 1; i <= M; ++i)
    	{
    		obj_array.push_back(Object(bird[i].y, bird[i].x, 0, i, BIRD));
    	}
    	sort(obj_array.begin(), obj_array.end());
    	go(obj_array, true);
    	reverse(obj_array.begin(), obj_array.end());
    	go(obj_array, true);
    }
     
     
    ///////////////////////////SubMain//////////////////////////////////
    int main(int argc, char *argv[])
    {
//    #ifndef ONLINE_JUDGE
    	freopen("in.txt", "r", stdin);
//    	freopen("stdout.txt", "w", stdout);
//    #endif
    	scanf("%d%d", &N, &M);
    	for (int i = 1; i <= N; ++i)
    	{
    		scanf("%d%d%d%d", &wall[i].x1, &wall[i].y1, &wall[i].x2, &wall[i].y2);
    		if (wall[i].x1 > wall[i].x2)
    		{
    			swap(wall[i].x1, wall[i].x2);
    		}
    		if (wall[i].y1 > wall[i].y2)
    		{
    			swap(wall[i].y1, wall[i].y2);
    		}
    		listx.push_back(wall[i].x1);
    		listx.push_back(wall[i].x2);
    		listy.push_back(wall[i].y1);
    		listy.push_back(wall[i].y2);
    	}
     
    	for (int i = 1; i <= M; ++i)
    	{
    		scanf("%d%d", &bird[i].x, &bird[i].y);
    		listx.push_back(bird[i].x);
    		listy.push_back(bird[i].y);
    	}
    	sort(listx.begin(), listx.end());
    	listx.erase(unique(listx.begin(), listx.end()), listx.end());
    	sort(listy.begin(), listy.end());
    	listy.erase(unique(listy.begin(), listy.end()), listy.end());
    	for (int i = 1; i <= N; ++i)
    	{
    		wall[i].x1 = lower_bound(listx.begin(), listx.end(), wall[i].x1) - listx.begin() + 1;
    		wall[i].x2 = lower_bound(listx.begin(), listx.end(), wall[i].x2) - listx.begin() + 1;
    		wall[i].y1 = lower_bound(listy.begin(), listy.end(), wall[i].y1) - listy.begin() + 1;
    		wall[i].y2 = lower_bound(listy.begin(), listy.end(), wall[i].y2) - listy.begin() + 1;
    	}
    	for (int i = 1; i <= M; ++i)
    	{
    		bird[i].x = lower_bound(listx.begin(), listx.end(), bird[i].x) - listx.begin() + 1;
    		bird[i].y = lower_bound(listy.begin(), listy.end(), bird[i].y) - listy.begin() + 1;
    	}
     
    	fly_x();
    	fly_y();
     
    	for (int i = 1; i <= M; ++i)
    	{
    		++result[the_distance[i].id];
    	}
    	for (int i = 1; i <= N; ++i)
    	{
    		printf("%d\n", result[i]);
    	}
     
//    #ifndef ONLINE_JUDGE
//    	fclose(stdin);
//    	fclose(stdout);
//    	system("out.txt");
//    #endif
    	return 0;
    }
    ///////////////////////////End Sub//////////////////////////////////
