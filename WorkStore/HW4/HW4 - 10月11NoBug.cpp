// HW4.cpp : 定義主控台應用程式的進入點。
//

#include <stdio.h>
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct{
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm *nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[]) 
{
	for ( int i = 0; i < MAX_TERMS; i++ ) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm *&polynomialTermPtr) 
{
	linkedPolynomialTerm *tmpPtr;

	while ( polynomialTermPtr != nullptr ) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo)
{
		if(coef == 0)
	{
		for(int i = 0; i < MAX_TERMS; i++)
		{
			if(terms[i].expo == expo)
			{
				terms[i].coef = 0,terms[i].expo = 0;
				for(int j = i; j <= MAX_TERMS; j++)
				{
					terms[j] = terms[j+1];
					if(terms[j].coef == 0)break;
				}
			}
		}
		return;
	}
	for(int i = 0; i < MAX_TERMS; i++)
	{
		if( terms[i].coef == 0)
		{
			terms[i].expo = expo,terms[i].coef = coef;
			break;
		}
		if(terms[i].expo == expo)
		{
			terms[i].expo = expo,terms[i].coef = coef;
			break;
		}
		else if(expo > terms[i].expo )
		{
			for(int j = MAX_TERMS-1; j >= i; j--)
				terms[j].expo = terms[j-1].expo,terms[j].coef = terms[j-1].coef;
			terms[i].expo = expo,terms[i].coef = coef;
			break;
		} 
	}


		return;

}

void inputLinkTerms(linkedPolynomialTerm *&polyPtr, int coef, int expo)
{
	linkedPolynomialTerm *tmpPtr;
	
	tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = coef;
	tmpPtr->expo = expo;
	tmpPtr->nextTermPtr = nullptr;
	if(coef == 0)
	{
		if(polyPtr == nullptr)return;
		if(polyPtr->expo == expo)
		{
			polyPtr = polyPtr->nextTermPtr;
		}
		else 
		{
			linkedPolynomialTerm *current = polyPtr;
			while(current->nextTermPtr != nullptr && expo != current->nextTermPtr->expo)
				current = current->nextTermPtr;
			if(current->nextTermPtr == nullptr && current->expo != expo)return; // 9 5 3 2 0  [3]
			if (current->nextTermPtr != nullptr)
			{
				if(current->nextTermPtr->nextTermPtr->coef != 0)
					current->nextTermPtr = current->nextTermPtr->nextTermPtr;
			}
		}
		return;
	}
	//if:poly內沒東西(尚未輸入)or"新的值的次方"比"頭的次方"大
	if(polyPtr == nullptr || tmpPtr->expo > polyPtr->expo) //接在"頭"的前面 
	{
		tmpPtr->nextTermPtr = polyPtr;
		polyPtr = tmpPtr;
	}
	else if(tmpPtr->expo == polyPtr->expo) //else if:"新的值的次方"等於"頭的次方"，就直接替換
	{
		tmpPtr->nextTermPtr = polyPtr->nextTermPtr;
		polyPtr = tmpPtr;
	}
	else 
	{
		linkedPolynomialTerm *prev = polyPtr;
		linkedPolynomialTerm *current = polyPtr;
		while(tmpPtr->expo < current->expo) //如果"現在位置幕次"比"輸入的幕次"大的話，就繼續往後找
		{//找到目標:5 3 1  [2]
			prev = current;
			current = current->nextTermPtr;
			if(!current)break;
		}//要是1.現在位置不存在 or 2.找到目標 才會停
		
		if(current == nullptr)//到尾巴了 就直接接在後面
			prev->nextTermPtr = tmpPtr;
		else if(current->expo == tmpPtr->expo) //兩者幕次相同的話，替換掉
		{
			tmpPtr->nextTermPtr = current->nextTermPtr;
			prev->nextTermPtr = tmpPtr;
		}
		else //現在的位置之幕次<輸入之幕次,所以塞到現在位置的前面
		{
			prev->nextTermPtr = tmpPtr;
			tmpPtr->nextTermPtr = current;
		}

	}
	
	return;
}


