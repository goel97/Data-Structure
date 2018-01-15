// Btree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int t;						//t is degree of btree

struct node
{
	int n;                      //number of keys currently in node         
	bool leaf; 					//if node is leaf
	int *key;					//array of keys
	struct node **child;		//array of children
};

struct node *head=NULL;			//head of btree

struct node* allocate()			//function to allocate memory to each new node on insertion
{
	struct node *h=new node();
	h->key=new int[2*t];		//allocates an array of keys of size 2deg, we start inserting from index 1
	h->child=new node*[2*t+1];	//allocates an array of children of size 2deg+1, we start inserting from index 1
	for (int i = 0; i < 2*t+1; ++i)
		h->child[i]=NULL;
	return h;
}

void create()
{
	struct node* x=allocate();		//for initialising the tree
	x->leaf=true;
	x->n=0;							//number of keys on initialisation is 0
	head=x;
}

int search(struct node *temp,int val)
{	
	int i;
	if(temp==NULL)										//if tree empty
		printf("Empty!\n");
	else
	{
		i=1;
		while(i<=(temp->n)&&val>(temp->key[i]))			//searching key if the tree is not empty
			i=i+1;
		if(i<=temp->n&&val==temp->key[i])				//printing key if found
		{
			printf("Id:%d Found\n",temp->key[i]);
			return 1;
		}
		else if(temp->leaf)								//if we reach leaf
		{
			printf("Not found\n");
			return 0;
		}
		else											//calling recursion to move to children
			search(temp->child[i],val);	
	}
}

void split_child(struct node* x, int i)			//in case there is a possibility of number of keys more than 2deg-1, we split that child of x
{
	struct node *z;
	struct node *y;

	z=allocate();					//allocate memory to the new node

	y=x->child[i];					//y is the current child of node to be split
	z->leaf=y->leaf;				//if y is leaf then z will be leaf
	z->n=t-1;						

	for (int j = 1; j <=t-1 ; ++j)	//copying keys to z from y
		z->key[j]=y->key[j+t];

	if(!y->leaf)
		for (int j = 1; j <=t; ++j)	//copying child to z from y
			z->child[j]=y->child[j+t];
	y->n=t-1;						//changing the new number of keys in y

	for (int j = x->n+1; j >i; --j)	//changing the children of x after splitting
		x->child[j+1]=x->child[j];
	x->child[i+1]=z;

	for (int j = x->n; j > i-1; j--)
		x->key[j+1]=x->key[j];
	x->key[i]=y->key[t];			//moving a key from y to x
	x->n=x->n+1;					//increasing the number of keys in x after splitting
}

void insert_nonfull(struct node *x,int k)	//function of inserting key in x, when x is not full
{
	int i=x->n;

	if(x->leaf)						//if the node x is leaf, add at suitable position
	{
		while(i>=1&&k<x->key[i])
		{
			x->key[i+1]=x->key[i];
			i--;
		}
		x->key[i+1]=k;
		x->n=x->n+1;
	}
	else						//traverse to the suitable child and call recursion
	{
		while(i>=1&&k<x->key[i])
			i--;
		i=i+1;
		if(x->child[i]->n==(2*t-1))		//if number of keys are maxed out, split the node
		{
			split_child(x,i);
			if(k>x->key[i])
				i++;
		}
		insert_nonfull(x->child[i],k);	//call insert-nonfull and pass the appropriate child
	}
}

void insert_bt(struct node *tmp,int k)
{
	struct node *r=tmp;
	if(r->n==(2*t-1))				//if the node is full, split it and call insert non full
	{
		struct node *s=allocate();	//allocate memory to new node for splitting
		head=s;						//make s as the new head and split the actual head
		s->leaf=false;
		s->n=0;
		s->child[1]=r;
		split_child(s,1);			//to split and make s as the new head
		insert_nonfull(s,k);
	}
	else
		insert_nonfull(r,k);	//if node is not full call insert non full
}

void print_bt(struct node *temp, int p)		// to print btree in form of a tree
{
    int i;
    if (temp)
    {
        for (i=1;i<temp->n+1;i++)				//recurively move for n(number of keys) times
        {
            print_bt(temp->child[i],p+5);		//recursively call the lestmost child
            for(int j=0;j<p;j++)
                printf(" ");
            printf("%d\n",temp->key[i]);
        }
        print_bt(temp->child[temp->n+1],p+5);
    }
    else
    	return;
}

