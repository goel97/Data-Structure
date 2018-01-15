#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max 300

int heap[Max];
int size=1;		//maintains the number of elements(size-1) in heap

void heapify_bottom() //to adjust the heap array on insertion
{
	int flag=1,temp;
	int i=size-1;
	while(i>1&&flag==1)		//untill we reach root
	{
		if(heap[(i)/2]>heap[i])		//if parent is greater than child, swap
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

void heapify_top()				//to adjust the array after deletion of minimum
{
	int smallest,temp;
	int i=1,k=1;

	while(i<(size-1)&&size>(2*i))	//untll you reachlast element in array
	{
		smallest=heap[i];			//let subtree parent be the smallest
		if(smallest>heap[2*i])		//if left child is smallest
		{
			smallest=heap[2*i];
			k=2*i;
		}
		if(smallest>heap[2*i+1]&&size>(2*i+1))//if right child is smallest
		{
			smallest=heap[2*i+1];
			k=2*i+1;
		}
		if(smallest!=heap[i])		//ifsubtree parent is not thee smallest swap it with the smaller child
		{
			temp=heap[i];
			heap[i]=smallest;
			heap[k]=temp;
			i=k;					//continue till you reach end of array
		}
		else
			break;
	}
}

void insert()
{
	printf("Enter Number: ");
	scanf("%d",&heap[size]); 	//put the new entry at the back of array
	size++;						//increases count of total entries
	heapify_bottom();			//callls heapify to readjust this new element
	printf("Entery Added!\n");
}

void return_min()
{
	if(size>1)
		printf("\nMinimum : %d\n",heap[1]);//returns the vlaue at index 1 (minimum value)
	else
		printf("List Empty!\n");
}

void delete_min()
{
	if(size>1)
	{
		heap[1]=heap[size-1];				//replaces the number at index 1 (minimum entry) with last entry
		size--;								//decrease size to delete last entry
		heapify_top();						//heapify to adjust the new heap array
		printf("Minimum Deleted!\n");
	}
	else
		printf("List Empty!\n");
}

void print()
{
	int i;
	for (int i = 1; i < size; i++)			//print the heap array
	{
		printf(" %d --",heap[i]);
	}
	printf("\n");
}

int main()
{
	int opp;
	
		do{
			printf("\nMenu:\n\n1.Insert \n2.Return Minimum\n3.Delete Minimum\n4.Print All entries\n5.Exit\n"); 	//to display menu
			scanf("%d",&opp);						//takes input from user and passes it to switch 
			switch(opp)
			{
				case 1:								//to insert an entry
					insert();								
					break;
				case 2:								//to search for minimum
					return_min();
					break;
				case 3:								//to delete an minimun entry
					delete_min();
					break;
				case 4:								//to print all entries
					print();
					break;
				case 5:								//to exit
					break;
				default :
					printf("Invalid Input\n");			
			}
		}while(opp!=5); 

	return 0;
}