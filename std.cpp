#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int s;
	int e;
}Node;
Node p[1000010];
int cmp(const void *_a,const void *_b)
{
	Node *a=(Node*)_a;
	Node *b=(Node*)_b;
	if(a->s==b->s)
		return b->e-a->e;
	return a->s-b->s;
}
int main()
{
	freopen("in.txt", "r", stdin);
	int n,t,i,j,f,c,mark,mx,k;
	while(scanf("%d %d",&n,&t)!=EOF)
	{
		for(i=0;i<n;i++)
		scanf("%d %d",&p[i].s,&p[i].e);
		qsort(p,n,sizeof(p[0]),cmp);
		if(p[0].s!=1)
		{
			printf("-1\n");
            continue;
		}
		if(p[0].s==1&&p[0].e==t)
		{
			printf("1\n");
			continue;
		}
		c=1;
		f=0;
		for(i=0;i<n;)
		{
			mark=0;
			mx=p[i].e;
			for(j=i+1;j<n;j++)
			if(p[j].s>=p[i].s&&p[j].s<=p[i].e+1)
			{
				if(p[j].e>mx)
				{
					mx=p[j].e;
					k=j;
					mark=1;
				}
			}
			if(mark)
			{
				i=k;
				c++;
			}
			else
				break;
			if(p[i].e==t)
			{
				f=1;
				break;
			}
		}
		if(f)
			printf("%d\n",c);
		else
			printf("-1\n");
	}
	return 1;
}
