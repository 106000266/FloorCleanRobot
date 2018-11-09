#include <iostream>
#define left 1
#define up 2
#define right 3
#define down 4
using namespace std;
char room[1000][1000];
int main()
{
    int n,m;
    int p_row,p_col,dust=0;
    char x='*',y='-';
    cin>>n>>m;
    for(int i=0;i<=n+1;i++)
    {
        for(int j=0;j<=m+1;j++)
            room[i][j]='1';
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>room[i][j];
            if(room[i][j]=='R')
            {
                p_row=i;
                p_col=j;
            }
            else if(room[i][j]=='0')
                dust++;
        }
    }
    cout<<dust<<endl;
    int dir=left;
    int i=p_row,j=p_col;
    while(dust!=0)
    {
        switch(dir)
        {
        case left:
            {
                room[p_row][p_col]='R';
                room[i][j]=y;
                if(room[i][j-1]=='0')
                {
                    --dust;
                    room[i][--j]=x;
                    if(room[i-1][j]=='0') dir=up;
                    for(int k=1;k<=n;k++)
                    {
                        for(int l=1;l<=m;l++)
                            cout<<room[k][l];
                        cout<<endl;
                    }
                    cout<<dust<<endl;
                }
                else if(room[i][j-1]=='1' || room[i][j-1]=='R') dir=up;
                else room[i][--j]=x;
                break;
            }
        case up:
            {
                room[p_row][p_col]='R';
                room[i][j]=y;
                if(room[i-1][j]=='0')
                {
                    --dust;
                    room[--i][j]=x;
                    for(int k=1;k<=n;k++)
                    {
                        for(int l=1;l<=m;l++)
                            cout<<room[k][l];
                        cout<<endl;
                    }
                    cout<<dust<<endl;
                }
                else if(room[i-1][j]=='1' || room[i-1][j]=='R') dir=right;
                else room[--i][j]=x;
                break;
            }
        case right:
            {
                room[p_row][p_col]='R';
                room[i][j]=y;
                if(room[i][j+1]=='0')
                {
                    --dust;
                    room[i][++j]=x;
                    if(room[i-1][j]=='0') dir=up;
                    for(int k=1;k<=n;k++)
                    {
                        for(int l=1;l<=m;l++)
                            cout<<room[k][l];
                        cout<<endl;
                    }
                    cout<<dust<<endl;
                }
                else if(room[i][j+1]=='1' || room[i][j+1]=='R') dir=down;
                else room[i][++j]=x;
                break;
            }
        case down:
            {
                room[p_row][p_col]='R';
                room[i][j]=y;
                if(room[i+1][j]=='0')
                {
                    --dust;
                    room[++i][j]=x;
                    if(room[i][j+1]=='0') dir=right;
                    for(int k=1;k<=n;k++)
                    {
                        for(int l=1;l<=m;l++)
                            cout<<room[k][l];
                        cout<<endl;
                    }
                    cout<<dust<<endl;
                }
                else if(room[i+1][j]=='1' || room[i+1][j]=='R') dir=left;
                else room[++i][j]=x;
                break;
            }
        }
    }
    return 0;
}

/*
Main Question: How to detect shortcut to R & all foods are eaten?6
N*M  Energy
7*11 30
lost_energy++ when step++
if(lost_energy==energy/2) *go back to sleep(R)*
come back road - -> +
detect R

eating_priority: left > up > right > down
if(room[i][j-1]==0 room[i-1][j]==0 room[i][j+1]==0 room[i+1][j]==0) *eat* 0 -> -
if(all direction!=0) go back last step

rules:
1:wall
0:food
-:eaten
R:bed
*:fat

11111111111
10001110011
10001110001
100011R0011
10001111011
10000000001
11111111111

*/
