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

void printArrayForward(int A[]) //運用疊代(iteration)的方式，將Array裡的數字順向輸出到螢幕。
{


	for (int i = 0; i < MAX; i++) 
	{
        cout << A[i] << " ";
    }


}

void printArrayBackward(int A[], int i) //運用遞迴(recursion)的方式，將陣列裡的數字反向輸出到螢幕。
{


    if(i >= 0)
	{
			cout << A[i] << " ";
			printArrayBackward(A ,i-1 );
	}


}

void printListForward(nodePtr ptr) //運用疊代(iteration)的方式，將List裡的數字順向輸出到螢幕。
{


	while (ptr != NULL)
	{
		cout << ptr->item << " ";
		ptr = ptr->next;
	}


}

void printListBackward(nodePtr ptr) //運用遞迴(recursion)的方式，將List裡的數字反向輸出到螢幕。
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