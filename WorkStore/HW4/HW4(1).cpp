// HW4.cpp : 定義主控台應用程式的進入點。
//

#include <stdio.h>
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct {
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm* nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[])
{
	for (int i = 0; i < MAX_TERMS; i++) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm*& polynomialTermPtr)
{
	linkedPolynomialTerm* tmpPtr;

	while (polynomialTermPtr != nullptr) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo)
{
	if (coef == 0)return;
	for (int i = 0; i <= MAX_TERMS; i++)
	{
		if (terms[i].expo == expo || terms[i].coef == 0)
		{
			terms[i].expo = expo, terms[i].coef = coef;
			break;
		}
		else if (expo > terms[i].expo)
		{
			for (int j = MAX_TERMS - 1; j >= i; j--)
				terms[j].expo = terms[j - 1].expo, terms[j].coef = terms[j - 1].coef;
			terms[i].expo = expo, terms[i].coef = coef;
			break;
		}
	}


	return;

}

void inputLinkTerms(linkedPolynomialTerm*& polyPtr, int coef, int expo)
{
	linkedPolynomialTerm* tmpPtr;

	tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = coef;
	tmpPtr->expo = expo;
	tmpPtr->nextTermPtr = nullptr;
	if (coef == 0)return;
	if (polyPtr == nullptr || tmpPtr->expo > polyPtr->expo) //接在"現在的"的前面
	{
		tmpPtr->nextTermPtr = polyPtr;
		polyPtr = tmpPtr;
	}
	else if (tmpPtr->expo == polyPtr->expo)
	{
		tmpPtr->nextTermPtr = polyPtr->nextTermPtr;
		polyPtr = tmpPtr;
	}
	else
	{
		linkedPolynomialTerm* current = polyPtr;
		while (current->nextTermPtr != nullptr && tmpPtr->expo < current->nextTermPtr->expo)
			current = current->nextTermPtr;

		if (current->expo == tmpPtr->expo) //替換用
		{
			tmpPtr->nextTermPtr = current->nextTermPtr;
			current = tmpPtr;
		}
		else //要是current是尾巴的話，就把current接到tmpPtr上
		{
			current->nextTermPtr = tmpPtr;
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

			aIndex++, bIndex++;
			continue;
		}
		dIndex++;
	}
}

linkedPolynomialTerm* addLinkBasedPoly(linkedPolynomialTerm* aPtr, linkedPolynomialTerm* bPtr)
{
	linkedPolynomialTerm* dPtr = nullptr;
	while (aPtr != nullptr && bPtr != nullptr)
	{
		if (aPtr->expo > bPtr->expo)
		{
			inputLinkTerms(dPtr, aPtr->coef, aPtr->expo);
			aPtr = aPtr->nextTermPtr;
		}
		else if (bPtr->expo > aPtr->expo)
		{
			inputLinkTerms(dPtr, bPtr->coef, bPtr->expo);
			bPtr = bPtr->nextTermPtr;
		}
		else if (aPtr->expo == bPtr->expo)
		{
			if (aPtr->coef + bPtr->coef)inputLinkTerms(dPtr, ((aPtr->coef) + (bPtr->coef)), aPtr->expo);
			aPtr = aPtr->nextTermPtr, bPtr = bPtr->nextTermPtr;
		}
	}
	if (aPtr == nullptr)
		for (; bPtr != nullptr; bPtr = bPtr->nextTermPtr)
			inputLinkTerms(dPtr, bPtr->coef, bPtr->expo);

	if (bPtr == nullptr)
		for (; aPtr != nullptr; aPtr = aPtr->nextTermPtr)
			inputLinkTerms(dPtr, aPtr->coef, aPtr->expo);


	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
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
}

void printLinkBasedPoly(linkedPolynomialTerm* polyPtr)
{
	linkedPolynomialTerm* termPtr = polyPtr;

	if (termPtr == nullptr)
		return;
	if (termPtr->coef == 0)
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
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm* aPtr, * bPtr, * dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear(a); clear(b); clear(d);
		clear(aPtr); clear(bPtr); clear(dPtr);

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(a, coef, expo);
			inputLinkTerms(aPtr, coef, expo);
		}

		cout << "\n\na = ";
		printArrayBasedPoly(a);
		cout << "\na = ";
		printLinkBasedPoly(aPtr);
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			inputTerms(b, coef, expo);
			inputLinkTerms(bPtr, coef, expo);
		}

		cout << "\n\nb = ";
		printArrayBasedPoly(b);

		cout << "\nb = ";
		printLinkBasedPoly(bPtr);

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly(a, b, d);
		cout << "\na + b = ";
		printArrayBasedPoly(d);

		dPtr = addLinkBasedPoly(aPtr, bPtr);
		cout << "\na + b = ";
		printLinkBasedPoly(dPtr);

		cout << "\n";
	}
	return 0;
}
