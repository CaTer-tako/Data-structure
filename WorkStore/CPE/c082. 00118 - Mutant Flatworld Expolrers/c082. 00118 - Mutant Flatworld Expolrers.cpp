#include <bits/stdc++.h>
//https://zerojudge.tw/ShowProblem?problemid=c082
#define MaxCoordinates 50
#define MaxCommonCount 100
using namespace std;

char Where[4] = {{'N'},{'E'},{'S'},{'W'}};
int move[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int TurnTo()
{
    ;
}

int ForWard()
{
    ;
}

int main()
{
    int x = 0, y = 0, x0 = 0, y0 = 0;
    char Location, common[MaxCommonCount] = {0};
    cin >> x >> y;
    printf("最大x,y:[%d,%d]\n",x,y);
    while(scanf("%d %d %c\n%s",&x0,&y0,&Location,common) != EOF)//初始位置座標 , 初始面對方向
    {
        printf("現在座標:[%d,%d,%c]\n",x0,y0,Location);
        //printf("字串:[%s]\n",common);


        for(int i=0; i < MaxCommonCount && common[i]!=0; i++)
        {
            //printf("[%c,%d]",common[i],i);
            if     (common[i] == 'F' || common[i] == 'f');

            else if(common[i] == 'R' || common[i] == 'r')
            {
                for(int i=0;i<4;i++)
                {
                    if(Where[i] = Location)
                    {
                        if(i++==5)i=0;
                        Location = Where[i];

                    }
                    else continue;
                }
            }

            else if(common[i] == 'L' || common[i] == 'l');
            {
                for(int i=0;i<4;i++)
                {
                    if(Where[i] = Location)
                    {
                        if(i--==-1)i=4;
                        Location = Where[i];
                    }
                    else continue;
                }
            }
            //好像三個都可使用同一個for迴圈，但用if判斷字元
            

        }
        cout << endl;
        
    }
}