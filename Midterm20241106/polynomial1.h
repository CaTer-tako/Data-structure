#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};

class ArrayPolynomial {
public:
	PolynomialTerm terms[MAX_TERMS];

	ArrayPolynomial()
	{
		for (int i = 0; i < MAX_TERMS; i++)
			terms[i].coef = terms[i].expo = 0;
	}

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{

		// modify the following code and add your code here

		int i = 0;

		for (; terms[i].coef != 0 && i < MAX_TERMS; i++);

		terms[i].coef = coef;
		terms[i].expo = expo;

		return;
	}

	void printArrayBasedPoly()
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			cout << terms[0].coef;
		else
			cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				cout << " + " << terms[i].coef;
			else
				cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	int maxDgreeCoef() //if (curPtr->expo > MaxExpo)MaxExpo = curPtr->expo;
	{
		int MaxExpo = 0;
		int SumCoef = 0;
		for (int i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].expo > MaxExpo)MaxExpo = terms[i].expo;
		}
		for (int i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].expo == MaxExpo)SumCoef += terms[i].coef;
		}

		return SumCoef;

	}

	bool contain(ArrayPolynomial& poly)
	{
		for (int i = 0,j = 0; i < MAX_TERMS; i++)
		{
			if (poly.terms[i].expo == 0 && poly.terms[i].coef == 0) break;
			if (poly.terms[i].expo == terms[j].expo && poly.terms[i].coef != terms[j].coef || terms[j].expo == 0 && terms[j].coef == 0)//次方相同但數不同 或 到尾
				return false;
			else if (poly.terms[i].expo != terms[j].expo) //要是次方不同j++
				j++;
		}

		return true;

	}

	void difference(ArrayPolynomial& poly)
	{

		for (int i = 0; i < MAX_TERMS; i++)
		{
			for (int j = 0; j < MAX_TERMS; j++)
			{
				if (poly.terms[j].expo == terms[i].expo && poly.terms[j].coef == terms[i].coef)
				{
					terms[i].expo = 0, terms[i].coef = 0;
					for (int k = i; k < MAX_TERMS-1; k++)
						terms[k] = terms[k + 1];
				}
			}
		}

	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr;
};

class LinkedPolynomial {
public:
	LinkedPolynomialTerm *polynomialTermPtr = nullptr;

	void clear()
	{
		LinkedPolynomialTerm *tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputTerms(int coef, int expo)
	{
		// modify the following code and add your code here

		LinkedPolynomialTerm *tmpPtr;

		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = polynomialTermPtr;

		polynomialTermPtr = tmpPtr;

		return;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr;

		if (termPtr == nullptr)
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

	int maxDgreeCoef()
	{
		int MaxExpo = 0;
		int SumCoef = 0;
		for (LinkedPolynomialTerm* curPtr = polynomialTermPtr; curPtr->nextTermPtr != nullptr; curPtr = curPtr->nextTermPtr)
		{
			if (curPtr->expo > MaxExpo)MaxExpo = curPtr->expo;
		}
		for (LinkedPolynomialTerm* cur2Ptr = polynomialTermPtr; cur2Ptr->nextTermPtr != nullptr; cur2Ptr = cur2Ptr->nextTermPtr)
		{
			if (cur2Ptr->expo == MaxExpo)SumCoef += cur2Ptr->coef;
		}

		return SumCoef;

	}

	bool contain(LinkedPolynomial& poly)
	{
		

		return false;

	}
	/*			{
					return false;
					break;
					continue;
			}*/

	void difference(LinkedPolynomial& poly)
	{

		


	}
};
