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
using namespace std;
typedef pair<int,int> Pii;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DBL;
typedef long double LDBL;
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define Sqr(a) ((a)*(a))

const char *ctn_name[7]={"std::vector<int>","std::list<int>","std::deque<int>","std::queue<int>",
					"std::stack<int>","std::priority_queue<int>","std::bitset<100>"};
const int maxn=1e5+10;
struct ctner
{
	int head,tail,id;
	int arry[2*maxn];
	ctner(){head=tail=maxn;}
	void clear(){head=tail=maxn;}
	void push_front(int n){arry[--head]=n;}
	void push_back(int n){arry[tail++]=n;}
	void pop_front(){head++;}
	void pop_back(){tail--;}
	void insert(int v,int p)
	{
		tail++;
		p+=head;
		for(int i=tail-1; i>p; i--) arry[i]=arry[i-1];
		arry[p]=v;
	}
	void erase(int p)
	{
		tail--;
		p+=head;
		for(int i=p; i<tail; i++) arry[i]=arry[i+1];
	}
	int front(){return arry[head];}
	int back(){return arry[tail-1];}
	int at(int p){return arry[p+head];}
	int kth(int k)
	{
		k=head+k-1;
		nth_element(arry+head, arry+k, arry+tail);
		return arry[k];
	} // here
	void pri()
	{
		puts("debug:");
		for(int i=head; i<tail; i++) printf("%d ", arry[i]);
		puts("");
	}
};

int N;
ctner list[5];
priority_queue<int> pq;
bitset<100> bit[2];
int bit_cnt;
char inpt[50];
int ctn_num(char *str) {for(int i=0; i<6; i++) {if(!strcmp(str, ctn_name[i])) return i;} return -1;}

void PQ();
void BITSET();

int main()
{
	#ifdef LOCAL
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	#endif
	
	for(int i=0; i<5; i++) list[i].id=i;
	
	int T;
	scanf("%d", &T);
	for(int ck=1; ck<=T; ck++)
	{
		scanf("%d ", &N);
		int val, pos;
		char str[25];
		bit_cnt=0;
		for(int i=1; i<=N; i++)
		{
			fgets(inpt, 50, stdin);
			//puts(inpt);
			if(strstr(inpt, ctn_name[5])) PQ();
			else if(strstr(inpt, ctn_name[6])) BITSET();
			else if(sscanf(inpt, "construct a %s", str))
				list[ ctn_num(str) ].clear();
			else if(sscanf(inpt,"push_back %d in %s", &val, str))
				list[ ctn_num(str) ].push_back(val);
			else if(sscanf(inpt,"pop_back in %s", str))
				list[ ctn_num(str) ].pop_back();
			else if(sscanf(inpt,"push_front %d in %s", &val, str))
				list[ ctn_num(str) ].push_front(val);
			else if(sscanf(inpt,"pop_front in %s", str))
				list[ ctn_num(str) ].pop_front();
			else if(sscanf(inpt,"insert %d in %s at %d", &val, str, &pos))
				list[ ctn_num(str) ].insert(val, pos);
			else if(sscanf(inpt,"erase %d in %s", &pos, str))
				list[ ctn_num(str) ].erase(pos);
			else if(sscanf(inpt,"front value in %s", str))
				printf("%d\n", list[ ctn_num(str) ].front());
			else if(sscanf(inpt,"back value in %s", str))
				printf("%d\n", list[ ctn_num(str) ].back());
			else if(sscanf(inpt,"query %d in %s", &pos, str))
				printf("%d\n", list[ ctn_num(str) ].at(pos));
			else if(sscanf(inpt,"%d-th in %s", &val, str))
				printf("%d\n", list[ ctn_num(str) ].kth(val));
			
			else if(sscanf(inpt,"%s", str) && !strcmp(str, "intersection"))
				printf("%s\n", (bit[0]&bit[1]).any()?"true":"false");
			//list[0].pri();
		}
	}
	return 0;
}

void PQ()
{
	int val;
	char str[25];
	if(sscanf(inpt, "construct a %s", str))
		while(pq.size()) pq.pop();
	else if(sscanf(inpt,"push_back %d in %s", &val, str))
		pq.push(val);
	else if(sscanf(inpt,"pop_front in %s", str))
		pq.pop();
	else if(sscanf(inpt,"front value in %s", str))
		printf("%d\n", pq.top());
}

void BITSET()
{
	int val,pos;
	char str[25];
	if(sscanf(inpt, "construct a %s", str))
		bit[ bit_cnt++ ].reset();
	else if(sscanf(inpt,"set %d in %*s %d", &pos, &val))
		bit[ val ].set(pos);
	else if(sscanf(inpt,"reset %d in %*s %d", &pos, &val))
		bit[ val ].reset(pos);
	else if(sscanf(inpt,"set in %*s %d", &val))
		bit[ val ].set();
	else if(sscanf(inpt,"reset in %*s %d", &val))
		bit[ val ].reset();
	else if(sscanf(inpt,"flip %d in %*s %d", &pos, &val))
		bit[ val ].flip(pos);
	else if(sscanf(inpt,"flip in %*s %d", &val))
		bit[ val ].flip();
	else if(sscanf(inpt,"count in %*s %d", &val))
		printf("%d\n", (int)bit[ val ].count());
	else if(sscanf(inpt,"test %d in %*s %d", &pos, &val))
		printf("%s\n", bit[ val ].test(pos)?"true":"false");
}
