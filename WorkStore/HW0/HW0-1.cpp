#include "stdio.h"
#include "iostream"

using namespace std;

#define MAX 5

struct Node
{
	int item;
	Node *next;
};

typedef Node* nodePtr;

void free_list(nodePtr node)
{
	nodePtr current, temp;
	current = node;
	while(current != NULL) {
		temp = current;
		current = current->next;
		free(temp);
	}
}

Node *inputData(int num, nodePtr headPtr)
{
	nodePtr currentPtr = headPtr;

	nodePtr tmpPtr = (nodePtr) malloc(sizeof(Node)) ; 
	tmpPtr->item = num;
	tmpPtr->next = NULL;

	if(headPtr == NULL)
		return tmpPtr;
	else	
	{
		while ( currentPtr->next != NULL )
			currentPtr = currentPtr->next;

		currentPtr->next = tmpPtr;

		return headPtr;
	}
}

void printArrayForward(int A[]) //�B���|�N(iteration)���覡�A�NArray�̪��Ʀr���V��X��ù��C
{


	for (int i = 0; i < MAX; i++) 
	{
        cout << A[i] << " ";
    }


}

void printArrayBackward(int A[], int i) //�B�λ��j(recursion)���覡�A�N�}�C�̪��Ʀr�ϦV��X��ù��C
{


    if(i >= 0)
	{
			cout << A[i] << " ";
			printArrayBackward(A ,i-1 );
	}


}

void printListForward(nodePtr ptr) //�B���|�N(iteration)���覡�A�NList�̪��Ʀr���V��X��ù��C
{


	while (ptr != NULL)
	{
		cout << ptr->item << " ";
		ptr = ptr->next;
	}


}

void printListBackward(nodePtr ptr) //�B�λ��j(recursion)���覡�A�NList�̪��Ʀr�ϦV��X��ù��C
{


	if(ptr != NULL)
	{
		printListBackward(ptr->next);
		cout << ptr->item << " ";
	}
	


}




int main()
{
	int num;
	int A[MAX] = {0};
	nodePtr headPtr = NULL;

	printf("Input %d numbers: ", MAX);
	
	for ( int i=0; i<MAX; i++ ) {
		cin >> num;
		A[i] = num;
		headPtr = inputData( num, headPtr );
	}

	printf("\nArray Forward Iteratively:  ");
	printArrayForward(A);
    printf("\nArray Backward Recursively: ");
	printArrayBackward(A, MAX-1);
	printf("\nList Forward Iteratively:  ");
	printListForward(headPtr);
	printf("\nList Backward Recursively: ");
	printListBackward(headPtr);

	printf("\n");
	free_list(headPtr);
	system("PAUSE");
	return 0;
}