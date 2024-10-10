#include "stdio.h"
#include "iostream"

using namespace std;

#define MAX 5

struct Node
{
	int item;
	Node* next;
};

typedef Node* nodePtr;

void free_list(nodePtr node)
{
	nodePtr current, temp;
	current = node;
	while (current != NULL) {
		temp = current;
		current = current->next;
		free(temp);
	}
}

void printListForward(nodePtr ptr)
{


	while (ptr != NULL)
	{
		cout << ptr->item << " ";
		ptr = ptr->next;
	}
	cout << endl;
}


Node* InputList(int num, nodePtr headPtr)
{
	nodePtr currentPtr = headPtr;
	nodePtr tmpPtr = (nodePtr)malloc(sizeof(Node));
	tmpPtr->item = num;
	tmpPtr->next = NULL;
	if (headPtr == NULL)
	{
		return tmpPtr;
	}
	else if (num < headPtr->item)
	{
		tmpPtr->next = headPtr;
		return tmpPtr;
	}
	else
	{
		while (currentPtr->next != NULL && num > currentPtr->next->item)
			currentPtr = currentPtr->next;
		tmpPtr->next = currentPtr->next;
		currentPtr->next = tmpPtr;

		return headPtr;
	}
}

Node* DeleteList(int num, nodePtr headPtr)
{

	nodePtr currentPtr = headPtr;
	nodePtr tmpPtr = (nodePtr)malloc(sizeof(Node));
	tmpPtr->item = num;
	tmpPtr->next = NULL;
	if (headPtr == NULL)
	{
		return headPtr;
	}
	else if (num == headPtr->item)
	{
		while (currentPtr->next != NULL && num == currentPtr->next->item)
			currentPtr = currentPtr->next;
		return currentPtr->next;
	}
	else
	{
		nodePtr ptr = headPtr;
		while (currentPtr->next != NULL && num != currentPtr->next->item)
			currentPtr = currentPtr->next;
		ptr = currentPtr;
		while (currentPtr->next != NULL && num == currentPtr->next->item)
			currentPtr = currentPtr->next;
		ptr->next = currentPtr->next;
	}

	return headPtr;
}



int main()
{
	int num;
	char IorD;
	nodePtr headPtr = NULL;
	while (1)
	{
		cout << "Input or Delete?";
		cin >> IorD;

		cout << "Input an integer?";
		cin >> num;
		if (IorD == 'I' || IorD == 'i')
			headPtr = InputList(num, headPtr);

		else if (IorD == 'D' || IorD == 'd')
			headPtr = DeleteList(num, headPtr);
		else continue;
		printListForward(headPtr);
	}


	printf("\n");

	system("PAUSE");
	return 0;
}
