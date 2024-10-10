// HW5.cpp : 定義主控台應用程式的進入點。
//

#include "stdio.h"
#include <iostream>
#include <math.h>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm { 
public:                          
	int coef;
	int expo;
};                                                                          /////
                                                                         
class ArrayPolynomial {                                        /////

public:                                                                  /////
	PolynomialTerm terms[MAX_TERMS]; /////

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo) /////
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
					if(terms[j].coef == NULL)break;
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

	void addArrayBasedPoly(ArrayPolynomial &a, ArrayPolynomial &b) /////
	{

		int aIndex = 0, bIndex = 0, dIndex = 0;

		while (aIndex < MAX_TERMS && bIndex < MAX_TERMS) 
		{
			if (a.terms[aIndex].coef == 0 && b.terms[bIndex].coef == 0)
				break;

			if (a.terms[aIndex].expo > b.terms[bIndex].expo) 
			{
				terms[dIndex] = a.terms[aIndex];
				aIndex++;
			}
			else if (a.terms[aIndex].expo < b.terms[bIndex].expo) 
			{
				terms[dIndex] = b.terms[bIndex];
				bIndex++;
			}
			//將幕次大的存入d

			else 
			{
				terms[dIndex].coef = a.terms[aIndex].coef + b.terms[bIndex].coef;
				terms[dIndex].expo = a.terms[aIndex].expo;

				if (terms[dIndex].coef != 0)//加總為0的話不處理
					dIndex++;

				aIndex++,bIndex++;
				continue;
			}
			dIndex++;
		}
	}

	void swap( int &a, int &b)
	{
		int t = a;
		a = b;
		b = t;
	}
	void reverseArrayBasedPoly() /////
	{
		int start = 0, end = 0;
		for(int i=0;i<MAX_TERMS;i++)
			if(terms[i].coef != 0)end++;
		while(start < end-1)
		{
			swap(terms[start].expo, terms[end-1].expo);
			swap(terms[start].coef, terms[end-1].coef);
			start++,end--;
		}
		
	}

	void printArrayBasedPoly() /////
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			std::cout << terms[0].coef;
		else
			std::cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				std::cout << " + " << terms[i].coef;
			else
				std::cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	int compute(int x) 
	{                        
		int sum = 0;  
		for(int i = 0; i < MAX_TERMS; i++)
			sum += terms[i].coef * pow( x, terms[i].expo);
		return sum;    
	}                           
};                                                                

class LinkedPolynomialTerm {                       
public:                                                          
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr; /////
};                                                                  /////

class LinkPolynomial {                                /////
public:                                                          /////
	LinkedPolynomialTerm *polynomialTermPtr = nullptr; /////

