#define MAXSIZE 20
#include <iostream>
#include <string>

using namespace std;
struct  list {
  int nodeInfo;
  list *next;
} ;
struct  queue {
  int nodeInfo;
  queue *next;
  queue * Front;
  queue * Rear;
} ;
struct Stack {
    int Stack_array [MAXSIZE];
    int Top;
};
struct Heap {
	int Heap_array[MAXSIZE];
	int count;
};

struct tree {
	int info;
	tree * left;
	tree * right;
};
class Cheap
{
	public:
	Heap * myheap;
	bool empty(Heap * myheap); 
	bool full(Heap * myheap) ;
	void insert(int a, Heap *  myheap);
	int serve(Heap *  myheap);
private:
	void bubble(int l, Heap * &myheap);
	void swap(int r, int s, Heap * &myheap);
	void trickle(int k, int l, Heap * &myheap);
	
};
bool Cheap::full(Heap * myheap)
{
	if(myheap->count >= MAXSIZE) return 1;
	return 0;
}
bool Cheap::empty(Heap * myheap)
{
	if (myheap->count == 0) return 1;
	return 0;
}
void Cheap::trickle(int k, int l, Heap * &myheap)
{
	int i,temp;
	int x,y,z;
	i = k;
	x = myheap->Heap_array[i];
	temp = l/2;
	while ( i <= (l/2))
	{ //begin
		if ((2*i) == l) 
		{ //begin
			y = myheap->Heap_array[l];
			if (y > x)
			{ //begin
				swap(i,2*i,myheap);
				i = l;
			} //end
		} //end
		else
		{ //begin
			y = myheap->Heap_array[2*i];
			z = myheap->Heap_array[2*i+1];
			if ((x <= y) && (y>z))
			{ //begin
				swap(i,2*i,myheap);
				i = 2*i;
			} //end
			else
				if ((x <= y) && (y<z))
				{ //begin
					swap(i,2*i+1,myheap);
					i = 2*i+1;
				} //end
			else i = l;
		}
	}
}


int Cheap::serve(Heap * myheap)
{
	int a;
	if (empty(myheap))
		printf ("heap empty \n");
	else
	{
		a =  myheap->Heap_array[0];
		swap(0,myheap->count-1,myheap);
		if (myheap->count ==1)
			myheap->count = 0;
		else
		{
			myheap->count= myheap->count-1;
			trickle(0,myheap->count,myheap);
		}
	}
	return a;
}
void Cheap::insert(int a, Heap * myheap)
{
	int k;
	if (full(myheap))
		printf("Take action heap full\n");
	else
	{
		k = myheap->count;
		myheap->Heap_array[k] = a;
		bubble(k,myheap);
		myheap->count++;
	}
}

void Cheap::bubble(int l, Heap * &myheap)
{
  int i,j,x,y;
  i = l;
  j=(l/2);
  x = myheap->Heap_array[i];
  y = myheap->Heap_array[j];
  if ((j != -1 ) && (y < x))
  {
	  swap(i,j,myheap);
	  bubble(l/2,myheap);
  }
//  printf("in bubble count = %d\n",myheap->count);
}
void Cheap::swap(int r, int s,  Heap * &myheap)
{
	int temp;
	temp = myheap->Heap_array[r];
	myheap->Heap_array[r]=myheap->Heap_array[s];
	myheap->Heap_array[s]=temp;
}
class Cstack
{
public:
	int N;
	Cstack(){ N=MAXSIZE;}
	~Cstack();
	Stack * stack;	
	list * stacklist;
	bool empty(list * stack);
	bool emptyA(Stack * stack);
	bool full(list * stack);
	bool fullA(Stack * stack);
	int  pop(list * &stack);
	int  popA(Stack * &stack);
	void push(int a, list * &stack);
	void pushA(int a, Stack * &stack);
private:
};
bool Cstack::empty(list * stack)
{
    if (stack)
    {
        return false;
    }
    else
        return true;
}
bool Cstack::full(list * stack)
{
    return false;
}
void Cstack::push(int a, list * &stack)
{
    list * q;
    if (full(stack))
    {
        printf("Something very wrong ... no more system heap\n");
    }
    else
    {
        q = new(list);
        q->nodeInfo = a;
        q->next = stack;
    }
    stack = q;
}
int Cstack::pop(list * &stack)
{
    int top;
    list * q;
    if (empty(stack))
    {
        printf("Nothing on stack\n");
        return -1;
    }
    else
    {
        top = stack->nodeInfo;
        q = stack;
        stack = stack->next;
        delete(q);
        return top;
    }
}
void Cstack::pushA(int a, Stack * &stack)
{
    if (fullA(stack))
        printf("Stack full\n");
    else
    {
        stack->Top = ++stack->Top;
        stack->Stack_array[stack->Top] = a;
    }   
}
int Cstack::popA(Stack * &stack)
{
    int retval;
    if (emptyA(stack))
    {
        printf("Stack empty\n");
        return -1;
    }
    else
    {       
        retval = stack->Stack_array[stack->Top];
        stack->Top--;
    }   
    return retval;
}
bool Cstack::emptyA(Stack * stack)
{
    if (stack)
        return (stack->Top == 0);
    else
        return true;
}
bool Cstack::fullA(Stack * stack)
{
    if (stack)
        return (stack->Top == N-1);
    else
        return false;
}

