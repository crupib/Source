// LinkList.cpp : Data structure basics.
//

#include "stdafx.h"
#include "linklist.h"
void run_queue_test();
void run_tree_test();
void run_stack_test();
void run_list_test();
void run_heap_test();


int _tmain(int argc, _TCHAR* argv[])
{
	printf("Running queue tests!\n");
	run_queue_test();
	printf("\n\n\n\n");
	printf("Running tree tests!\n");
	run_tree_test();
	printf("\n\n\n\n");
	printf("Running stack tests!\n");
	run_stack_test();
	printf("\n\n\n\n");
	printf("Running list tests!\n");
	run_list_test();  
	printf("\n\n\n\n");
	printf("Running heap tests!\n");
	run_heap_test();  
	printf("\n\n\n\n");

    return 0;
}
void run_heap_test()
{
	Cheap * myheap;
	myheap = NULL;   
    myheap = new(Cheap);
	myheap->myheap = new(Heap);

	myheap->myheap->count = 0;
	if (!myheap->empty(myheap->myheap))
		printf("heap empty\n");
	myheap->insert(70,myheap->myheap);
	myheap->insert(42,myheap->myheap);
	myheap->insert(60,myheap->myheap);
	myheap->insert(17,myheap->myheap);
	myheap->insert(10,myheap->myheap);
	myheap->insert(72,myheap->myheap);
	myheap->insert(96,myheap->myheap);
	myheap->insert(90,myheap->myheap);
	myheap->insert(80,myheap->myheap);
	myheap->insert(75,myheap->myheap);
	myheap->insert(44,myheap->myheap);
	myheap->insert(14,myheap->myheap);
	printf("Heap output before serve\n");
	for (int i = 0; i < myheap->myheap->count; i++)
		printf("%d ",myheap->myheap->Heap_array[i]);	
	printf("\n");
	int heapserv = 0;
	heapserv = myheap->serve(myheap->myheap);
	printf("Heap output after serve\n");
	for (int i = 0; i < myheap->myheap->count; i++)
		printf("%d ",myheap->myheap->Heap_array[i]);
}
void run_queue_test()
{
	Cqueue  myqueue;
	int qserve;
	myqueue.qpublic = new(queue);
	myqueue.qpublic->Front = NULL;
	myqueue.qpublic->Rear = NULL;
	if (myqueue.emptyq(myqueue.qpublic))
		printf("The queue is empty!\n");
	else printf("The queue has elements");
	printf("New queue elements added\n");
	myqueue.enque(5,myqueue.qpublic);
	myqueue.enque(6,myqueue.qpublic);
	myqueue.enque(7,myqueue.qpublic);
	if (qserve=myqueue.serve(myqueue.qpublic))
		printf("You have been served : %d\n",qserve);
	if (qserve=myqueue.serve(myqueue.qpublic))
		printf("You have been served : %d\n",qserve);
	if (qserve=myqueue.serve(myqueue.qpublic))
		printf("You have been served : %d\n",qserve);
	if (qserve=myqueue.serve(myqueue.qpublic))
		printf("You have been served : %d\n",qserve);
}
void run_tree_test()
{
	Ctree mytree;

	mytree.treelist = NULL;
	mytree.tree_insert(8,mytree.treelist);
	mytree.tree_insert(3,mytree.treelist);
	mytree.tree_insert(9,mytree.treelist);
	mytree.tree_insert(28,mytree.treelist);
	mytree.tree_insert(13,mytree.treelist);
	mytree.tree_insert(7,mytree.treelist);
	mytree.tree_insert(10,mytree.treelist);
	mytree.tree_insert(5,mytree.treelist);
	mytree.tree_insert(7,mytree.treelist);
	mytree.tree_insert(2,mytree.treelist);
	printf("preorder\n");
	mytree.preorder(mytree.treelist);
	printf("Inorder\n");
	mytree.inOrder(mytree.treelist);
	printf("postorder\n");
	mytree.postOrder(mytree.treelist);
	mytree.deltreenode(28,mytree.treelist);
	printf("After Tree delete\n");
	mytree.preorder(mytree.treelist);
}
void run_stack_test()
{
	Cstack * mystack;
	int i = 0;
	mystack = NULL;   
    mystack = new(Cstack);
	mystack->stack = new(Stack);
	mystack->stack->Top = 0;
    mystack->stack->Stack_array[0] = -1;
	printf("Push stack\n");
	mystack->pushA(1,mystack->stack);
    mystack->pushA(2,mystack->stack);
    mystack->pushA(3,mystack->stack);
    mystack->pushA(4,mystack->stack);
    for (i = 0; i < 5; i++)
    {
		printf("popped = %d\n",mystack->popA(mystack->stack));
    }

	mystack->stacklist = NULL;
	if (mystack->empty(mystack->stacklist))
        printf("Stack has been emptied\n");
    else
        printf("Stack was empty\n");
	printf("Stack pushed\n");
	mystack->push(-1,mystack->stacklist);
    printf("node %2d; address %x ;next address %x\n",mystack->stacklist->nodeInfo,mystack->stacklist,mystack->stacklist->next);

    mystack->push(1,mystack->stacklist);
    printf("node %2d; address %x ;next address %x\n",mystack->stacklist->nodeInfo,mystack->stacklist,mystack->stacklist->next);
    mystack->push(2,mystack->stacklist);
    printf("node %2d; address %x ;next address %x\n",mystack->stacklist->nodeInfo,mystack->stacklist,mystack->stacklist->next);
    mystack->push(3,mystack->stacklist);
    printf("node %2d; address %x ;next address %x\n",mystack->stacklist->nodeInfo,mystack->stacklist,mystack->stacklist->next);
    i = mystack->pop(mystack->stacklist);
    printf(" pop %d\n",i);
    printf("node %2d; address %x ;next address %x\n",mystack->stacklist->nodeInfo,mystack->stacklist,mystack->stacklist->next);
    i = mystack->pop(mystack->stacklist);
    printf(" pop %d\n",i);
    printf("node %2d; address %x ;next address %x\n",mystack->stacklist->nodeInfo,mystack->stacklist,mystack->stacklist->next);
    i = mystack->pop(mystack->stacklist);
    printf(" pop %d\n",i);
    printf("node %2d; address %x ;next address %x\n",mystack->stacklist->nodeInfo,mystack->stacklist,mystack->stacklist->next);
    i = mystack->pop(mystack->stacklist);
    printf(" pop %d\n",i);
    if (mystack->empty(mystack->stacklist))
        printf("Stack empty\n");
    else
        printf("node %2d; address %x ;next address %x\n",mystack->stacklist->nodeInfo,mystack->stacklist,mystack->stacklist->next); 

}
void run_list_test()
{
	 int i;
    list * looper;
  	Clist mylist;
	mylist.head = NULL;
	printf("new class list \n");
	mylist.head = new(list);
    mylist.head->nodeInfo = -1;
    mylist.head->next = NULL;
    for (i = 1; i < 10;i++)
        mylist.insert_after(i,mylist.head);
  
    for (i = 1; i < 10;i++)
        mylist.insert_at_head(i,mylist.head);
   
    looper = mylist.head;

    for (i = 0; i < 10; i++)
    {
        printf("node %2d; address %x ;next address %x\n",looper->nodeInfo,looper,looper->next);
        looper=looper->next;
    }
   
    for (i = 1; i < 10;i++)
        mylist.delete_after(mylist.head);

    for (i = 1; i < 10;i++)
        mylist.delete_at_head(mylist.head);


    looper = mylist.head;
	printf("after delete class list \n");
    if (looper->next)
    {
        for (i = 0; i < 10; i++)
        {
            printf("node %d\n",looper->nodeInfo);
            looper=looper->next;
        }
    }

}