	void clear() /////
	{
		LinkedPolynomialTerm *tmpPtr;                       

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkTerms(int coef, int expo) /////
	{
	LinkedPolynomialTerm *tmpPtr;
	
	tmpPtr = new LinkedPolynomialTerm;
	tmpPtr->coef = coef;
	tmpPtr->expo = expo;
	tmpPtr->nextTermPtr = nullptr;
	if(coef == 0)
	{
		if(polynomialTermPtr->expo == expo)
		{
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		}
		else 
		{
			LinkedPolynomialTerm *current = polynomialTermPtr;
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
	if(polynomialTermPtr == nullptr || tmpPtr->expo > polynomialTermPtr->expo) //接在"現在的"的前面
	{
		tmpPtr->nextTermPtr = polynomialTermPtr;
		polynomialTermPtr = tmpPtr;
	}
	else if(tmpPtr->expo == polynomialTermPtr->expo)
	{
		tmpPtr->nextTermPtr = polynomialTermPtr->nextTermPtr;
		polynomialTermPtr = tmpPtr;
	}
	else 
	{
		LinkedPolynomialTerm *current = polynomialTermPtr;
		while(current->nextTermPtr != nullptr && tmpPtr->expo < current->nextTermPtr->expo)
			current = current->nextTermPtr;
		
		if(current->nextTermPtr->expo == tmpPtr->expo)
		{
			tmpPtr->nextTermPtr = current->nextTermPtr->nextTermPtr;
			current->nextTermPtr = tmpPtr;
		}
		else //接在"現在的"的後面
		{
			tmpPtr->nextTermPtr = current->nextTermPtr;
			current->nextTermPtr = tmpPtr;
		}

	}
	
	return;
}



	void addLinkBasedPoly(LinkPolynomial &aPol, LinkPolynomial &bPol) /////
	{
		LinkedPolynomialTerm *aPtr = aPol.polynomialTermPtr;
		LinkedPolynomialTerm *bPtr = bPol.polynomialTermPtr;
		while(aPtr != nullptr && bPtr != nullptr)
		{
			if(aPtr->expo > bPtr->expo)
			{
				inputLinkTerms( aPtr->coef, aPtr->expo);
				aPtr = aPtr->nextTermPtr;
			}
			else if(bPtr->expo > aPtr->expo)
			{
				inputLinkTerms( bPtr->coef, bPtr->expo);
				bPtr = bPtr->nextTermPtr;
			}
			else if(aPtr->expo == bPtr->expo)
			{
				if(aPtr->coef + bPtr->coef != 0)inputLinkTerms( aPtr->coef+bPtr->coef, aPtr->expo);
				aPtr = aPtr->nextTermPtr,bPtr = bPtr->nextTermPtr;
			}
		}
		if(aPtr == nullptr)
			for( ; bPtr != nullptr; bPtr = bPtr->nextTermPtr)
				inputLinkTerms( bPtr->coef, bPtr->expo);
		
		if(bPtr == nullptr)
			for( ; aPtr != nullptr; aPtr = aPtr->nextTermPtr)
				inputLinkTerms( aPtr->coef, aPtr->expo);
	}
		


	void reverseLinkBasedPoly() /////
	{
		LinkedPolynomialTerm *prev = nullptr, 
							 *current = polynomialTermPtr,
							 *next = nullptr;
		if(polynomialTermPtr == nullptr || polynomialTermPtr->nextTermPtr == nullptr)return ;
		while (current != nullptr)
		{
			next = current->nextTermPtr;
			current->nextTermPtr = prev;
			prev = current;
			current = next;
		}
		polynomialTermPtr = prev;


	}

	void printLinkBasedPoly()                                                            /////
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr; /////

		if (termPtr == nullptr)
			return;
		if (termPtr->coef == 0 ) 
			return;
		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;

		while (termPtr != nullptr) {
			if (termPtr->coef == 0)
				return;

			if (termPtr->expo == 0)
				cout << " + " << termPtr->coef;
			else
				cout << " + " << termPtr->coef << "X^" << termPtr->expo;

			termPtr = termPtr->nextTermPtr;
		}

		return;
	}

	int compute(int x) 	
	{
		LinkedPolynomialTerm *ptr = polynomialTermPtr;
		int sum = 0;
		while(ptr != nullptr)
		{
			sum += ptr->coef * pow( x, ptr->expo);
			ptr = ptr->nextTermPtr;
		}
		return sum;
	}
}; 

int main()
{
	ArrayPolynomial a, b, d;                                                              /////
	LinkPolynomial aPol, bPol, dPol;                                             /////

	int coef, expo, x;


	while (1) {
		a.clear(); b.clear(); d.clear();                                    /////


		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			a.inputTerms(coef, expo);             /////
			aPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\na = ";
		a.printArrayBasedPoly();     /////
		cout << "\na = ";
		aPol.printLinkBasedPoly(); /////
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			b.inputTerms(coef, expo);             /////
			bPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\nb = ";
		b.printArrayBasedPoly();      /////

		cout << "\nb = ";
		bPol.printLinkBasedPoly(); /////

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		d.addArrayBasedPoly(a, b); /////
		cout << "\na + b = ";
		d.printArrayBasedPoly();     /////

		dPol.addLinkBasedPoly(aPol, bPol); /////
		cout << "\na + b = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		d.reverseArrayBasedPoly(); /////
		cout << "\nreversed d = ";
		d.printArrayBasedPoly();     /////
		
		dPol.reverseLinkBasedPoly(); /////
		cout << "\nreversed d = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		cout << "\ninput X: ";
		cin >> x;

		cout << "\nd = ";
		cout << d.compute(x);      //////

		cout << "\nd = ";
		cout << dPol.compute(x); //////

		cout << "\n";

		aPol.clear(); bPol.clear(); dPol.clear(); /////
	}

	return 0;
}
