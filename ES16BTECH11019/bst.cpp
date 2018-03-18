//Binary search tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
struct node
{
	int name;				//id of number
	struct node *left;		// to access left child
	struct node *right;		//to access right child
};
struct node *head=NULL;

void insert()
{
	int n;	
	struct node* new_node = (struct node*) malloc(sizeof(struct node));//memory allocation for new node
	
	printf("Enter Id:");	//id of new node
	scanf("%d",&n);
	
	new_node->name=n;

	if(head==NULL)		//if bst empty,for adding the first element(root)
	{
		head=new_node;
		new_node->left=NULL;	//left child is empty
		new_node->right=NULL;	//right child is empty
	}
	else
	{
		struct node *temp=head,*prev;
		int p=0;
		while((temp!=NULL))		//to traverse to the leaf to add the node at appropriate location
			if((temp->name)>(new_node->name))	//if id is less than current node, move left
				{
					p=1;
					prev=temp;
					temp=temp->left;
				}
			else if((temp->name)<(new_node->name))	//if id is greater than current node, move right
				{
					p=2;
					prev=temp;
					temp=temp->right;
				}
		if(p==1)					//adding element on the left subtree
		prev->left=new_node;
		else if(p==2)		
		prev->right=new_node;		//adding element on the right subtree
		new_node->left= NULL ;		//making childs of added node empty
		new_node->right= NULL ;
	}
	printf("Entry added!\n\n");
}

void search()
{
	int key;		//element which we need to find
	printf("Enter Id:");
	scanf("%d",&key);
	
	struct node *temp=head;
	
	if(head==NULL)				//if tree empty
		printf("NotFound!\n");
	else
	{
		while(temp!=NULL)		//searching key if the tree is not empty
		{
			if((temp->name)==key)
			{
				printf("Id:%d\n\n",temp->name);
				break;
			}
			else if((temp->name)>key)		//if id is less than current node, move left
				temp=temp->left;
			else							//if id is greater than current node, move right
				temp=temp->right;
		}
		if(temp==NULL)						//if element is not in tree
			printf("NotFound!\n");
	}
}

void delete_one()
{
	int key,flag1=0;
	printf("Enter Id:");
	scanf("%d",&key);
	
	struct node *temp=head,*prev=NULL;
	struct node *q=head;
	
	if(head==NULL)													
		printf("Not found! List is Emprty!\n");
	else
	{
		while(temp!=NULL)						//searching for element to be deleted
		{
			if((temp->name)==key)
			{					
				q=temp;							//if found,q is the address of the key 
				break;
			}
			else if((temp->name)>key)			//if id is less than current node, move left
			{
				flag1=1;
				prev=temp;
				temp=temp->left;
			}
			else								//if id is greater than current node, move right
			{
				flag1=2;
				prev=temp;
				temp=temp->right;
			}
		}
		if(temp==NULL)							//if traverse till leaf child and not found
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
						{
							if(flag1==1)
							prev->left=NULL;
							else if(flag1==2)
							prev->right=NULL;	
							free(q);
						}
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
				else 										//key have both child
				{	
					int flag=0;
					struct node *p_temp=q,*prev1;			//p_temp temporary loction of the key used to traverse the tree
					p_temp=p_temp->left;	
					while(p_temp->right!=NULL)				//finding the predecessor
					{
						flag=1;
						prev1=p_temp;
						p_temp=p_temp->right;
					}
					q->name=p_temp->name;		//replace the data of deleted element with the smallest on its right subtree
					if(flag==1)
					prev1->right=NULL;
					else
					q->left=p_temp->left;			
					free(p_temp);
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
				print(temp->left);								//inorder printing of tree
			printf("Id:%d\n\n",temp->name);
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
			printf(" ");										//inorder printing in form of tree,p=spaces
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
				free_memory(temp->left);						//freeing the memory after excecution
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
				case 5:																	//to free the allocated memory
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