void print(struct node *temp)		//to print btree in form of sets of keys
{
	if(temp->leaf)
	{	
		printf("{ ");
		for (int i = 1; i <=temp->n; ++i)
		{
			printf("%d ",temp->key[i]);
		}
		printf("} ");
	}
	else
	{
		for (int i = 1; i <=temp->n+1; ++i)
		{
			print(temp->child[i]);
		}
		printf("\n");
		for (int i = 1; i <=temp->n; ++i)
		{
			printf("%d  ",temp->key[i]);
		}
		printf("\n");
	}
}

int get_pre(struct node* p)		//to find the predecessor , utility function in delete
{
	int j=0;
	while(p!=NULL)	//till be reach end of btree
	{
		j=p->key[1];	//j is the smallest key in p
		p=p->child[1];
	}
	return j;		//returns the largest predecessor
}

int get_suc(struct node* p)		//to find the successor , utility function in delete
{
	int j=0;
	while(p!=NULL)		//till be reach end of btree
	{
		j=p->key[p->n];		//j is the largest key in p 
		p=p->child[p->n+1];
	}
	return j;		//returns the smallest successor
}

void delete_bt(struct node *z,int k)
{
	if(head->n==0)
	{
		struct node *q=head;
		head=head->child[1];
		delete q;
	}
	int i=1;
	if(z->leaf==true)						//case 1. the key is in leafs
	{
		while(i<z->n+1  && k>z->key[i])		// to find the index of key
			i++;
		for (int j = i; j < z->n; ++j)		//shifting keys fwd to replace the deleted key
			z->key[j]=z->key[j+1];
		z->n=z->n-1;
	}
	else		//case2 or 3, if key is in internal nodes
	{
		while(i<z->n+1&&k>z->key[i])
			i++;
		if(i<=z->n && k==z->key[i])			//case 2 , if key found in that node
		{
			if((z->child[i+1]->n)>t-1)			//if number of keys are more than minimum allowed	
			{
				int l=get_pre(z->child[i+1]);	//find predecessor and replace it with key and delete predecessor recursively
				delete_bt(z->child[i+1],l);
				z->key[i]=l;
			}
			else if((z->child[i]->n)>t-1)		//if number of keys are more than minimum allowed
			{
				int l=get_suc(z->child[i]);		//find successor and replace it with key and delete successor recursively
				delete_bt(z->child[i],l);
				z->key[i]=l;
			}
			else							//if degree of both is less than t-1, merge both and key
			{
				struct node* t1=z->child[i];
				struct node* t2=z->child[i+1];
											//merging
				if(t1->leaf==false)				
					for(int j=1;j<=t;j++)
						t1->child[t+j]=t2->child[j];
				t1->key[t]=k; 				//put key in this array as well
				int l=1;
				while(l<t)					//merging the keys to t1
				{
					t1->key[t+l]=t2->key[l];
					l++;
				}			
				for(int j=i;j<=z->n-1;j++)		//replacing key with next key and rearranging keys in parent
					z->key[j]=z->key[j+1];
				for(int j=i+1;j<=z->n;j++)		//moving each child accordingly	in parent
					z->child[j]=z->child[j+1];
				z->n--;							//reducing count due to key movement
				t1->n=2*t-1;					//new count of child
				delete t2;
				delete_bt(z->child[i],k);
			}
		}
		else	//case 3 is for transvarsal if key is in lower node
		{
			struct node* c=z->child[i];		//c is the child which may contain the key to be deleted

			if(c->n==t-1)		//if number of keys in c is exactly equal to minimum allowed
			{
				if(z->child[i-1]!=NULL && z->child[i-1]->n>=t) 	//borrowing from left sibling if it has more than t-1 key
				{
					struct node* m1=z->child[i-1];			//m1 is the child from which we are borrowing
					for(int j=t-1;j>=1;j--) 				//shifting keys to right so that parent come in at position 1
						c->key[j+1]=c->key[j];
					c->key[1]=z->key[i-1];					//parent comes at position 1
					z->key[i-1]=m1->key[m1->n];				//new parent is the last key of m1
					if(c->leaf==false)						//if c is not leaf, shift the child else not required
					{
						for(int j=t;j>=1;j--)
							c->child[j+1]=c->child[j];
						c->child[1]=m1->child[m1->n+1];
						m1->child[m1->n+1]=NULL;
					}
					m1->n--;							//sice one key from m1 is borrowed, size decreases
					c->n++;								//since number of keys in c increases by 1
					delete_bt(c,k);          			//now call delete on child of z
				}
				else if(z->child[i+1]!=NULL && z->child[i+1]->n>=t) //borrowing from right sibling if it has more than t-1 keys
				{
					struct node* m1=z->child[i+1];				//m1 is the child from which we are borrowing
					c->key[c->n+1]=z->key[i];					//adding the parent key to c	
					c->n++;										//since number of keys in c increases by 1
					z->key[i]=m1->key[1];						//shifting 1st key from m1 to parent 
					for(int j=1;j<m1->n;j++)					//shifting keys to right so that parent come in at position 1
						m1->key[j]=m1->key[j+1];
					if(c->leaf==false)							//if c is not leaf, shift the child else not required
					{
						c->child[c->n+1]=m1->child[1];
						for(int j=1;j<m1->n+1;j++)
							m1->child[j]=m1->child[j+1];
						m1->child[m1->n+1]=NULL;
					}
					m1->n--;									//sice one key from m1 is borrowed, size decreases
					delete_bt(z->child[i],k);					//now call delete on child of z
				}
				else		//if both right and left sibling has less than t keys, we merge one of them with c so that c has more than t keys
				{
					if(z->child[i+1]!=NULL)		//if i+1 child exist
					{
						struct node* m1=z->child[i+1];		//merging m1 and c and parent into c
						c->key[t]=z->key[i];				//merge the c and parent
						for(int j=1;j<t;j++)				//merging c and m1
							c->key[t+j]=m1->key[j];
						for(int j=i;j<z->n;j++)				//shifting each key of z forward since one key has moved down
							z->key[j]=z->key[j+1];
						for(int j=i+1;j<z->n+1;j++)			//shifting each shild of z forward since one key has moved down
							z->child[j]=z->child[j+1];
						z->n--;								//decreasing the number of keys in z
						if(c->leaf==false)					//if c is not a leaf, making changes in c's child appropriately
							for(int j=1;j<=t;j++)
								c->child[t+j]=m1->child[j];
						c->n=2*t-1;							//updating the number of keys in c
						delete m1;
						delete_bt(c,k);						//recursive call for deletion of k from c
					}
					else	//if i+1th child doesnt exits.Occurs when we have to delte key greter than last key of z
					{
						struct node* m1=z->child[i-1];		//merging m1 and c and parent into m1
						m1->key[t]=z->key[i-1];				//merge the m1 and parent
						for(int j=1;j<t;j++)				//merging c and m1
							m1->key[t+j]=c->key[j];
						z->n--;								//decreasing the number of keys in z
						if(c->leaf==false)					//if c is not a leaf, making changes in c's child appropriately
							for(int j=1;j<=t;j++)
								m1->child[t+j]=c->child[j];
						m1->n=2*t-1;						//updating the number of keys in m1
						delete c;
						delete_bt(m1,k);					//recursive call for deletion of k from c
					}	
				}
			}
			else		//if number of keys are more than minimum allowed
				delete_bt(c,k);	//recursive call to delete k from z's child c
		}
	}
}

