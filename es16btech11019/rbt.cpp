//RED Black tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

struct node
{
	int id;					//input id
	char colour;			//BLACK =b RED= r 
	struct node *left;		//node's left child
	struct node *right;		//node's right child
	struct node *parent;	//nde's parent	
};
struct node *head=NULL;

void left_rotate(struct node* x)	//used to maintain rbt properties in case of insertion CASE 2 & 3
{
	struct node* y;
	y=x->right;
	x->right=y->left;
	if(y->left!=NULL)
		y->left->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		head=y;
	else if(x==x->parent->left)
		x->parent->left=y;
	else
		x->parent->right=y;
	y->left=x;
	x->parent=y;
}

void right_rotate(struct node* x)	//used to maintain rbt properties in case of insertion CASE 2 & 3
{
	struct node* y;
	y=x->left;
	x->left=y->right;
	if(y->right!=NULL)
		y->right->parent=x;
	y->parent=x->parent;
	if(x->parent==NULL)
		head=y;
	else if(x==x->parent->left)
		x->parent->left=y;
	else
		x->parent->right=y;
	y->right=x;
	x->parent=y;
}

void rbtfixup(struct node* new_node)
{
	struct node* uncle;
	if(new_node->parent!=NULL)	//if the added node is not root
		while((new_node->parent!=NULL)&&(new_node->parent->colour=='r'))//if parent colour is red
		{
			if(new_node->parent==new_node->parent->parent->left)//if parent is left child of grandparent
			{
				uncle=new_node->parent->parent->right;
				if((uncle!=NULL)&&(uncle->colour=='r'))//if uncle exist and uncle is red CASE 1
				{
					new_node->parent->colour='b';
					uncle->colour='b';
					new_node->parent->parent->colour='r';
					new_node=new_node->parent->parent;
				}	
				else	//if uncle does not exist or uncle is black
				{
					if(new_node==new_node->parent->right) //CASE 2
					{
						new_node=new_node->parent;
						left_rotate(new_node);
					}	//CASE 3
					new_node->parent->colour='b';
					new_node->parent->parent->colour='r';
					right_rotate(new_node->parent->parent);
				}
			}
			else	//if parent is right child of grandparent
			{
				uncle=new_node->parent->parent->left;
				if((uncle!=NULL)&&(uncle->colour=='r'))
				{
					new_node->parent->colour='b';
					uncle->colour='b';
					new_node->parent->parent->colour='r';
					new_node=new_node->parent->parent;
				}	
				else
				{
					if(new_node==new_node->parent->left)
					{
						new_node=new_node->parent;
						right_rotate(new_node);
					}	
					new_node->parent->colour='b';
					new_node->parent->parent->colour='r';
					left_rotate(new_node->parent->parent);
				}
			}
		}
	else
		new_node->colour='b';	//if added node is root
	head->colour='b';	//colour of root is always black
}

void insert()
{
	int n;
	
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	
	printf("Enter ID:");
	scanf("%d",&n);
	new_node->id=n;
	new_node->colour='r';
	
	if(head==NULL)					//for adding the first element(root)
	{
		head=new_node;
		new_node->left=NULL;
		new_node->right=NULL;
		new_node->parent=NULL;
	}
	else
	{
		struct node *temp=head,*prev=NULL;
		int p=0;
		while((temp!=NULL))
			if((temp->id)>(new_node->id))	//if entry is less than node
				{
					p=1;
					prev=temp;
					temp=temp->left;
				}
			else if((temp->id)<(new_node->id))	//if entry is greater than node
				{
					p=2;
					prev=temp;
					temp=temp->right;
				}
		if(p==1)						//adding element on the left subtree
		prev->left=new_node;
		else if(p==2)		
		prev->right=new_node;			//adding element on the right subtree
		new_node->parent=prev;
		new_node->left= NULL ;
		new_node->right= NULL ;
	}
	rbtfixup(new_node);		//to miantain red black tree properties
	printf("ID:%d Colour= %c\n\n",new_node->id,new_node->colour);
	printf("Entry added!\n\n");
}

void search()
{
	int key;
	printf("Enter name:");
	scanf("%d",&key);
	
	struct node *temp=head;
	
	if(head==NULL)							//if tree empty
		printf("NotFound!\n");
	else
	{
		while(temp!=NULL)					//searching key if the tree is not empty
		{
			if((temp->id)==key)
			{
				printf("Found ID:%d\n\n",temp->id);
				break;
			}
			else if((temp->id)>key)
				temp=temp->left;
			else
				temp=temp->right;
		}
		if(temp==NULL)						//if element is not in tree
			printf("NotFound!\n");
	}
}

void print(struct node *temp)
{
	if(temp!=NULL)
	{
		if(temp->left)
			print(temp->left);				//inorder printing of tree
		printf("%d     %c\n\n",temp->id,temp->colour);
		if(temp->right)
			print(temp->right);
	}
	else
		return;
}

void print_rbt(struct node *temp,int p)
{
		if(temp!=NULL)
		{
			if(temp->right)
				print_rbt(temp->right,p+7);
			for(int i=0;i<p;i++)
				printf(" ");				//inorder printing in form of tree
			printf("%d %c\n\n",temp->id,temp->colour);
			if(temp->left)
				print_rbt(temp->left,p+7);
		}
		else
			return;
}

void free_memory(struct node* temp)
{
	if(temp!=NULL)					//post order of freeing memory 
		{
			if(temp->left)
				free_memory(temp->left);						
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
			printf("Menu:\n\n1.Insert \n2.Search\n3.Print All entries\n4.Free memory\n5.Exit\n"); 	//to display menu
			scanf("%d",&opp);	//takes input from user and passes it to switch 
			switch(opp)
			{
				case 1:						//to insert an entry
					insert();								
					break;
				case 2:						//to search for an entry 
					search();
					break;
				case 3:
					printf("ID   Colours\n\n");		//to print all entries
					print(head);
					print_rbt(head,0);
					break;
				case 4:						//to free all the allocated memory
					free_memory(head);
					head=NULL;
					break;
				case 5:
					break;
				default :
					printf("Invalid Input\n");			
			}
		}while(opp!=5);	
		
	return 0;
}