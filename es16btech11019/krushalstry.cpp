#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
int tedges;
int mark[200];
int sum=0;
int size=1;
int a[200];
struct node* sorted[100];
struct node* heap[100];
struct node* head[101];
struct node* iteration=NULL;

struct node
{
	int s,w,d;
	struct node* next;

};

void insert (struct node* itr)
{
	printf("%d  ",itr->w );
	heap[size]=itr;
	size++;
}

void heapify(struct node* heap[],int sta,int n)
{
	int smallest;
	struct node* temp;
	int i=sta,k=sta;

	while(i<(n)&&(n+1)>(2*i))
	{
		smallest=(heap[i]->w);
		printf("%d\n", heap[i]->w);
		if(smallest>(heap[2*i]->w))
		{
			smallest=(heap[2*i]->w);
			k=2*i;	
		}
		printf("ttttt11\n");
		if((n+1)>(2*i+1)&&smallest>(heap[2*i+1]->w))
		{
			smallest=(heap[2*i+1]->w);
			k=2*i+1;
		}
		printf("tttttww\n");
		if(smallest!=(heap[i]->w))
		{
			temp=heap[i];
			heap[i]=heap[k];
			heap[k]=temp;
			i=k;
		}
		else
		{
			printf("tttttkk\n");	
			break;
		}
	}
}

void build_minheap(struct node* heap[],int n,struct node* sorted[])
{
	int i,m=n;
	for(i=n/2;i>=1;i--)
	{	printf("hhhhhhh\n");
		heapify(heap,i,n);
		printf("hello\n");
	}
	for(i=1;i<=m;i++)
	{
		sorted[i]=heap[1];
		heap[1]=heap[n];
		n--;
		heapify(heap,1,n);		
	}
}

int root (int t)
{
    while(mark[t] != t)
    {
        t = mark[t];
    }
    return t;
}

void union1 (int x, int y)
{
    int p = root(x);
    int q = root(y);
    mark[p] = mark[q];
}


int main()
{
	int v,i,c=0;
	printf("Total Vertices :");
	scanf("%d",&v);
	
	for (int i = 0; i <=v; ++i)
	{
		mark[i]=i;
	}
	for(i=0;i<=100;i++)
		head[i]=NULL;
	tedges=0;
	for(i=1;i<=v;i++)
	{
		int e,j;
		printf("Number of edges for v %d : ",i);
		scanf("%d",&e);
		tedges=tedges+e;
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

	for(i=1;i<=v;i++)
	{
		iteration=head[i];
		while(iteration!=NULL)
		{
			if((iteration->d)>i)
				insert(iteration);
			iteration=iteration->next;
		}
	}

	build_minheap(heap, (size-1) ,sorted);

	for (int i = 1; i < size; ++i)
	{
		/* code */
		printf("%d  ",sorted[i]->w);
	}

	i=0;
	while(i<tedges)
	{
		if(root(mark[sorted[i]->s])!=root(mark[sorted[i]->d]))
		{
			union1(mark[sorted[i]->s],mark[sorted[i]->d]); 	
			printf("%d -- %d\n", sorted[i]->s,sorted[i]->d);
			a[c++]=sorted[i]->w;
			sum=sum+(sorted[i]->w);
		}
		i++;
	}

	printf("\n\nEdge Weights: ");

	for(i=0;i<c;i++)
		printf("%d --",a[i]);	

	printf("\nMST Weight = %d\n",sum);

	return 0;
}