void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{
    int aIndex = 0, bIndex = 0, dIndex = 0;

    while (aIndex < MAX_TERMS && bIndex < MAX_TERMS) 
	{
        if (a[aIndex].coef == 0 && b[bIndex].coef == 0)
            break;

        if (a[aIndex].expo > b[bIndex].expo) 
		{
            d[dIndex] = a[aIndex];
            aIndex++;
        }
        else if (a[aIndex].expo < b[bIndex].expo) 
		{
            d[dIndex] = b[bIndex];
            bIndex++;
        }
		//將幕次大的存入d

        else 
		{
            d[dIndex].coef = a[aIndex].coef + b[bIndex].coef;
            d[dIndex].expo = a[aIndex].expo;

            if (d[dIndex].coef != 0)//加總為0的話不處理
                dIndex++;

            aIndex++,bIndex++;
            continue;
        }
        dIndex++;
    }
}

linkedPolynomialTerm *addLinkBasedPoly(linkedPolynomialTerm *aPtr, linkedPolynomialTerm *bPtr)
{
	linkedPolynomialTerm *dPtr = nullptr;
		while(aPtr != nullptr && bPtr != nullptr)
		{
			if(aPtr->expo > bPtr->expo)
			{
				inputLinkTerms( dPtr, aPtr->coef, aPtr->expo);
				aPtr = aPtr->nextTermPtr;
			}
			else if(bPtr->expo > aPtr->expo)
			{
				inputLinkTerms( dPtr, bPtr->coef, bPtr->expo);
				bPtr = bPtr->nextTermPtr;
			}
			else if(aPtr->expo == bPtr->expo)
			{
				if(aPtr->coef + bPtr->coef)inputLinkTerms( dPtr, ((aPtr->coef) + (bPtr->coef)), aPtr->expo);
				aPtr = aPtr->nextTermPtr,bPtr = bPtr->nextTermPtr;
			}
		}
		if(aPtr == nullptr)
			for( ; bPtr != nullptr; bPtr = bPtr->nextTermPtr)
				inputLinkTerms( dPtr, bPtr->coef, bPtr->expo);
		
		if(bPtr == nullptr)
			for( ; aPtr != nullptr; aPtr = aPtr->nextTermPtr)
				inputLinkTerms( dPtr, aPtr->coef, aPtr->expo);
		

		return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
{
	if ( terms[0].coef == 0 ) 
		return;

	if ( terms[0].expo == 0 )
		cout << terms[0].coef;
	else
		cout << terms[0].coef << "X^" << terms[0].expo;

	for ( int i = 1; i < MAX_TERMS; i++ ) {
		if ( terms[i].coef == 0 ) 
			return;

		if ( terms[i].expo == 0 )
			cout << " + " << terms[i].coef;
		else
			cout << " + "<< terms[i].coef  << "X^" << terms[i].expo;
	}
}

void printLinkBasedPoly(linkedPolynomialTerm *polyPtr)
{
	linkedPolynomialTerm *termPtr =  polyPtr;

	if ( termPtr  == nullptr )
			return;
	if ( termPtr->coef == 0 ) 
			return;
	if ( termPtr->expo == 0 )
		cout << termPtr->coef;
	else
		cout << termPtr->coef << "X^" << termPtr->expo;

	termPtr  = termPtr->nextTermPtr;
	
	while ( termPtr  != nullptr ) 
	{
		if ( termPtr->coef == 0 ) 
			return;

		if ( termPtr->expo == 0 )
		{
			cout << " + " << termPtr->coef;
		}
		else
			cout << " + "<< termPtr->coef  << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;
	}
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm *aPtr, *bPtr, *dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear( a ); clear( b ); clear( d );
		clear( aPtr ); clear( bPtr ); clear( dPtr );

		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerms( a, coef, expo );
			inputLinkTerms( aPtr, coef, expo );
		}

		cout << "\n\na = ";
		printArrayBasedPoly( a );
		cout << "\na = ";
		printLinkBasedPoly( aPtr );
		cout << "\n";
		
		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerms( b, coef, expo );
			inputLinkTerms( bPtr, coef, expo );
		}

		cout << "\n\nb = ";
		printArrayBasedPoly( b );

		cout << "\nb = ";
		printLinkBasedPoly( bPtr );

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly( a, b, d );
		cout << "\na + b = ";
		printArrayBasedPoly( d );
		
		dPtr = addLinkBasedPoly( aPtr, bPtr );
		cout << "\na + b = ";
		printLinkBasedPoly( dPtr );

		cout << "\n";
	}
	return 0;
}
 