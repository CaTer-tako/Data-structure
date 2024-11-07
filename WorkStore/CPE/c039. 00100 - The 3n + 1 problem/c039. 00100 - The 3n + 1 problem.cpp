#include <stdio.h>
#include <iostream>
#define swap(x,y) {int t; t=x; x=y; y=t; }
using namespace std;


int compute( int n, int L)
{
    L++;
    if(n == 1)
        return L;
    else if(n%2 == 1)
        return compute( n*3+1, L);
    else if(n%2 == 0)
        return compute( n/2, L);
    
    return L;
}


int main()
{
    int i = 0, j = 0;
    while(scanf("%d %d",&i,&j) != EOF)
    {
        int MaxLength = 0;
        printf("%d %d ",i,j); 
        if(i <= 0 || j >= 1000000)break;
        if(i>j)swap(i,j);
        for(int i2 = i; i2 <= j; i2++)
        {
            int L = compute(i2, 0);
            //printf("[%d]\n\n",L);
            if(MaxLength < L)MaxLength = L;
        }
        printf("%d\n",MaxLength);
    }
    

}