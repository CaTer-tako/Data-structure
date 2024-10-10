#include <stdio.h>
#include <memory.h>

#define MAX_degree 10 /*MAX degree of polynomial+1 多項式的最大值+1*/

typedef struct
{
	int degree; //最高幕次
	int coef [MAX_degree]; //存放多項式各幕次的係數的陣列
	/*多項式 3?^2+5?+1，coef[2]=3 coef[1]=5 coef[0]=1*/
} polynomial;

#define MAX_TERMS 20 /*size of terms array 項數陣列的大小*/
typedef struct
{
	int coef; //係數
	int expo;//幕次(指數)
} polynomial_term;

polynomial_term terms [MAX_TERMS];
/*3?^2+5?+1,terms[0]=3x^2 terms[1]=5x...以此類推*/
int avail = 0;
	
polynomial Zero(polynomial p)
{
	memset(&p, 0, sizeof(p));

	return p;
}

int IsZero(polynomial p)
{
	int f=0;
	for(int i = p.degree;i>=0;i--)
	{
		if(p.coef[i])f=1;
	}
	return 1-f;   
	
}

int Lead_Exp(polynomial p)
{//回傳p的最高幕次
	return p.degree;
}

int COMPARE(int i, int j)
{
	if(i < j)
		return -1;
	else if (i == j)
		return 0;
	return 1;
}

int Coef(polynomial p, int expo)
{
	return p.coef[expo];
}

polynomial Attach(polynomial p, int coef, int expo)
{ //p,係數,幕次

	p.coef[expo] += coef;
	if(expo >= p.degree)p.degree = expo;
	return p;
}

polynomial Remove(polynomial p, int expo)
{

// add your code
	p.coef[expo] = 0;
	if(expo == p.degree) {
		for(int i=p.degree;i>=0;i--)
		{
			if(p.coef[i])
			{
				p.degree = i;
				return p;
			}
		}
		p.degree = 0;
	}
	return p;
}

void attach(int coef, int expo)
{
	if (avail >= MAX_TERMS)   
		return;

	terms[avail].coef = coef;
	terms[avail++].expo = expo;
}

void PrintPoly1(polynomial p) 
{
	for (int i = p.degree; i >= 0; i--) {
		if (p.coef[i] != 0 ) {
			if (p.degree == i) {
				if (i == 0 )
					printf("%d", p.coef[i]);
				else
					printf("%dX^%d", p.coef[i], i);
			}
			else {
				if ( i == 0 )
					printf(" + %d", p.coef[i]);
				else
					printf(" + %dX^%d", p.coef[i], i);
			}
		}
	}
}

void PrintPoly2(polynomial_term t[], int start, int finish)
{
	//printf("\nEnter void\n");
	int min=10,array[10] = {0};
	for(int i = finish,j = start;i >= j;i--)
 	{
		array[terms[i].expo] = terms[i].coef;
		if(terms[i].expo < min)min = terms[i].expo;
	}

	for(int k = 9;k >= 0;k--)
	{	
		
		if(array[k])
		{
			//printf("\narray[%d]=%d\n",k,array[k]);
			char str[50] = {0};
			if (k != 0) 
   				 sprintf(str, "X^%d", k);
 			else 
  			 	str[0] = '\0';

			//sprintf(str, k?"X^%d":"\0", k);
			printf("%d%s%s",array[k],str,(k==min || k==0)?"":" + ");
			//printf("\n[min:%d,k:%d]\n",min,k);
		}
		
		 
	}


}
/*	    
	    //printf("[i:%d],[j:%d]\n",i,j);
		if(terms[i].coef)
			printf("%dX^",terms[i].coef);
		else continue;
		printf("%d%s",terms[i].expo,(i==j)?"":" + ");
		printf("terms[%d].coef:%d\nterms[%d].expo:[%d]\n",terms[i].coef,i,terms[i].expo,i); */

