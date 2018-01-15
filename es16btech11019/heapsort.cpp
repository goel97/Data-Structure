#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

void buildminheap(int heap[], int size)
{
	int flag=1,temp;
	int i=size;
	while(i>1&&flag==1)
	{
		if(heap[(i)/2]>heap[i])
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

void heapify(int heap[],int n)
{
	int smallest,temp;
	int i=1,k=1;

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

int main()
{
	int n;
	printf("Total elements: ");
	scanf("%d",&n);

	int heap[n+1],j,i,sorted[n+1],k=0;

	for(j=1;j<=n;j++)
	{
		scanf("%d",&heap[j]);
		buildminheap(heap,j);
	}
	int size=n;
	for(i=1;i<=n;i++,k++)
	{
		sorted[k]=heap[1];
		heap[1]=heap[n];
		n--;
		heapify(heap,n);
	}

	for (int i = 0; i < size; ++i)
	{
		printf("%d  ",sorted[i]);
	}
}