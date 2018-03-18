//RED Black tree with delete
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
struct node *par;
char col;

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
				printf("ID:%d\n\n",temp->id);
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

void transplant( struct node *u, struct node *v)			// to connect u's parent to v
{
	if(u->parent==NULL)	
		head=v;										
	else if(u==u->parent->left)
		u->parent->left=v;							
	else	
		u->parent->right=v;
	if(v!=NULL)
		v->parent=u->parent;
}

struct node* minimum(struct node *z)
{
	while(z->left!=NULL)														//Traverse till left to get  minimum
		z=z->left;
	return z;
}

struct node* search_i (int t)
{	
	struct node* x=head;
	while(x != NULL)											//traverse till sentinel node
	{
		if(x->id == t)													// if it is x is data then return 
			{
				return x;
			}
		else if(x->id < t)												//if x<t then move right
			{	
				x=x->right;
			}
		else if(x->id > t)												//if x>t then move left
			{	
				x=x->left;
			} 
	}
	return x;													//if not found return sentinel
}

void deletefixup(struct node *x,int flag)
{
	if(flag==1)
	{
		while(x->parent!=NULL && x->colour=='b')									//till x is not a root and x has colour black
		{	
			if(x==x->parent->left)														
			{
				struct node *sibling;
				sibling=x->parent->right;
				if(sibling->colour=='r')									//Case 1: If x's sibling is red
				{	
					sibling->colour='b';
					x->parent->colour='r';									//make sibling black parent red and left rotate about x's parent
					left_rotate(x->parent);
					sibling=x->parent->right;
				
					if(sibling->left->colour=='b' && sibling->right->colour=='b')
					{	
						sibling->colour='r';									//Case 2: if sibling is black and both siblings children are also black
						x=x->parent;											//make that sibling red and take it above to parent 
					}
					else if(sibling->right->colour=='b')
					{	
						sibling->left->colour='b';							//Case 3: if siblings left child is red and right is black 
						sibling->colour='r';									//right rotate about siblings and make sibling asred and siblings left as black
						right_rotate(sibling);
						sibling=x->parent->right;
					}

					sibling->colour=x->parent->colour;						//Case 4:if both child are red
					x->parent->colour='b';
					sibling->right->colour='b';							//Left Rotate about parent and make parent color black and siblings also black
					left_rotate(x->parent);
					x=head;
				}
			}
			else																//Same as above and swap left with right
			{	
				struct node *sibling;
				sibling=x->parent->left;
				if(sibling->colour=='r')
				{	
					sibling->colour='b';
					x->parent->colour='r';
					right_rotate(x->parent);
					sibling=x->parent->left;
				
					if(sibling->left->colour=='b' && sibling->right->colour=='b')
					{	
						sibling->colour='r';
						x=x->parent;
					}
					else if(sibling->left->colour=='b')
					{	
						sibling->right->colour='b';
						sibling->colour='r';
						left_rotate(sibling);
						sibling=x->parent->left;
					}

					sibling->colour=x->parent->colour;
					x->parent->colour='b';
					sibling->left->colour='b';
					right_rotate(x->parent);
					x=head;
				}	
			}
		}
		x->colour='b';	
	}															// In the end x reaches root and make sure root is black
	else
	{
		while(par!=NULL && (col=='b'||x->colour=='b'))									//till x is not a root and x has colour black
		{
			printf("hhhhh\n");	
			col='t';
			if(x==par->left)														
			{
				struct node *sibling;
				sibling=par->right;
				if(sibling->colour=='r')									//Case 1: If x's sibling is red
				{	
					sibling->colour='b';
					par->colour='r';									//make sibling black parent red and left rotate about x's parent
					left_rotate(par);
					sibling=par->right;
				}
				if(sibling->left->colour=='b' && sibling->right->colour=='b')
				{	
					sibling->colour='r';									//Case 2: if sibling is black and both siblings children are also black
					x=par;											//make that sibling red and take it above to parent 
					par=par->parent;
				}
				else if(sibling->right->colour=='b')
				{	
					sibling->left->colour='b';							//Case 3: if siblings left child is red and right is black 
					sibling->colour='r';									//right rotate about siblings and make sibling asred and siblings left as black
					right_rotate(sibling);
					sibling=x->parent->right;
				}
				
				printf("tttt\n");
				sibling->colour=par->colour;						//Case 4:if both child are red
				par->colour='b';
				sibling->right->colour='b';							//Left Rotate about parent and make parent color black and siblings also black
				left_rotate(par);
				x=head;
			}
			else																//Same as above and swap left with right
			{	
				struct node *sibling;
				sibling=par->left;
				if(sibling->colour=='r')
				{	
					sibling->colour='b';
					par->colour='r';
					right_rotate(par);
					sibling=par->left;
				}
				if(sibling->left->colour=='b' && sibling->right->colour=='b')
				{	
					sibling->colour='r';
					x=par;
					par=par->parent;
				}
				else if(sibling->left->colour=='b')
				{	
					sibling->right->colour='b';
					sibling->colour='r';
					left_rotate(sibling);
					sibling=par->left;
				}

				sibling->colour=par->colour;
				par->colour='b';
				sibling->left->colour='b';
				right_rotate(par);
				x=head;
					
			}
		}
		x->colour='b';
	}
}
void delete_rbt(int t)
{
	struct node *z;
	struct node *x;
	//printf("ttttttm\n");
	if(search_i (t)==NULL)												//Search if element is there
	{
		cout<<"Element Not Found"<<endl;
		return;
	}
	if(head==NULL)												//Check if tree is empty or not
	{
		cout<<"Tree empty";
		return;
	}	
	z=search_i (t);														//search for the key to be deleted
	struct node *y;
	y=z;
	char yorg;															// to note color of deleted/replaced node
	yorg=y->colour;
	if(z->left==NULL)			
	{
		x=z->right;
		transplant(z,x);
		if(x==NULL)
			col=z->colour;
		par=z->parent;
		free(z);
	}
	else if(z->right==NULL)
	{	
		x=z->left;														//vice versa as above
		if(x==NULL)
			col=z->colour;
		transplant(z,z->left);
		par=z->parent;
		free(z);
	}
	else
	{
		y=minimum(z->right);										 // now if z is a two child node get minimum 
		yorg=y->colour;												 // get original color of the node with which it is swapped
		
		x=y->right;
		
		if(y->parent==z)
			x->parent=y;
		else
		{
			transplant(y,y->right);
			y->right=z->right;
			y->right->parent=y;
		}
		transplant(z,y);
		y->left=z->left;
		y->left->parent=y;
		y->colour=z->colour;
		free(z);
	}		
	if(yorg=='b')	
	{
		if(x==NULL)
		deletefixup(x,2);				//If y had a color black then only a violation can occur so call DeleteFixup
		else
		deletefixup(x,1);	
	}	
}

int main()
{
	int opp,k;
	
		do{
			printf("Menu:\n\n1.Insert \n2.Search\n3.Print All entries\n4.Delete\n5.Free memory\n6.Exit\n"); 	//to display menu
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
				case 4:
					printf("Enter key:");
					scanf("%d",&k);
					delete_rbt(k);
					printf("deleted!\n");
					break;
				case 5:						//to free all the allocated memory
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