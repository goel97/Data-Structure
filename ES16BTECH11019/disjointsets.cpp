#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int root (int mark[],int t)			//to find the root of value
{
    while(mark[t] != t)				//till entry is ame as the index
    {
    	mark[t] = mark[mark[t]];
        t = mark[t];
    }
    return t;
}

int find1(int mark[],int x,int y)		//to check if they belong to same set
{
	if(root(mark,x)==root(mark,y))		//if root of two value is same then they belong to same set
		return 1;
	else
		return 0;
}

void union1 (int mark[],int x, int y)	//to combine two sets
{
    int p = root(mark,x);
    int q = root(mark,y);
    mark[p] = mark[q];			//to combine, we make root of one set as the other element
}

void printsets(int mark[],int v)				//prints same value for all elements in same set
{
	int p;
	printf("\nNumber\t Respective Root\n");
	for (int i = 1; i <=v; ++i)
	{
		p=root(mark,i);
		printf("%d\t\t%d\n",i,p);
	}
}

int main()
{
	int v,i,x,y,k=0,opp;				//v:vertices,rest are uitility variables

	printf("Total Vertices :");
	scanf("%d",&v);

	int mark[v];					//array of v vertices

	for (int i = 1; i <=v; ++i)		//array initialization
		mark[i]=i;

	do{
			printf("\nMenu:\n\n1.Union \n2.Find \n3.Print all disjoint sets\n4.Exit\n"); 							//to display menu
			scanf("%d",&opp);
																		//takes input from user and passes it to switch 
			switch(opp)
			{
				case 1:  // for union operation
					printf("Enter the numbers: ");
					scanf("%d%d",&x,&y);
					if(x<1||x>v||y<1||y>v)
					{
						printf("Incorrect Input!\n");
						break;
					}	
					k=find1(mark,x,y);
					if(k==1)
						printf("Numbers Already belong to same set\n");
					else
					{
						printf("Numbers belong to different sets,combining..\n");																	//to combine to sets
						union1(mark,x,y);
						printf("Sets combined!\n");	
					}							
					break;

				case 2:		//to find if two values belong to same set
					printf("Enter the numbers: ");
					scanf("%d%d",&x,&y);		
					if(x<1||x>v||y<1||y>v)
					{
						printf("Incorrect Input!\n");
						break;
					}										
					k=find1(mark,x,y);		//to search for link between two entries
					if(k==1)
						printf("Yes they belong to same set\n");
					else
						printf("No, belong to different sets\n");
					break;

				case 3:		//to print the in what set each value lie
					printsets(mark,v);
					break;
					
				case 4:
					break;

				default :
					printf("Invalid Input\n");			
			}
		}while(opp!=4); 

	return 0;
}