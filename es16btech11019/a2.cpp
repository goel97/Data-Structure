//Binary search tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
struct node
{
	int name;
	char college[100];
	char gender[10];
	struct node *left;
	struct node *right;
};
struct node *head=NULL;

void insert()
{
	int n;
	char c[100];
	char g[10];
	
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	
	printf("Enter name:");
	scanf("%d",&n);
	printf("Enter College:");
	cin.ignore();
	cin.getline(c,100);
	printf("Enter Gender:");
	scanf("%s",g);
	new_node->name=n;
	strcpy(new_node->college,c);
	strcpy(new_node->gender,g);
	
	if(head==NULL)											//for adding the first element(root)
	{
		head=new_node;
		new_node->left=NULL;
		new_node->right=NULL;
	}
	else
	{
		struct node *temp=head,*prev;
		int p=0;
		while((temp!=NULL))
			if((temp->name)>(new_node->name))
				{
					p=1;
					prev=temp;
					temp=temp->left;
				}
			else if((temp->name)<(new_node->name))
				{
					p=2;
					prev=temp;
					temp=temp->right;
				}
		if(p==1)								//adding element on the left subtree
		prev->left=new_node;
		else if(p==2)		
		prev->right=new_node;					//adding element on the right subtree
		new_node->left= NULL ;
		new_node->right= NULL ;
	}
	printf("Entry added!\n\n");
}

void search()
{
	int key;
	printf("Enter name:");
	scanf("%d",&key);
	
	struct node *temp=head;
	
	if(head==NULL)												//if tree empty
		printf("NotFound!\n");
	else
	{
		while(temp!=NULL)										//searching key if the tree is not empty
		{
			if((temp->name)==key)
			{
				printf("name:%d\nCollege:%s\ngender:%s\n\n",temp->name,temp->college,temp->gender);
				break;
			}
			else if((temp->name)>key)
				temp=temp->left;
			else
				temp=temp->right;
		}
		if(temp==NULL)											//if element is not in tree
			printf("NotFound!\n");
	}
}

void delete_one()
{
	int key;
	printf("Enter name:");
	scanf("%d",&key);
	
	struct node *temp=head,*prev=NULL;
	struct node *q=head;
	
	if(head==NULL)													
		printf("Not found! List is Emprty!\n");
	else
	{
		while(temp!=NULL)											//searching for element to be deleted
		{
			if((temp->name)==key)
			{					
				q=temp;												//q is the address of the key 
				break;
			}
			else if((temp->name)>key)
			{
				prev=temp;
				temp=temp->left;
			}
			else
			{
				prev=temp;
				temp=temp->right;
			}
		}
		if(temp==NULL)
			printf("NotFound!\n\n");
		else
		{
			if(q->right==NULL)
			{
				if(q->left==NULL)					//key have both child empty
					{
						if(q==head)					//key is root
						{
							head=NULL;
							free(q);
						}
						else
						free(q);
					}
				else 								//key has only left child
				{
					if(q==head)						//key is root
					{
						head=q->left;
						free(q);
					}
					else
					{
						prev->left=q->left;
						free(q);
					}
				}				
			}
			else 
			{
				if(q->left==NULL)					//key has only right child
				{
					if(q==head)						//key is root
					{
						head=q->right;
						free(q);
					}
					else
					{
						prev->right=q->right;
						free(q);
					}
				}	
				else 								//key have both child
				{	
					struct node *p_temp=q;			//p_temp temporary laction of the key used to traverse the tree
					p_temp=p_temp->left;	
					while(p_temp->right!=NULL)
						p_temp=p_temp->right;
					q->name=p_temp->name;				//replace the data of deleted element with the smallest on its right subtree
					strcpy(q->college,p_temp->college);
					strcpy(q->gender,p_temp->gender);
					free(p_temp->right);
					free(p_temp->left);
					p_temp=NULL;
				}
			}
			printf("Entry Deleted!\n\n");
		}
	}
}

void print(struct node *temp)
{
		if(temp!=NULL)
		{
			if(temp->left)
				print(temp->left);																//inorder printing of tree
			printf("name:%d\nCollege:%s\ngender:%s\n\n",temp->name,temp->college,temp->gender);
			if(temp->right)
				print(temp->right);
		}
		else
			return;
}

void print_bst(struct node *temp,int p)
{
	if(temp!=NULL)
	{
		if(temp->right)
			print_bst(temp->right,p+4);
		for(int i=0;i<p;i++)
			printf(" ");											//inorder printing of tree
		printf("%d\n",temp->name);
		if(temp->left)
			print_bst(temp->left,p+4);
	}
	else
		return;
}

void free_memory(struct node* temp)
{
	if(temp!=NULL)
		{
			if(temp->left)
				free_memory(temp->left);																//inorder printing of tree
			if(temp->right)
				free_memory(temp->right);
			free(temp);
		}
		else
			return;
}
int main()
{
	int opp;
	
		do{
			printf("Menu:\n\n1.Insert \n2.Search\n3.Delete\n4.Print All entries\n5.Free memory\n6.Exit\n"); 	//to display menu
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
					print(head);
					print_bst(head,0);
					break;
				case 5:
					free_memory(head);
					head=NULL;
					break;
				case 6:
					break;
				default :
					printf("Invalid Input\n");			
			}
		}while(opp!=6);	
		
	return 0;
}