polynomial padd1(polynomial p1, polynomial p2)
{
	polynomial p3;
	int sum;

	p3.degree = 0;
	p3 = Zero(p3);

	while ( ! IsZero(p1) && ! IsZero(p2) ) {
	   switch ( COMPARE( Lead_Exp(p1), Lead_Exp(p2) ) ) {
		   case -1: 
			   p3 = Attach(p3, Coef(p2, Lead_Exp(p2)), Lead_Exp(p2));
			   p2 = Remove(p2, Lead_Exp(p2));
			   break;
		  case  0:
			  sum = Coef(p1, Lead_Exp (p1)) + Coef( p2, Lead_Exp(p2));
			  
			  if (sum)
				  p3 = Attach (p3, sum, Lead_Exp(p1));
			  
			  p1 = Remove(p1 , Lead_Exp(p1));
			  p2 = Remove(p2 , Lead_Exp(p2));
			  break;
		  case 1:
			  p3 = Attach(p3, Coef (p1, Lead_Exp(p1)), Lead_Exp(p1));
			  p1 = Remove(p1, Lead_Exp(p1));
	   }  
	}

	while (!IsZero(p1) ) {
		p3 = Attach(p3, Coef (p1, Lead_Exp(p1)), Lead_Exp(p1));
		p1 = Remove(p1, Lead_Exp(p1));
	}
	while (!IsZero(p2) ) {
		p3 = Attach(p3, Coef (p2, Lead_Exp(p2)), Lead_Exp(p2));
		p2 = Remove(p2, Lead_Exp(p2));
	}

	return p3;
}

void padd2(int starta, int finisha, int startb, int finishb, int* startd, int* finishd)
{
	int sum;

	*startd = avail;

	while (starta <= finisha && startb <= finishb) {
		switch (COMPARE( terms[starta].expo, terms[startb].expo) ) {
		   case -1: 
			   attach(terms[startb].coef, terms[startb].expo);
			   startb++;
			   break;
		  case  0:
			  sum = terms[starta].coef + terms[startb].coef;
			  
			  if (sum)
				  attach(sum, terms[starta].expo);
			  starta++;
			  startb++;			  
			  break;
		  case 1:
			   attach(terms[starta].coef, terms[starta].expo);
			   starta++;
	   }  
	}

	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expo);
	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expo);

	*finishd = avail - 1;
}

int main()
{
	polynomial a, b, d;
	int coef, expo;
	
	int starta = 0, finisha, startb, finishb, startd, finishd;
	
	memset(terms, 0, sizeof(terms));

	a.degree = b.degree = d.degree = 0;

	a = Zero(a);
	b = Zero(b);
	d = Zero(d);

	while (1) {
		printf("\ninput a's coefficient and exponent: ");
		scanf("%d %d", &coef, &expo);

		if (expo == 0 && coef == 0)
			break;

		a.coef[expo] = coef;

		if (a.degree < expo)
			a.degree = expo; //找出最大幕次

		terms[avail].coef = coef;
		terms[avail].expo = expo;
		avail++;
	}

	finisha = avail - 1;
	startb = avail;

	printf("\n\na = ");
	PrintPoly1(a);
	printf("\na = ");
	PrintPoly2(terms, starta, finisha);
	printf("\n");

	while (1) {
		printf("\ninput b's coefficient and exponent: ");
		scanf("%d %d", &coef, &expo);
		if (expo >= MAX_degree) 
        	continue; 
		if (expo == 0 && coef == 0)
			break;

		b.coef[expo] = coef;
		

		if (b.degree < expo)
			b.degree = expo;

		terms[avail].coef = coef;
		terms[avail].expo = expo;
		avail++;
	}

	finishb = avail - 1;
	printf("\n\nb = ");
	PrintPoly1(b);
	//printf("TEST2\n");
	printf("\nb = ");
	//printf("TEST3\n");
	PrintPoly2(terms, startb, finishb);
    //printf("TEST4\n");
	/* d =a + b, where a, b, and d are polynomials */
	d = padd1(a, b);
	printf("\n\nd = ");
	PrintPoly1(d);
	//printf("TEST5\n");
	padd2(starta, finisha, startb, finishb, &startd, &finishd);
	printf("\nd = ");
	PrintPoly2(terms, startd, finishd);

  	return 0;
}
