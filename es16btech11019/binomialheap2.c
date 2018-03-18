//Binomial Working one merge faulty
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
	int key,deg;				//key= value stored, deg= degree of node
	struct node *sib;			//sibling of node	
	struct node *p;				//parent of node
	struct node *son;			//child of the node
};

struct node* make_binomialheap(int n)	//to allocate memory to each node
{
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	new_node->p=NULL;			//initialising parent
	new_node->son=NULL;			//initialising child
	new_node->sib=NULL;			//initialising sibling
	new_node->deg=0;			//initialising degree
	new_node->key=n;			//initialising value

	return new_node;
}

struct node* h=NULL;			//main binomial heap
struct node* hr=NULL;			//temporary heap used in delete

void revert(struct node* y)		//utility fuc=nction used to reverse the link list in deletemin operation
{
	if(y!=NULL)
	{
		struct node *temp,*sib1,*prev;
		sib1=y->sib;
		y->sib=NULL;
		prev=y;
		while(sib1!=NULL)
		{
			temp=sib1->sib;
			sib1->sib=prev;
			prev=sib1;
			sib1=temp;	
		}
		hr=prev;
	}
}

void return_min()			//returns the minimum vale in the binomial heap
{
	int min=9999;
	struct node* h1=h;
	if (h1==NULL)
	{
		/* code */
		printf("Heap Empty\n");
		return;
	}
	while(h1!=NULL)
	{
		if(h1->key<min)
		{
			min=h1->key;
		}
		h1=h1->sib;
	}

	printf("Minimum: %d\n",min);
}

/*void print_biheap()
{
	struct node *t,*prev,*s,*u;
    t = h;
    while (t != NULL)
    {	
    	printf("Root\n");
        for (int i = 0; i<t->deg-1; ++i)
        	printf("    ");
        printf("%d\n", t->key);
        u=t->son;
        while(u!=NULL)
        {
        	prev=u;
        	s=u;
        	while(s!=NULL)
        	{
        		printf("%2d  ",s->key );
        		s=s->sib;
        	}
        	printf("\n");
        	u=prev->son;
        }	
        t = t->sib;
    	printf("\n");
    }
}*/

void print()		//prints the heads of all the heaps in binomial heap
{
	struct node* t;
    if (h == NULL)
    {
        printf("Heap Empty!\n");
        return;
    }
    printf("\nThe root nodes:-\n");
    t = h;
    while (t != NULL)
    {
        printf("%d(%d)", t->key,t->deg);
	    if (t->sib!= NULL)
            printf("---");
        t = t->sib;
    }
    printf("\n");
}

struct node* heap_merge(struct node* h,struct node* h1)		//utitlity operation to merge to heap used in heap union
{
	struct node* temp=NULL;
	struct node* t1;
    struct node* t2;
	struct node* a;
	struct node* b;
	t1=h;
    t2=h1;

    if (t1!=NULL)				
    {
        if (t2!=NULL&&t1->deg<=t2->deg)
            temp=t1;
        else if (t2!=NULL&&t1->deg>t2->deg)
            temp=t2;
        else
            temp=t1;
    }
    else
        temp=t2;
    while (t1!=NULL&&t2!=NULL)
    {
        if (t1->deg<t2->deg)
            t1=t1->sib;
        else if (t1->deg==t2->deg) 
        {
            a=t1->sib;
            t1->sib= t2;
            t1=a;
        }
        else 
        {
            b=t2->sib;
            t2->sib=t1;
            t2=b;
        }
    }
    return temp;
}

struct node* heap_union(struct node* h,struct node* h1)		//combines to heap into one use=ing merge function
{
	struct node* prev_x;
    struct node* next_x;
    struct node* x;
	h=heap_merge(h,h1);
	printf("Merged\n");

	if(h==NULL)
		return h;
	prev_x=NULL;
	x=h;
	next_x=x->sib;
	    while (next_x != NULL)
	    {
			if ((x->deg!= next_x->deg)||((next_x->sib != NULL)&& (next_x->sib)->deg==x->deg)) 
			{
	            prev_x = x;
	            x = next_x;
	        }
	        else 
	        {
	            if (x->key <= next_x->key)
	            {
	                x->sib= next_x->sib;
	                next_x->p=x;
					next_x->sib=x->son;
					x->son=next_x ;
					x->deg=x->deg+1;
	            }
	            else 
	            {
	                if (prev_x == NULL)
	                    h= next_x;
	                else
	                    prev_x->sib= next_x;
	                x->p=next_x;
					x->sib=next_x->son;
					next_x->son=x ;
					next_x->deg=next_x->deg+1;

	                x = next_x;
	            }
        	}
        	next_x = x->sib;
    	}
    return h;
}

void insert()			//inserts key into binomial heap using union function
{
	int n;
	printf("Key: ");
	scanf("%d",&n);
	struct node* h1=NULL;
	h1=make_binomialheap(n);
	h=heap_union(h,h1);
	printf("added\n");
}

void deletekey()		//delete the minimum value in binomial heap		
{
	struct node* temp;
	struct node* h1=h;
	struct node* prev;
	struct node* x;
	struct node* next;
	int min=9999,flag=0;

	if (h==NULL)
	{
		/* code */
		printf("Heap Empty\n");
		return;
	}
	while(h1!=NULL)
	{
		if(h1->key<min)
		{
			min=h1->key;
		}
		h1=h1->sib;
	}
	prev=NULL;
	x=h;
	next=x->sib;
	while(next!=NULL)
	{
		if(x->key==min)
		{
			printf("Found\n");
			flag=1;
			break;
		}
		prev=x;
		x=next;
		if(next->sib!=NULL)
				next=next->sib;
		else
			next=NULL;	
		
	}
	if(x->key==min&&flag!=1)
	{
		printf("Found\n");
		flag=1;
		next=NULL;
	}
	if(next==NULL&&flag!=1)
	{
		printf("Not Found\n");
		return;
	}
	if(prev==NULL)
	{
		h=next;
		//printf("ttt%d\n",next->key);
		if(x->son!=NULL)
		{
			temp=x->son;
			revert(temp);		
			h=heap_union(h,hr);
		}
	}
	else
	{
		prev->sib=next;
		if(x->son!=NULL)
		{
			temp=x->son;
			revert(temp);		
			h=heap_union(hr,h);
		}	
	}
	free(x);
	printf("Deleted\n");
}

int main()
{
	int opp;
	
		do{
			printf("\nMenu:\n\n1.Insert \n2.Return Minimum\n3.Delete Minimum\n4.Print All roots\n5.Exit\n"); 	//to display menu
			scanf("%d",&opp);					//takes input from user and passes it to switch 
			switch(opp)
			{
				case 1:							//to insert an entry
					insert();								
					break;
				case 2:							//to search for minimum entry 
					return_min();
					break;
				case 3:							//to delete minimum entry
					deletekey();
					break;
				case 4:							//to print all entries
					print();
					//print_biheap();
					break;
				case 5:
					break;
				default :
					printf("Invalid Input\n");			
			}
		}while(opp!=5); 

	return 0;
}