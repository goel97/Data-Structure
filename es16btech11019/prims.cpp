#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct node
{
	int s,w,d;				//s: source of edge, w: weight of edge,d:drain of edge
	struct node* next;		//used in adjacency list to point to next edge

};

int a[200];					//array to store weights of edges of MST
int sum=0;					//Total weight of MST
int size=1;					//maintain the size of minheap
int count=0;				//To count the numberof visited vertices
struct node* heap[100];		//min heap of the edge weights
struct node* head[101];		//ajdacency list 
struct node* iteration=NULL;

void heapify_bottom()		//to re adjust the min heap after insertion of edges
{
	int flag=1;
	struct node* temp;
	int i=size-1;
	while(i>1&&flag==1)
	{
		if((heap[(i)/2]->w)>(heap[i]->w))
		{
			temp=heap[i];
			heap[i]=heap[i/2];
			heap[i/2]=temp;
			i=i/2;
		}	
		else
			flag=0;
	}
}

void heapify_top()			//to re adjust the min heap after deletion of min edge
{
	int smallest;
	struct node* temp;
	int i=1,k=1;

	while(i<(size-1)&&size>(2*i))
	{
		smallest=(heap[i]->w);
		if(smallest>(heap[2*i]->w))
		{
			smallest=(heap[2*i]->w);
			k=2*i;
		}
		if(smallest>(heap[2*i+1]->w)&&size>(2*i+1))
		{
			smallest=(heap[2*i+1]->w);
			k=2*i+1;
		}
		if(smallest!=(heap[i]->w))
		{
			temp=heap[i];
			heap[i]=heap[k];
			heap[k]=temp;
			i=k;
		}
		else
			break;
	}
}

void insert (struct node* itr)		//to insert edges of the called vertice in the min heap
{
	heap[size]=itr;
	size++;
	heapify_bottom();
}

void delete_min()					//to select the edge with minimum weight among the edges in the min heap
{
	if(size>1)
	{
		heap[1]=heap[size-1];
		size--;
		heapify_top();
	}
}

void free_memory(int v)
{
	for(int i=1;i<=v;i++)//free the allocated memory of all the nodes
    {
        struct node* ite=head[i];
        struct node* temp=NULL;
        while(ite!=NULL)
        {
            temp=ite;
            ite=ite->next;
            free(temp);
        }
        head[i]=NULL;
    }
}

int main()
{
	int v,i,c=0;				//v:vertices,c:numberof edges in final mst
	printf("Total Vertices :");
	scanf("%d",&v);
	int mark[v];				//to check if a vertice is already visited
	for (int i = 0; i <=v; ++i)
	{
		mark[i]=0;
	}
	for(i=0;i<=100;i++)			//we make a adjacency link-list for each vertice , and head[index] points to root of each
		head[i]=NULL;

	for(i=1;i<=v;i++)	//loop to input all edges vertice by vertice
	{
		int e,j;
		printf("Number of edges for v %d : ",i);
		scanf("%d",&e);
		for(j=1;j<=e;j++)		//loop for number of edges for respective vertice
		{

			struct node* new_node = (struct node*) malloc(sizeof(struct node));	//allocate memory for each edge
			new_node->s=i;					//source for eachof this edge is vertice i
			printf("Enter Weight and Edge respectively:\n");
			scanf("%d",&new_node->w);		//input edge weight
			scanf("%d",&new_node->d);		//input edge drain
			if(head[i]==NULL)				//add in the adjacency list
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
	//int flag2=0;
	iteration=head[1];			//start fromvertice 1
	printf("MST:\t Weight");
	mark[1]=1;					//mark vertice 1 as visited(1)
	count++;
	while(count<v)
	{	
		while(iteration!=NULL)			//untill we reach the end of the respective vertice link list
		{
			//if(mark[iteration->d]==0||flag2==0)
			{
				insert(iteration);		//insert the edge in min heap
				iteration=iteration->next;
			}
		}
		printf("\n");
		//after inserting all edges of the this vertice, select the one with min weight among all the edges in min heap
		int flag1=1;
		while(flag1==1)//untill we delete an edge from min heap
		if(mark[heap[1]->d]==0)//if the drain of edge is not already visited
		{
			mark[heap[1]->d]=1;// mark the drain visted
			printf("%d -- %d    %d\n", heap[1]->s,heap[1]->d,heap[1]->w);//print the edge seleted
			//printf("\n\n");
			iteration=head[heap[1]->d];//move to the drain vertice as the next selected vertice
			a[c++]=heap[1]->w;		   //add the weight of min edge to array a
			sum=sum+(heap[1]->w);	   //records and update the MST value
			count++;				   //increase the count of visited vertice

			delete_min();

			flag1=0;
		}
		else				//if drain of minimum wright edge is already visted, delete it and select the next minimum weighted edge
			delete_min();	
	}

	printf("\nEdge Weights: ");
	for(i=0;i<c;i++)
		printf("%d --",a[i]);	
	printf("\nMST Weight = %d\n",sum);

	free_memory(v);
	
	return 0;
}