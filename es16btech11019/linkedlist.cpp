//linked list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
struct node
{
	char name[50];
	char college[100];
	char gender[10];
	struct node *ptr;
};

struct node *head=NULL;

void insert()
{
	char n[50];
	char c[100];
	char g[10];
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	cin.ignore();
	printf("Enter name:");
	cin.getline(n,50);
	printf("Enter College:");
	cin.getline(c,100);
	printf("Enter Gender:");
	scanf("%s",g);
	strcpy(new_node->name,n);
	strcpy(new_node->college,c);
	strcpy(new_node->gender,g);
	if(head==NULL)
	{
		head=new_node;
		new_node->ptr=NULL;
	}
	else
	{
		new_node->ptr=head;
		head=new_node;
	}
	printf("Entry added!\n\n");
}

void search()
{
	char key[50];
	printf("Enter name:");
	cin.ignore();
	cin.getline(key,50);
	struct node *temp=head;
	if(head==NULL)
		printf("NotFound!\n");
	else
	{
		while(temp!=NULL)
		{
			if(strcmp((temp->name),key)==0)
			{
				printf("name:%s\nCollege:%s\ngender:%s\n\n",temp->name,temp->college,temp->gender);
				break;
			}
			temp=temp->ptr;
		}
		if(temp==NULL)
		printf("NotFound!\n");
	}
}

void delete_one()
{
	char key[50];
	cin.ignore();
	printf("Enter name:");
	cin.getline(key,50);
	struct node *temp=head;
	struct node *q=head;
	if(head==NULL)
		printf("Not found! List is Emprty!\n");
	else
	{
		while(temp!=NULL)
		{
			if(strcmp((temp->name),key)==0)
			{
				q=temp;
				break;
			}
			temp=temp->ptr;
		}
		if(temp==NULL)
			printf("NotFound!\n\n");
		else
		{
			if(q==head)
			{
				if((q->ptr)==NULL)
				{
					head=NULL;
					free(q);
				}
				else
				{
					head=q->ptr;
					free(q);
				}
			}
			else
			{
				temp=head;
				while(temp->ptr!=q)
					temp=temp->ptr;
				temp->ptr=q->ptr;
				free(q);
			}
			printf("Entry Deleted!\n\n");
		}
	}
}

void print()
{
	struct node* temp=head;
	while(temp!=NULL)
	{
		printf("name:%s\nCollege:%s\ngender:%s\n\n",temp->name,temp->college,temp->gender);
		temp=temp->ptr;
	}
}

int main()
{
	int opp;
		do
		{
			printf("Menu:\n\n1.Insert \n2.Search\n3.Delete\n4.Print All entries\n5.Exit\n"); 	//to display menu
			scanf("%d",&opp);															//takes input from user and passes it to switch 
			switch(opp)
			{
				case 1:																	//to insert an entry
					insert();								
					break;
				case 2:																	//to search for an entry 
					search();
					break;
				case 3:																	//to delete an entry
					delete_one();
					break;
				
				case 4:																	//to print all entries
					print();
					break;
				case 5:
					break;
				
				default :
					printf("Invalid Input\n");			
			}
		}while(opp!=5);	
	return 0;
}
