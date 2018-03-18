#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <climits>

using namespace std;

struct node
{
	int s,w,d;
	struct node* next;

};

struct path
{
	int ver;
	int dist;
};

int loc[100];
int size;
int count=0;
struct path minheap[100];
struct node* head[101];
struct node* iteration=NULL;

void heapify(struct path minheap[],int sta,int n)
{
	int smallest,t;
	struct path temp;
	int i=sta,k=sta;

	while(i<(n)&&(n+1)>(2*i))
	{
		smallest=(minheap[i].dist);
		if(smallest>(minheap[2*i].dist))
		{
			smallest=(minheap[2*i].dist);
			k=2*i;
		}
		if((n+1)>(2*i+1)&&smallest>(minheap[2*i+1].dist))
		{
			smallest=(minheap[2*i+1].dist);
			k=2*i+1;
		}
		if(smallest!=(minheap[i].dist))
		{
			t=loc[minheap[i].ver];
			loc[minheap[i].ver]=loc[minheap[k].ver];
			loc[minheap[k].ver]=t;
			temp=minheap[i];
			minheap[i]=minheap[k];
			minheap[k]=temp;
			i=k;
		}
		else
			break;
	}
}

void build_minheap(struct path minheap[],int n)
{
	int i;
	for(i=n/2;i>=1;i--)
	{	//printf("hhhhhhh\n");
		heapify(minheap,i,n);
		//printf("hello\n");
	}
}

int main()
{
	int v,i,c=0,st,a[100],mark[100];
	struct path tmp;
	printf("Total Vertices :");
	scanf("%d",&v);
	for (int i = 1; i <= v; ++i)
	{
		loc[i]=i;
		a[i]=i;
		mark[i]=0;
	}

	for(i=0;i<=100;i++)
		head[i]=NULL;

	for(i=1;i<=v;i++)
	{
		int e,j;
		printf("Number of edges for v %d : ",i);
		scanf("%d",&e);
		for(j=1;j<=e;j++)
		{

			struct node* new_node = (struct node*) malloc(sizeof(struct node));
			new_node->s=i;
			scanf("%d",&new_node->w);
			scanf("%d",&new_node->d);
			if(head[i]==NULL)
			{
				head[i]=new_node;
				new_node->next=NULL;
			}
			else
			{
				new_node->next=head[i];
				head[i]=new_node;
			}
		}
	}
	printf("Source: ");
	scanf("%d",&st);

	for (int i = 1; i <=v; ++i)
	{
		if(i==st)
		{
			minheap[i].ver=st;
			minheap[i].dist=0;
		}
		else
		{
			minheap[i].ver=i;
			minheap[i].dist=10000;
		}
	}

	size=v;
	build_minheap(minheap,size);

	while(count<=v)
	{
		iteration=head[minheap[1].ver];
		count++;	
		
		while(iteration!=NULL)
		{
			if(mark[iteration->d]!=1)
			{
				if((minheap[loc[iteration->d]].dist)>(minheap[loc[iteration->s]].dist + iteration->w))
				{
					minheap[loc[iteration->d]].dist=minheap[loc[iteration->s]].dist + iteration->w;
					a[iteration->d]=iteration->s;
				}
			}
			iteration=iteration->next;
		}

		mark[minheap[1].ver]=1;
		loc[minheap[1].ver]=size;
		loc[minheap[size].ver]=1;
		tmp=minheap[1];
		minheap[1]=minheap[size];
		minheap[size]=tmp;
		size--;
		
		build_minheap(minheap,size);
	}

	printf("\nVertex \t Shortest Distance From %d     Previous\n\n",st);
	for (int i = v; i >=1; --i)
	{
		printf("  %d\t\t   %2d\t\t\t%d\n",(v-i)+1,minheap[loc[(v-i)+1]].dist,a[(v-i)+1]);
	}
	return 0;
}