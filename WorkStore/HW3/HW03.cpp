// HW3.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#define MAX_TERMS 10

typedef struct
{
	int coef;
	int expo;
} polynomialTerm;

void clear(polynomialTerm t[]) 
{
	for ( int i = 0; i < MAX_TERMS; i++ ) 
	{ //�ΨӦs��h����
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void printArrayBasedPoly(polynomialTerm t[])
{
	if ( t[0].coef == 0 ) 
		return;

	if ( t[0].expo == 0 )
		cout << t[0].coef;
	else
		cout << t[0].coef << "X^" << t[0].expo;

	for ( int i = 1; i < MAX_TERMS; i++ ) 
	{
		if ( t[i].coef == 0 ) 
			return;

		if ( t[i].expo == 0 )
			cout << " + " << t[i].coef;
		else
			cout << " + "<< t[i].coef  << "X^" << t[i].expo;
	}
}

void inputTerm(polynomialTerm t[], int coef, int expo)
{
	if(coef == 0)
	{
		for(int i = 0; i < MAX_TERMS; i++)
		{
			if(t[i].expo == expo)
			{
				t[i].coef = 0,t[i].expo = 0;
				for(int j = i; j <= MAX_TERMS; j++)
				{
					t[j] = t[j+1];
					if(t[j].coef == NULL)break;
				}
			}
		}
		return;
	}

	for(int i = 0; i < MAX_TERMS; i++)
	{
		if( t[i].coef == 0)
		{
			t[i].expo = expo,t[i].coef = coef;
			break;
		}//4 4 

		if(t[i].expo == expo)//搜尋的幕次 = 新幕次
		{
			t[i].expo = expo,t[i].coef = coef;
			break;
		}

		else if(expo > t[i].expo ) //
		{
			for(int j = MAX_TERMS-1; j >= i; j--)
				t[j].expo = t[j-1].expo,t[j].coef = t[j-1].coef;
			t[i].expo = expo,t[i].coef = coef;
			break;
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
		//�N�����j���s�Jd

        else 
		{
            d[dIndex].coef = a[aIndex].coef + b[bIndex].coef;
            d[dIndex].expo = a[aIndex].expo;

            if (d[dIndex].coef != 0)//�[�`��0���ܤ��B�z
                dIndex++;

            aIndex++,bIndex++;
            continue;
        }
        dIndex++;
    }
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	int coef, expo;

	while (1) {
		clear( a ); clear( b ); clear( d );

		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerm( a, coef, expo );
		}


		cout << "\n\na = ";
		printArrayBasedPoly( a );
		cout << "\n";
		
		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;
			inputTerm( b, coef, expo );
		}

		cout << "\n\nb = ";
		printArrayBasedPoly( b );
		cout << "\n";
		addArrayBasedPoly( a, b, d );
		cout << "\na + b = ";
		printArrayBasedPoly( d );
		cout << "\n";
	}

	return 0;
}
