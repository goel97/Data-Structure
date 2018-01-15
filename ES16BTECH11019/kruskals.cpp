//Working kruskals
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int count=1;				//To count the numberof visited vertices
int sum=0;					//Total weight of MST
int size=1;					//maintain the size of minheap
int a[200];					//array to store weights of edges of MST
struct node* sorted[100]; 	//heap array after sorting 	
struct node* heap[100];		//heap in which weight of edges are inserted and heapsort are called
struct node* head[101];		//ajdacency list 
struct node* iteration=NULL;

struct node
{
	int s,w,d;				//s: source of edge, w: weight of edge,d:drain of edge
	struct node* next;		//used in adjacency list to point to next edge

};

void insert (struct node* itr)	//to insert edges of the called vertice in the min heap
{
	heap[size]=itr;
	size++;
}

int root (int mark[],int t)		//used to find the parent of element in union-find operations
{								//also used to check if cycle is formed by comparing root of the two vertices
    while(mark[t] != t)			//to find root, loop untill mark[t]==t
    {
    	mark[t] = mark[mark[t]];
        t = mark[t];
    }
    return t;
}

void union1 (int mark[],int x, int y)	//it is use to combine two vertices in visited set
{
    int p = root(mark,x);
    int q = root(mark,y);
    mark[p] = mark[q];
}

void heapify(struct node* heap[],int sta,int n)	//used in maintaing the min heap prperties after build min heap is called
{
	int smallest;
	struct node* temp;
	int i=sta,k=sta;

	while(i<(n)&&(n+1)>(2*i))				//we move in top down manner
	{
		smallest=(heap[i]->w);
		if(smallest>(heap[2*i]->w))			//if parent is greater than left child
		{
			smallest=(heap[2*i]->w);
			k=2*i;
		}
		if((n+1)>(2*i+1)&&smallest>(heap[2*i+1]->w))	//if current smallest is greater than right child  
		{
			smallest=(heap[2*i+1]->w);
			k=2*i+1;
		}
		if(smallest!=(heap[i]->w))		//swaps to move the smaller child up
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

void build_minheap(struct node* heap[],int n,struct node* sorted[])	//to sort the edges in heap by weight 
{
	int i,m=n;
	for(i=n/2;i>=1;i--)
	{	//printf("hhhhhhh\n");
		heapify(heap,i,n);
		//printf("hello\n");
	}
	for(i=1;i<=m;i++)			//adding minmum element to new array name sorted 
	{
		sorted[i]=heap[1];
		heap[1]=heap[n];		//replacing the fiirst element with last, and decreasing the size of heap
		n--;
		
		heapify(heap,1,n);		//calling heapify to readjust the new heap array
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
	int mark[v];
	for (int i = 1; i <=v; ++i)
	{
		mark[i]=i;				//to check if two vertices for a cycle using disjoint sets
	}
	for(i=0;i<=100;i++)	//we make a adjacency link-list for each vertice , and head[index] points to root of each
		head[i]=NULL;

	for(i=1;i<=v;i++)	//loop to input all edges vertice by vertice
	{
		int e,j;
		printf("Number of edges for v %d : ",i);
		scanf("%d",&e);
		for(j=1;j<=e;j++)		//loop for number of edges for respective vertice
		{
			struct node* new_node = (struct node*) malloc(sizeof(struct node));	//allocate memory for each edge
			new_node->s=i;				//source for eachof this edge is vertice i
			printf("Enter Weight and Edge respectively:\n");
			scanf("%d",&new_node->w);	//input edge weight
			scanf("%d",&new_node->d);	//input edge drain
			if(head[i]==NULL)			//add the first entry in the adjacency list
			{
				head[i]=new_node;
				new_node->next=NULL;
			}
			else						//to build the adjacency list
			{
				new_node->next=head[i];
				head[i]=new_node;
			}
		}
	}

	for(i=1;i<=v;i++)
	{
		iteration=head[i];
		while(iteration!=NULL)			//untill we reach the end of their respective adjacency list
		{
			if((iteration->d)>i)		//to not add an edge if already added
				insert(iteration);		//insert the edge in min heap
			iteration=iteration->next;
		}
	}

	build_minheap(heap, (size-1) ,sorted);	//to sort the all the edges by weight and store them in a new sorted array
	printf("Sorted Edges\n");
	for (int i = 1; i < size; ++i)
		printf("%d  ",sorted[i]->w);

	printf("\n\nPath:   Weight \n");
	i=1;
	while(i<size)	//untill we reach the end of sorted array
	{
		if(root(mark,mark[sorted[i]->s])!=root(mark,mark[sorted[i]->d]))		//if the two vertices doesnt form a cycle
		{
			union1(mark,mark[sorted[i]->s],mark[sorted[i]->d]);					//combine 2 vertices in one set
			printf("%d -- %d    %d\n", sorted[i]->s,sorted[i]->d,sorted[i]->w);	//print the edge seleted
			a[c++]=sorted[i]->w;												//add the weight of min edge to array a
			sum=sum+(sorted[i]->w);												//records and update the MST value
		}
		i++;
	}

	printf("\nEdge Weights: ");

	for(i=0;i<c;i++)					//print the array with selected weights
		printf("%d --",a[i]);	

	printf("\nMST Weight = %d\n",sum);

	free_memory(v);

	return 0;
}