void free_memory(struct node* q)//deallocates all the memory
{
	if(q->leaf==false)
	{
		for(int i=1;i<q->n+2;i++)
		{
			free_memory(q->child[i]);//recursive call on child pointer
		}
	}
	delete [] q->key;//dealocates the memory for integer pointers
	delete [] q->child;//dealocates the memory for child pointers
	delete (q);//dealocates the memory for node
	return;
}

int main()
{
	printf("Enter Degree t:");
	scanf("%d",&t);
	create();
	int opp,req,met;

		do{
			printf("Menu:\n\n1.Insert \n2.Search\n3.Print All entries\n4.Delete\n5.Exit\n"); 	//to display menu
			scanf("%d",&opp);								//takes input from user and passes it to switch 
			switch(opp)
			{
				case 1:
					int key1;	
					printf("Enter Key:");
					scanf("%d",&key1);							//to insert an entry
					insert_bt(head,key1);
					printf("Entry Added\n");								
					break;
				case 2:		
					int val;
					printf("Enter key:");
					scanf("%d",&val);							//to search for an entry 
					req=search(head,val);
					break;
				case 3:											//to print the tree
					print(head);								//in form of setrs
					printf("\n");
					print_bt(head,0);							//in form of tree
					break;
				case 4:
					int key2;	
					printf("Enter Key:");						//key to be deleted
					scanf("%d",&key2);
					met=search(head,key2);						//to search the entry, returns 1 if found
					if(met==1)
					{
						delete_bt(head,key2);					//deletes the entry from btree
						printf("Entry Deleted!\n");
					}
					break;
				case 5:										//to exit from the program
					break;
				default :
					printf("Invalid Input\n");			
			}
		}while(opp!=5);	
		free_memory(head);
	return 0;
}
