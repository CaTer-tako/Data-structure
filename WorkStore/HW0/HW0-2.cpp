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


Node *InputList(int num, nodePtr headPtr) //��J�\��G�ϥΪ̨C��J�@�Ӿ�ơA�K�N�����ӥѤp��j�����Ǵ��J��Array���A�M��NArray���x�s���Ȥ@�@display��ù��W�C�`�N�G�����������J��w��A���i���J��A�ӱƧǡC
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
		while ( currentPtr->next != NULL && num > currentPtr->next->item) //�� �U�@�Ӥ���NULL�B�Ʀr���e��m�j����..
			currentPtr = currentPtr->next;
		
		//printf("now currentPtr = %d\t\ttmpPtr = %d\t\tnext currentPtr = %d\n\n",currentPtr->item,tmpPtr->item,currentPtr->next->item); //���ե�
		 tmpPtr->next = currentPtr->next;
		// printf("[tmpPtr->next = %d]\n",currentPtr->next->next);
		 currentPtr->next = tmpPtr;
		// printf("[currentPtr->next = %d]\n",tmpPtr);
		// printf("[tmpPtr->next = %d]\n\n",tmpPtr->next);

		return headPtr;
	}
}

Node *DeleteList(int num, nodePtr headPtr) //�R���\��G�ϥΪ̨C��J�@�Ӿ�ơA�K�NArray���Ҧ��ۦP�Ʀr���`�I�R���F�YArray���L�ӼƦr�A�h���B�z�C�̫�NArray���x�s���Ȥ@�@display��ù��W�C
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