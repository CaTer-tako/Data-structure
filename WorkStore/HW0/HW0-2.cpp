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

void printListForward(nodePtr ptr)
{


	while (ptr != NULL)
	{
		cout << ptr->item << " ";
		ptr = ptr->next;
	}
	cout << endl;

}


Node *InputList(int num, nodePtr headPtr) //輸入功能：使用者每輸入一個整數，便將它按照由小到大的順序插入到Array中，然後將Array裡儲存的值一一display到螢幕上。注意：必須直接插入到定位，不可插入後再來排序。
{
	nodePtr currentPtr = headPtr;
	//cout << "success enter InputList\n" ;
	nodePtr tmpPtr = (nodePtr) malloc(sizeof(Node)) ; 
	tmpPtr->item = num;
	if(headPtr == NULL)
	{
		headPtr->next = NULL;
		return tmpPtr;
	}
	else if(num < headPtr->item)
	{
		tmpPtr->next = headPtr;
		return tmpPtr;
	}
	else	
	{
		while ( currentPtr->next != NULL && num > currentPtr->next->item) //當 下一個不為NULL且數字比當前位置大的話..
			currentPtr = currentPtr->next;
		
		//printf("now currentPtr = %d\t\ttmpPtr = %d\t\tnext currentPtr = %d\n\n",currentPtr->item,tmpPtr->item,currentPtr->next->item); //測試用
		 tmpPtr->next = currentPtr->next;
		// printf("[tmpPtr->next = %d]\n",currentPtr->next->next);
		 currentPtr->next = tmpPtr;
		// printf("[currentPtr->next = %d]\n",tmpPtr);
		// printf("[tmpPtr->next = %d]\n\n",tmpPtr->next);

		return headPtr;
	}
}

Node *DeleteList(int num, nodePtr headPtr) //刪除功能：使用者每輸入一個整數，便將Array中所有相同數字的節點刪除；若Array中無該數字，則不處理。最後將Array裡儲存的值一一display到螢幕上。
{

	nodePtr currentPtr = headPtr;
	//cout << "success enter DeleteList\n" ;
	nodePtr tmpPtr = (nodePtr) malloc(sizeof(Node)) ; 
	tmpPtr->item = num;
	if(headPtr == NULL)
	{
		return headPtr;
	}
	else if(num == headPtr->item)
	{
		while ( currentPtr->next != NULL && num == currentPtr->next->item )
			currentPtr = currentPtr->next;
		//printf("now currentPtr = %d,\t\twill return%d\n\n",currentPtr->item,currentPtr->next->item);
		return currentPtr->next;
	}
	else
	{
		nodePtr ptr = headPtr;
		while ( currentPtr->next != NULL && num != currentPtr->next->item )
			currentPtr = currentPtr->next;
		ptr = currentPtr;
		//printf("NoHead,now currentPtr = %d,\t\t to%d\n\n",currentPtr->item,currentPtr->next->item);
		while ( currentPtr->next != NULL && num == currentPtr->next->item )
			currentPtr = currentPtr->next;
		//printf("NoHead,now currentPtr = %d,\t\t to%d\n\n",currentPtr->item,currentPtr->next->item);
		ptr->next = currentPtr->next;
		//printf("NoHead,now currentPtr = %d,\t\t ptr = %d\n\n",currentPtr->item,ptr->item);
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
		cout << "Input or Delete?" ;
		cin >> IorD;
		
		cout << "Input an integer?";
		cin >> num;
		if(IorD == 'I' || IorD == 'i')
			headPtr = InputList(num ,headPtr);
		
		else if(IorD == 'D' || IorD == 'd')
			headPtr = DeleteList(num ,headPtr);
		else continue;
		printListForward(headPtr);
		
	}

	printf("\n");
	free_list(headPtr);
	system("PAUSE");
	return 0;
}