class Cqueue
{
public:
	Cqueue();
	~Cqueue();
	queue * qpublic;
	void enque(int a, queue * Q);
	bool fullq(queue * queue);
	bool emptyq(queue * queue);
	int serve(queue * Q);

	private:
};

Cqueue::Cqueue()
{
}

Cqueue::~Cqueue()
{
}
void Cqueue::enque(int a, queue * Q)
{
	queue * p;
	if (fullq(Q))
		printf("****queue full something wrong****\n");
	else
	{
		p = new(queue);
		p->nodeInfo = a;
		p->next = NULL;
		if (Q->Rear == NULL)
			Q->Front = p;
		else
			Q->Rear->next = p;
		Q->Rear = p;
	}

}
bool Cqueue::fullq(queue * queue)
{
	return false;
}
bool Cqueue::emptyq(queue * queue)
{
	if (queue->Front==NULL && queue->Rear==NULL)
    {
        return true;
    }
    else
        return false;
}
int Cqueue::serve(queue * Q)
{
	int info;
	queue * p;
	if (emptyq(Q))
	{
		printf("The queue is empty!\n");
	}
	else
	{

		p = Q->Front;
		info = p->nodeInfo;
		Q->Front = Q->Front->next;
		if (Q->Front == NULL)
			Q->Rear = NULL;
		delete(p);	
		return info;
	}
	return 0;
}

//list * head;
class Clist {
public:
      list * head;
	  void insert_after(int a, list* reflist);
	  void insert_at_head(int a, list * &reflist);
	  void delete_after(list * reflist);
      void delete_at_head(list * &reflist);
      
private:
      
};
void Clist::insert_after(int a, list * reflist)
{
    list * q;
    if (reflist)
    {
        q = new(list);
        q->nodeInfo = a;
        q->next = reflist->next;
        reflist->next = q;
    }
    return;
}
void Clist::insert_at_head(int a, list * &reflist)
{
    list * q;
    q = new(list);
    q->nodeInfo = a;
    q->next = reflist;
    reflist = q;
}
void Clist::delete_after(list * reflist)
{
    list * q;
    if ((reflist) && (reflist->next))
    {
        q = reflist->next;
        reflist->next = q->next;
        delete(q);
    }
}
void Clist::delete_at_head(list * &reflist)
{
    list * q;
    if (reflist)
    {
        q = reflist;
        reflist = q->next;
        delete(q);
    }
}
class  Ctree
{
public:
	Ctree();
	~Ctree();
	tree * treelist;
	void tree_insert(int info, tree * &tree_list);
    void preorder(tree * &tree_list);
	void process(int info);
	void deltreenode(int info, tree * &tree_list);
	void inOrder(tree * &tree_list);
	void postOrder (tree * &tree_list);
private:

};

Ctree::Ctree()
{

}

Ctree::~Ctree()
{
}
void Ctree::tree_insert(int info, tree * &tree_list)
{
	tree * p;
	if (tree_list == NULL)
	{
		p = new(tree);
		p->info = info;
		p->left = NULL;
		p->right = NULL;
		tree_list = p;
	}
	else
	{
		if (info < tree_list->info)
			tree_insert(info, tree_list->left);
		else
			if (info > tree_list->info)
					tree_insert(info,tree_list->right);
			else
				printf("Node info %d is already present\n",info);

	}

}
void Ctree::preorder(tree * &tree_list)
{
	if (tree_list != NULL)
	{
		process(tree_list->info);
		preorder(tree_list->left);
		preorder(tree_list->right);
	}
}
void Ctree::process(int info)
{
	printf("info = %d\n",info);
}
void Ctree::deltreenode(int info, tree * &tree_list)
{
	tree * q;
	tree * p;
	if (tree_list == NULL)
		printf("%d is not present\n",info);
	else
		if (info < tree_list->info)
			deltreenode(info,tree_list->left);
		else 
			if (info > tree_list->info)
				deltreenode(info,tree_list->right);
			else
				if (info == tree_list->info)
				{
					q = tree_list;
					if (q->right == NULL)
						tree_list = q->left;
					else
						if (q->left == NULL)
							tree_list = q->right;
						else
						{
							p = q->right;
							while(p->left != NULL)
							{
								p = p->left;
								tree_list = p;
								tree_list->left = q->left;
								p = p->right;
							}
						}

				}
}
void Ctree::inOrder(tree * &tree_list)
{
	if (tree_list != NULL)
	{
		inOrder(tree_list->left);
		process(tree_list->info);
		inOrder(tree_list->right);
	}

}
void Ctree::postOrder (tree * &tree_list)
{
  if(tree_list == NULL) return;
  postOrder( tree_list->left);
  postOrder( tree_list->right); 
  process(tree_list->info);

}
