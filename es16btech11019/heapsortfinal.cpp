#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

void heapify(int heap[],int size,int n)
{
	int smallest,temp;
	int i=size,k=size;

	while(i<(n)&&(n+1)>(2*i))
	{
		smallest=heap[i];
		if(smallest>heap[2*i])
		{
			smallest=heap[2*i];
			k=2*i;
		}
		if(smallest>heap[2*i+1]&&(n+1)>(2*i+1))
		{
			smallest=heap[2*i+1];
			k=2*i+1;
		}
		if(smallest!=heap[i])
		{
			temp=heap[i];
			heap[i]=smallest;
			heap[k]=temp;
			i=k;
		}
		else
			break;
	}
}

void build_minheap(int heap[],int n,int sorted[])
{
	int i,m=n;
	for(i=n/2;i>=1;i--)
		heapify(heap,i,n);
	for(i=1;i<=m;i++)
	{
		sorted[i]=heap[1];
		heap[1]=heap[n];
		n--;
		heapify(heap,1,n);		
	}
}

int main()
{
	int n;
	printf("Total elements: ");
	scanf("%d",&n);

	int heap[n+1],j,sorted[n+1];

	for(j=1;j<=n;j++)
	{
		scanf("%d",&heap[j]);
		sorted[j]=0;
	}

	build_minheap(heap,n,sorted);

	for (int i = 1; i <=n; ++i)
		printf("%d  ",sorted[i]);
	printf("\n");
	return 0;
}