//Binomial Working one
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

void revert(struct node* t)		//utility fuc=nction used to reverse the link list in deletemin operation
{
	if(t!=NULL)	 	//if the passed heap is not empty
	{
		struct node *temp,*sib1,*prev;		//prev is the reversed binomial heap, sib1 and temp are used for temporary changes
		sib1=t->sib;	//we temporarily store sib of first node
		t->sib=NULL;	//new sib of first node should be null now
		prev=t;			//current head of new binomial heap is t
		while(sib1!=NULL)		//till we reach the end of binomial heap
		{
			temp=sib1->sib;		//we temporarily store sib of node
			sib1->sib=prev;		//new sib of this node should be prev now
			prev=sib1;			//prev now points to this node
			sib1=temp;			
		}
		hr=prev;				//final reversed binomial heap
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
	while(h1!=NULL)			//till we reach end pf binomial heap node list
	{
		if(h1->key<min)		//if vale is less than minimum, update minimum
		{
			min=h1->key;
		}
		h1=h1->sib;
	}

	printf("Minimum: %d\n",min);	//return the minimum
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

struct node* heap_merge(struct node* x,struct node* y)//merge two binomial heap and return the combination
{
	struct node *a,*b;
	struct node* temp=NULL;
	struct node* z=NULL;
	a=x;
	b=y;
	while(a!=NULL && b!=NULL)	//performing merge operation similar to what we do in merge sort
	{
		if(a->deg > b->deg)		//comparing the degree of the two binomial heap
		{
			if(temp==NULL)		//if final binomial heap is empty
			{
				temp=b;
				z=temp;			
				b=b->sib;
			}
			else				//if heap is not empty and deg of b is less than a, we add currently pointed node of b to z
			{
				z->sib=b;
				z=b;
				b=b->sib;
			}
		}
		else
		{
			if(temp==NULL)		//if the final binomial heap is empty
			{
				temp=a;
				z=temp;
				a=a->sib;
			}
			else				//if heap is not empty and deg of a is less or equal to b, we add currently pointed node of a to z
			{
				z->sib=a;
				z=a;
				a=a->sib;
			}
		}
	}
	if(b==NULL)				//if we reach till end of b, we add all the remaining nodes of a to final binomal heap
	{
		while(a!=NULL)
		{
			if(temp==NULL)
			{
				temp=a;
				z=temp;
				a=a->sib;
			}
			else
			{
				z->sib=a;
				z=a;
				a=a->sib;
			}
			
		}
	}
	if(a==NULL)				//if we reach till end of a, we add all the remaining nodes of b to final binomal heap
	{
		while(b!=NULL)
		{
			if(temp==NULL)
			{
				temp=b;
				z=temp;
				b=b->sib;
			}
			else
			{
				z->sib=b;
				z=b;
				b=b->sib;
			}
		}
	}
	return temp;
}

struct node* heap_union(struct node* h,struct node* h1)		//combines two binomial heaps into one using merge function
{
	struct node* prev_x;
    struct node* next_x;
    struct node* x;
	h=heap_merge(h,h1);		//we first merge the two binomial heap into 1 in ascending order of degree
	printf("Merged\n");

	if(h==NULL)				//if heap is empty return
		return h;
	prev_x=NULL;			//prev_x points to node previous of x
	x=h;					//x points to node currently we are at
	next_x=x->sib;			//next_x points to node next of x

	while (next_x != NULL)	//till x reach last node
	{
		if ((x->deg!= next_x->deg)||((next_x->sib != NULL)&& (next_x->sib)->deg==x->deg)) 	//if we find a situation when x's degree is same as next_x's sibling's degree 
		{	printf("kkkk\n");																				//since the degree are in ascending order, this means degree of x and next_x is also smae 
	        prev_x = x;			//we leave alone the 1st node, and combine the other two same degree, and hence this step
	        x = next_x;
	     }
	    else 
	    {
	        if (x->key <= next_x->key)		//if x-value is less than nextxvalue, next_x becomes x'son
	        {	printf("nnnnn\n");
	            x->sib= next_x->sib;		//x now points to next_x sibling
	            next_x->p=x;				//next_x becomes x'x son
				next_x->sib=x->son;			//next_x sibling becomes x's old son
				x->son=next_x ;
				x->deg=x->deg+1;			//degree of x increases
	        }
	        else 							//if x-value is greater than next_xvalue, x becomes next_x'son
	        {
	        	printf("yyyyyy\n");
	            if (prev_x == NULL)			//if x is first node
	                h= next_x;
	            else
	                prev_x->sib= next_x;
	            x->p=next_x;				//x's parent is now next_x
				x->sib=next_x->son;			//x sibling becomes next_x's old son
				next_x->son=x ;				//x becomes next_x'x son
				next_x->deg=next_x->deg+1;
	            x = next_x;
	            }
        	}
        	printf("uuuuuu\n");
        	next_x = x->sib;			//move to next node
    	}
    return h;
}

void insert()			//inserts key into binomial heap using union function
{
	int n;
	printf("Key: ");
	scanf("%d",&n);
	struct node* h1=NULL;	
	h1=make_binomialheap(n);	//we make a temporary binomial heap with n as element
	h=heap_union(h,h1);			//now we call union to add this element in appropriate location in the original binomial heap
	printf("added\n");
}

void deletemin()		//delete the minimum value in binomial heap		
{
	struct node* temp;
	struct node* h1=h;
	struct node* prev;
	struct node* x;
	struct node* next;
	int min=9999,flag=0;

	if (h==NULL)						//if binomial heap is empty
	{	
		/* code */
		printf("Heap Empty\n");
		return;
	}
	while(h1!=NULL)						//to traverse to the minimum node
	{
		if(h1->key<min)
		{
			min=h1->key;
		}
		h1=h1->sib;
	}
	prev=NULL;
	x=h;							//x currently points to 1st node in main binomial heap
	next=x->sib;
	while(next!=NULL)				//we move untill we reach end of binomial heap, or break if we find the key(the minimum found above)
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
	if(x->key==min&&flag!=1)		//if we break even before entering, that is if there is only 1 node
	{
		printf("Found\n");
		flag=1;
		next=NULL;
	}
	if(next==NULL&&flag!=1)			//if we reach end of main binomial heap, and still not found minimum
	{
		printf("Not Found\n");
		return;
	}
	if(prev==NULL)							//if minimum is the first node itself
	{
		h=next;								//we delete x, and the new heap now points to x->sib	
		//printf("ttt%d\n",next->key);
		if(x->son!=NULL)					//we delete x, make x's children form a new heap and union it with main heap
		{
			temp=x->son;
			revert(temp);		
			h=heap_union(h,hr);
		}
	}
	else								//if minimum is not the 1st node of binomial heap
	{
		prev->sib=next;					//new sibling of prev is now next, since x is deleted 
		if(x->son!=NULL)				//we delete x, make x's children form a new heap and union it with main heap
		{
			temp=x->son;
			revert(temp);		
			h=heap_union(h,hr);
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
					deletemin();
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