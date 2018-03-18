//RED Black tree with delete
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

struct node
{
    int id;                 //input id
    char colour;            //BLACK =b RED= r 
    struct node *left;      //node's left child
    struct node *right;     //node's right child
    struct node *parent;    //nde's parent  
};
struct node *head=NULL;
struct node *sentinel;

 void redblacktree()            //initialize sentinel and root node
{
        sentinel=(struct node*) malloc(sizeof(struct node));
        sentinel->right=NULL;
        sentinel->left=NULL;                    
        sentinel->parent=NULL;
        sentinel->colour='b';
        head=sentinel;
        sentinel->id=-11;
}

void left_rotate(struct node* x)    //used to maintain rbt properties in case of insertion CASE 2 & 3
{
    struct node* y;
    y=x->right;
    if(y->left!=sentinel)
    {
        y->left->parent=x;
        x->right=y->left;
    }
    else
       x->right=sentinel; 
    if(x->parent==sentinel)
        head=y;
    else
        y->parent=x->parent;
    if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;
    y->left=x;
    x->parent=y;
}

void right_rotate(struct node* x)   //used to maintain rbt properties in case of insertion CASE 2 & 3
{
    struct node* y;
    y=x->left;
    if(y->right!=sentinel)
    {
        y->right->parent=x;
        x->left=y->right;
    }
    else
       x->left=sentinel; 
    if(x->parent==sentinel)
        head=y;
    else
        y->parent=x->parent;
    if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;
    y->right=x;
    x->parent=y;
}

void rbtfixup(struct node* new_node)
{
    struct node* uncle;
    if(new_node==head)
    {
        new_node->colour='b';
        return;
    }
        while((new_node->parent!=sentinel)&&(new_node->parent->colour=='r'))    //if parent colour is red
        {
            if(new_node->parent==new_node->parent->parent->left)                //if parent is left child of grandparent
            {
                uncle=new_node->parent->parent->right;
                if((uncle->colour=='r'))                            //if uncle exist and uncle is red CASE 1
                {
                    new_node->parent->colour='b';
                    uncle->colour='b';
                    new_node->parent->parent->colour='r';
                    new_node=new_node->parent->parent;
                }   
                else                                            //if uncle does not exist or uncle is black
                {
                    if(new_node==new_node->parent->right) //CASE 2
                    {
                        new_node=new_node->parent;
                        left_rotate(new_node);
                    }                                    //CASE 3
                    new_node->parent->colour='b';
                    new_node->parent->parent->colour='r';
                    right_rotate(new_node->parent->parent);
                }
            }
            else    //if parent is right child of grandparent
            {
                uncle=new_node->parent->parent->left;
                if((uncle->colour=='r'))
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
    head->colour='b';   //colour of root is always black
}

struct node* search_i (int t)           //returns the node of key if found else returns sentinel
{   
    struct node* x=head;
    while(x != sentinel)                                            //traverse till sentinel node
    {
        if(x->id == t)                                                  // if it is x is data then return 
            {
                return x;
            }
        else if(x->id < t)                                              //if x<t then move right
            {   
                x=x->right;
            }
        else if(x->id > t)                                              //if x>t then move left
            {   
                x=x->left;
            } 
    }
    return sentinel;                                                   //if not found return sentinel
}

void insert()
{
    int n;
    
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    
    printf("Enter ID:");
    scanf("%d",&n);
    
    if(search_i(n)!=sentinel)
    {
        cout<<"Element Already Exists"<<endl;               //check for duplicacy in tree
        return;
    }
    new_node->id=n;
    new_node->colour='r';
    
    if(head==sentinel)                  //for adding the first element(root)
    {
        head=new_node;
        new_node->left=sentinel;
        new_node->right=sentinel;
        new_node->parent=sentinel;
    }
    else
    {
        struct node *temp=head,*prev=NULL;
        int p=0;
        while((temp!=sentinel))
            if((temp->id)>(new_node->id))   //if entry is less than node
                {
                    p=1;
                    prev=temp;
                    temp=temp->left;
                }
            else if((temp->id)<(new_node->id))  //if entry is greater than node
                {
                    p=2;
                    prev=temp;
                    temp=temp->right;
                }
        if(p==1)                        //adding element on the left subtree
        prev->left=new_node;
        else if(p==2)       
        prev->right=new_node;           //adding element on the right subtree
        new_node->parent=prev;
        new_node->left= sentinel ;
        new_node->right= sentinel ;
    }
    head->parent=sentinel;
    rbtfixup(new_node);     //to miantain red black tree properties
    printf("ID:%d Colour= %c\n\n",new_node->id,new_node->colour);
    printf("Entry added!\n\n");
}

void search()                       //to find the desired key
{
    int key;
    printf("Enter name:");
    scanf("%d",&key);
    
    struct node *temp=head;
    
    if(head==sentinel)                          //if tree empty
        printf("NotFound!\n");
    else
    {
        while(temp!=sentinel)                   //searching key if the tree is not empty
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
        if(temp==sentinel)                      //if element is not in tree
            printf("NotFound!\n");
    }
}

void print(struct node *temp)
{
    if(temp!=sentinel)
    {
        if(temp->left)
            print(temp->left);           //inorder printing of tree
        printf("%d     %c\n\n",temp->id,temp->colour);
        if(temp->right)
            print(temp->right);
    }
    else
        return;
}

void print_rbt(struct node *temp,int p)         //for printing the red black tree
{
        if(temp!=sentinel)
        {
            if(temp->right)
                print_rbt(temp->right,p+7);
            for(int i=0;i<p;i++)
                printf(" ");                                //inorder printing in form of tree
            printf("%d %c\n\n",temp->id,temp->colour);
            if(temp->left)
                print_rbt(temp->left,p+7);
        }
        else
            return;
}

void free_memory(struct node* temp)         //to free the allocated memory
{
    if(temp!=sentinel)      //post order of freeing memory 
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

void transplant( struct node *u, struct node *v)            //connects v to u's parent         
{
    if(u->parent==sentinel) 
        head=v;                                     
    else if(u==u->parent->left)
        u->parent->left=v;                          
    else    
        u->parent->right=v;
    v->parent=u->parent;
}

struct node* minimum(struct node *z)             //returns the smallest successor of z
{
    while(z->left!=sentinel)                               
        z=z->left;
    return z;
}

void deletefixup(struct node *x)
{
        while(x->parent!=sentinel && x->colour=='b')                        //till x is not a root and x has colour black
        {   
            if(x==x->parent->left)                                                      
            {
                struct node *sibling;
                sibling=x->parent->right;
                if(sibling->colour=='r')                                    //Case 1: If x's sibling is red
                {   
                    sibling->colour='b';
                    x->parent->colour='r';                                  //make sibling's black parent red and left rotate about x's parent
                    left_rotate(x->parent);
                    sibling=x->parent->right;
                }
                if(sibling->left->colour=='b' && sibling->right->colour=='b')
                {   
                    sibling->colour='r';                                    //Case 2: if sibling is black and both siblings children are also black
                    x=x->parent;                                            //make that sibling red and take it above to parent 
                }
                else 
                {
                   if(sibling->right->colour=='b')
                    {
                        sibling->left->colour='b';                          //Case 3: if siblings left child is red and right is black 
                        sibling->colour='r';                                    //right rotate about siblings and make sibling asred and siblings left as black
                        right_rotate(sibling);
                        sibling=x->parent->right;
                    }   

                    sibling->colour=x->parent->colour;                      //Case 4:if both child are red
                    x->parent->colour='b';
                    sibling->right->colour='b';                         //Left Rotate about parent and make parent color black and siblings also black
                    left_rotate(x->parent);
                    x=head;
                }
            }
            else                                                                //Same as above and swap left with right
            {   
                struct node *sibling;
                sibling=x->parent->left;
                if(sibling->colour=='r')
                {   
                    sibling->colour='b';
                    x->parent->colour='r';
                    right_rotate(x->parent);
                    sibling=x->parent->left;
                
                }    
                if(sibling->left->colour=='b' && sibling->right->colour=='b')
                {   
                    sibling->colour='r';
                    x=x->parent;
                }
                else 
                {    if(sibling->left->colour=='b')
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
    x->colour='b';                      // In the end x reaches root and make sure root is black
}
void delete_rbt(int t)                  //for deleting the key t from the rb tree
{
    struct node *z;                     //z is the node with value t
    struct node *x;                     //x is z's child,which we'll replace it after deleting z
    struct node *y;

    if(search_i (t)==sentinel)                                      //Search if element is found
    {
        cout<<"Element Not Found"<<endl;
        return;
    }
    if(head==sentinel)                                              //Check if tree is empty or not
    {
        cout<<"Tree empty";
        return;
    }   

    z=search_i (t);                                                 //search for the key to be deleted
    y=z;                                                            //store this location in a temporary variable y

    char yorg;                                                      // to note color of deleted/replaced node
    yorg=y->colour;

    if(z->left==sentinel && z->right==sentinel)                     //if both left child and right child are sentinel
    {   
        x=sentinel;
        transplant(z,sentinel);                                     //connects senitel to z's parent 
        x->parent=z->parent;
        free(z);                                                    //free the node with key t
    }
    else if(z->left==sentinel && z->right!=sentinel)                // if right child is not NULL then connect right child
    {
        x=z->right;
        transplant(z,z->right);
        z=sentinel;
        x->right=sentinel;
        free(z);
    }
    else if(z->right==sentinel && z->left!=sentinel)                // if right child is not NULL then connect right child
    { 
        x=z->left;                                                  
        transplant(z,z->left);
        z=sentinel;
        x->left=sentinel;
        free(z);  
    }
    else                        // now if z has two child node
    {
        y=minimum(z->right);                                  // get minimum (successor)
        yorg=y->colour;                                       // get original color of the node with which z is swapped
        
        x=y->right;
        x->parent=y->parent;
        if(z->right!=y)
            y->parent->left=x;
        else                                                 //perform all the required linkages to delete and connect with all childrens and parents   
            y->parent->right=x;
        
        if(y->parent==z)  
            x->parent=y;
        else
        {   
            y->right=z->right;
            y->right->parent=y;
        }      
        transplant(z,y);
        y->left=z->left;
        y->left->parent=y;
        y->colour=z->colour;
    }       
    if(yorg=='b')  
        deletefixup(x);                                 //a violation can only occur If y had a color black, call DeleteFixup
    head->parent=sentinel;      
}

int main()
{
    int opp,k;
    redblacktree();
        do{
            printf("Menu:\n\n1.Insert \n2.Search\n3.Print All entries\n4.Delete\n5.Free memory\n6.Exit\n");     //to display menu
            scanf("%d",&opp);   //takes input from user and passes it to switch 
            switch(opp)
            {
                case 1:                             //to insert an entry
                    insert();                               
                    break;
                case 2:                             //to search for an entry 
                    search();
                    break;
                case 3:
                    printf("ID   Colours\n\n");     //to print all entries
                    print(head);
                    print_rbt(head,0);
                    break;
                case 4:                             
                    printf("Enter key:");
                    scanf("%d",&k);
                    delete_rbt(k);                  //to delete the key k from rbt
                    printf("deleted!\n");
                    break;
                case 5:                             //to free all the allocated memory
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