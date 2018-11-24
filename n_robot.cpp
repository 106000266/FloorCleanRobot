#include <iostream>
#define left 1
#define up 2
#define right 3
#define down 4
using namespace std;
char room[1000][1000];
int row[1000],column[1000];
int main()
{
    int n,m,battery;
    int p_row,p_col,dust=0,step=0,en=0,cen=0,pen=0,index=0;
    char x='*',y='-',z='P';
    cin>>n>>m>>battery;
    int elec=battery;
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
    int dir=left,mem=0;
    int i=p_row,j=p_col;
    while(dust!=0)
    {
        if(elec!=battery/2 && !en && !cen)
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
                        elec--;
                        row[index]=i;
                        column[index]=j;
                        index++;
                    }
                    else if((room[i-1][j]!='0' && room[i][j-1]=='1') || (room[i-1][j]=='1' && room[i][j-1]) || (room[i][j-1]!='0' && room[i+1][j]=='0')) dir=down;
                    else if(room[i][j-1]=='1' || (room[i][j-1]=='1' && room[i+1][j]=='1') || (room[i][j-1]!='0' && room[i-1][j]=='0') || room[i][j-1]=='R') dir=up;
                    else if((room[i-1][j]=='1' && room[i][j-1]=='1' && room[i+1][j]=='1') || (room[i][j-1]!='0' && room[i][j+1]=='0')) dir=right;
                    else
                    {
                        room[i][--j]=x;
                        elec--;
                        row[index]=i;
                        column[index]=j;
                        index++;
                    }
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
                        elec--;
                        row[index]=i;
                        column[index]=j;
                        index++;
                    }
                    else if((room[i-1][j]=='1' && room[i][j+1]=='1') || (room[i-1][j]!='0' && room[i][j-1]=='0')) dir=left;
                    else if(room[i-1][j]=='1' || (room[i-1][j]=='1' && room[i][j-1]=='1') || (room[i-1][j]!='0' && room[i][j+1]=='0') || room[i-1][j]=='R') dir=right;
                    else if((room[i-1][j]=='1' && room[i][j+1]=='1' && room[i][j-1]=='1') || (room[i-1][j]!='0' && room[i+1][j]=='0')) dir=down;
                    else
                    {
                        room[--i][j]=x;
                        elec--;
                        row[index]=i;
                        column[index]=j;
                        index++;
                    }
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
                        elec--;
                        row[index]=i;
                        column[index]=j;
                        index++;
                    }
                    else if((room[i][j+1]=='1' && room[i+1][j]=='1') || (room[i][j+1]!='0' && room[i-1][j]=='0')) dir=up;
                    else if(room[i][j+1]=='1' || (room[i][j+1]=='1' && room[i-1][j]=='1') || (room[i][j+1]!='0' && room[i+1][j]=='0') || room[i][j+1]=='R') dir=down;
                    else if((room[i][j+1]=='1' && room[i+1][j]=='1' && room[i-1][j]=='1') || (room[i][j+1]!='0' && room[i][j-1]=='0')) dir=left;
                    else
                    {
                        room[i][++j]=x;
                        elec--;
                        row[index]=i;
                        column[index]=j;
                        index++;
                    }
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
                        elec--;
                        row[index]=i;
                        column[index]=j;
                        index++;
                    }
                    else if((room[i+1][j]=='1' && room[i][j-1]=='1') || (room[i+1][j]!='0' && room[i][j+1]=='0')) dir=right;
                    else if(room[i+1][j]=='1' || (room[i+1][j]=='1' && room[i][j+1]=='1') || (room[i+1][j]!='0' && room[i][j-1]=='0') || room[i+1][j]=='R') dir=left;
                    else if((room[i+1][j]=='1' && room[i][j-1]=='1' && room[i][j+1]=='1') || (room[i+1][j]!='0' && room[i-1][j]=='0')) dir=up;
                    else
                    {
                        room[++i][j]=x;
                        elec--;
                        row[index]=i;
                        column[index]=j;
                        index++;
                    }
                    break;
                }
            }
        }
        else
        {
            if(elec==battery/2)
            {
                mem=dir;
                switch(dir)
                {
                    case left:
                    {
                        if(room[i+1][j]=='R') dir=down;
                        else if(room[i-1][j]=='R') dir=up;
                        else dir=right;
                        break;
                    }
                    case up:
                    {
                        if(room[i][j+1]=='R') dir=right;
                        else if(room[i][j-1]=='R') dir=left;
                        else dir=down;
                        break;
                    }
                    case right:
                    {
                        if(room[i+1][j]=='R') dir=down;
                        else if(room[i-1][j]=='R') dir=up;
                        else dir=left;
                        break;
                    }
                    case down:
                    {
                        if(room[i][j+1]=='R') dir=right;
                        else if(room[i][j-1]=='R') dir=left;
                        else dir=up;
                        break;
                    }
                }
            }
            if(step==0) cen=0;
            if((i!=p_row || j!=p_col) && elec!=0)
            {
                en=1,cen=1;
                switch(dir)
                {
                case left:
                    {
                        if(room[i+1][j]=='1' && room[i-1][j]=='1' && room[i][j-1]!='1')
                        {
                            room[i][--j]=x;
                            room[i][j+1]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i+1][j]!='1') dir=down;
                            else if(room[i-1][j]!='1') dir=up;
                        }
                        else if(room[i+1][j]=='1' && room[i][j-1]!='1')
                        {
                            room[i][--j]=x;
                            room[i][j+1]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i+1][j]!='1') dir=down;
                        }
                        else if(room[i-1][j]=='1' && room[i][j-1]!='1')
                        {
                            room[i][--j]=x;
                            room[i][j+1]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i-1][j]!='1') dir=up;
                        }
                        else if(room[i+1][j]!='1' && room[i-1][j]!='1' && room[i][j-1]!='1')
                        {
                            room[i][--j]=x;
                            room[i][j+1]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                        }
                        if(room[i][j-1]=='1' || room[i-1][j]==z || room[i+1][j]=='R') dir=down;
                        if((room[i][j-1]=='1' && room[i+1][j]=='1') || room[i-1][j]=='R') dir=up;
                        if(room[i][j-1]=='R' || room[i][j+1]=='R' || room[i-1][j]=='R' || room[i+1][j]=='R') pen=1;
                        break;
                    }
                case up:
                    {
                        if(room[i][j+1]=='1' && room[i][j-1]=='1' && room[i-1][j]!='1')
                        {
                            room[--i][j]=x;
                            room[i+1][j]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i][j+1]!='1') dir=right;
                            else if(room[i][j-1]!='1') dir=left;
                        }
                        else if(room[i][j+1]=='1' && room[i-1][j]!='1')
                        {
                            room[--i][j]=x;
                            room[i+1][j]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i][j+1]!='1') dir=right;
                        }
                        else if(room[i][j-1]=='1' && room[i-1][j]!='1')
                        {
                            room[--i][j]=x;
                            room[i+1][j]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i][j-1]!='1') dir=left;
                        }
                        else if(room[i-1][j]!='1' && room[i][j+1]!='1' && room[i][j-1]!='1')
                        {
                            room[--i][j]=x;
                            room[i+1][j]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                        }
                        if(room[i-1][j]=='1' || room[i][j-1]=='R') dir=left;
                        if((room[i-1][j]=='1' && room[i][j-1]=='1') || room[i][j+1]=='R') dir=right;
                        if(room[i][j-1]=='R' || room[i][j+1]=='R') pen=1;
                        break;
                    }
                case right:
                    {
                        if(room[i+1][j]=='1' && room[i-1][j]=='1' && room[i][j+1]!='1')
                        {
                            room[i][++j]=x;
                            room[i][j-1]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i+1][j]!='1')dir=down;
                            else if(room[i-1][j]!='1') dir=up;
                        }
                        else if(room[i+1][j]=='1' && room[i][j+1]!='1')
                        {
                            room[i][++j]=x;
                            room[i][j-1]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i+1][j]!='1')dir=down;
                        }
                        else if(room[i-1][j]=='1'&& room[i][j+1]!='1')
                        {
                            room[i][++j]=x;
                            room[i][j-1]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i-1][j]!='1')dir=up;
                        }
                        else if(room[i+1][j]!='1' && room[i][j+1]!='1' && room[i-1][j]!='1')
                        {
                            room[i][++j]=x;
                            room[i][j-1]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                        }
                        if(room[i][j+1]=='1' || room[i-1][j]=='R') dir=up;
                        if((room[i][j+1]=='1' && room[i-1][j]=='1') || room[i+1][j]=='R' || room[i-1][j]==z) dir=down;
                        if(room[i][j-1]=='R' || room[i][j+1]=='R' || room[i-1][j]=='R' || room[i+1][j]=='R') pen=1;
                        break;
                    }
                case down:
                    {
                        if(room[i][j+1]=='1' && room[i][j-1]=='1' && room[i+1][j]!='1')
                        {
                            room[++i][j]=x;
                            room[i-1][j]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i][j+1]!='1')dir=right;
                            else if(room[i][j-1]!='1') dir=left;
                        }
                        if(room[i][j+1]=='1' && room[i+1][j]!='1')
                        {
                            room[++i][j]=x;
                            room[i-1][j]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i][j+1]!='1')dir=right;
                        }
                        else if(room[i][j-1]=='1' && room[i+1][j]!='1')
                        {
                            room[++i][j]=x;
                            room[i-1][j]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                            if(room[i][j-1]!='1')dir=left;
                        }
                        else if(room[i+1][j]!='1' && room[i][j+1]!='1' && room[i][j-1]!='1')
                        {
                            room[++i][j]=x;
                            room[i-1][j]=z;
                            elec--;
                            step++;
                            row[index]=i;
                            column[index]=j;
                            index++;
                        }
                        if(room[i+1][j]=='1' || room[i][j+1]=='R') dir=right;
                        if((room[i][j+1]=='1' && room[i+1][j]=='1') || room[i][j-1]=='R') dir=left;
                        if(room[i][j-1]=='R' || room[i][j+1]=='R' || room[i-1][j]=='R' || room[i+1][j]=='R') pen=1;
                        break;
                    }
                }
            }
            else if(pen)
            {
                en=0;
                elec=battery;
                dir=left;
                while(step)
                {
                    switch(dir)
                    {
                    case left:
                        {
                            if(room[i][j-1]!=z)
                            {
                                if(room[i][j+1]==z) dir=right;
                                else if(room[i+1][j]==z) dir=down;
                                else if(room[i-1][j]==z) dir=up;
                            }
                            else if(room[i][j-1]==z)
                            {
                                room[i][--j]=x;
                                room[p_row][p_col]='R';
                                room[i][j+1]=y;
                                elec--;
                                step--;
                                row[index]=i;
                                column[index]=j;
                                index++;
                            }
                            break;
                        }
                    case up:
                        {
                            if(room[i-1][j]!=z)
                            {
                                if(room[i][j+1]==z) dir=right;
                                else if(room[i+1][j]==z) dir=down;
                                else if(room[i][j-1]==z) dir=left;
                            }
                            else if(room[i-1][j]==z)
                            {
                                room[--i][j]=x;
                                room[p_row][p_col]='R';
                                room[i+1][j]=y;
                                elec--;
                                step--;
                                row[index]=i;
                                column[index]=j;
                                index++;
                            }
                            break;
                        }
                    case right:
                        {
                            if(room[i][j+1]!=z)
                            {
                                if(room[i-1][j]==z) dir=up;
                                else if(room[i+1][j]==z) dir=down;
                                else if(room[i][j-1]==z) dir=left;
                            }
                            else if(room[i][j+1]==z)
                            {
                                room[i][++j]=x;
                                room[p_row][p_col]='R';
                                room[i][j-1]=y;
                                elec--;
                                step--;
                                row[index]=i;
                                column[index]=j;
                                index++;
                            }
                            break;
                        }
                    case down:
                        {
                            if(room[i+1][j]!=z)
                            {
                                if(room[i-1][j]==z) dir=up;
                                else if(room[i][j+1]==z) dir=right;
                                else if(room[i][j-1]==z) dir=left;
                            }
                            else if(room[i+1][j]==z)
                            {
                                room[++i][j]=x;
                                room[p_row][p_col]='R';
                                room[i-1][j]=y;
                                elec--;
                                step--;
                                row[index]=i;
                                column[index]=j;
                                index++;
                            }
                            break;
                        }
                    }
                    if(room[i][j-1]=='0')
                    {
                        cen=0,pen=0;
                        dir=left;
                        break;
                    }
                    if(room[i+1][j]=='0')
                    {
                        cen=0,pen=0;
                        dir=down;
                        break;
                    }
                    if(room[i-1][j]=='0')
                    {
                        cen=0,pen=0;
                        dir=up;
                        break;
                    }
                    if(room[i][j+1]=='0')
                    {
                        cen=0,pen=0;
                        dir=right;
                        break;
                    }
                }
                cen=0,pen=0;
                dir=mem;
            }
        }
    }
    while((i!=p_row || j!=p_col) && elec!=0)
    {
        switch(dir)
        {
            case left:
            {
                if(room[i+1][j]=='1' && room[i-1][j]=='1' && room[i][j-1]!='1')
                {
                    room[i][--j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i+1][j]!='1') dir=down;
                    else if(room[i-1][j]!='1') dir=up;
                }
                else if(room[i+1][j]=='1' && room[i][j-1]!='1')
                {
                    room[i][--j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i+1][j]!='1') dir=down;
                }
                else if(room[i-1][j]=='1' && room[i][j-1]!='1')
                {
                    room[i][--j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i-1][j]!='1') dir=up;
                }
                else if(room[i+1][j]!='1' && room[i-1][j]!='1' && room[i][j-1]!='1')
                {
                    room[i][--j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                }
                if((room[i+1][j]==x && room[i-1][j]!=x) || room[i][j-1]=='1' || room[i-1][j]=='R') dir=up;
                if((room[i+1][j]!=x && room[i-1][j]==x) || (room[i][j-1]=='1' && room[i-1][j]=='1') ||  room[i+1][j]=='R') dir=down;
                if(room[i-1][j]=='R' || room[i+1][j]=='R') pen=1;
                break;
            }
            case up:
            {
                if(room[i][j+1]=='1' && room[i][j-1]=='1' && room[i-1][j]!='1')
                {
                    room[--i][j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i][j+1]!='1') dir=right;
                    else if(room[i][j-1]!='1') dir=left;
                }
                else if(room[i][j+1]=='1' && room[i-1][j]!='1')
                {
                    room[--i][j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i][j+1]!='1') dir=right;
                }
                else if(room[i][j-1]=='1' && room[i-1][j]!='1')
                {
                    room[--i][j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i][j-1]!='1') dir=left;
                }
                else if(room[i-1][j]!='1' && room[i][j+1]!='1' && room[i][j-1]!='1')
                {
                    room[--i][j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                }
                if((room[i][j-1]==x && room[i][j+1]!=x) || room[i-1][j]=='1' || room[i][j+1]=='R') dir=right;
                if((room[i][j-1]!=x && room[i][j+1]==x) || (room[i-1][j]=='1' && room[i][j+1]=='1') || room[i][j-1]=='R') dir=left;
                if(room[i][j-1]=='R' || room[i][j+1]=='R') pen=1;
                break;
            }
            case right:
            {
                if(room[i+1][j]=='1' && room[i-1][j]=='1' && room[i][j+1]!='1')
                {
                    room[i][++j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i+1][j]!='1')dir=down;
                    else if(room[i-1][j]!='1') dir=up;
                }
                else if(room[i+1][j]=='1' && room[i][j+1]!='1')
                {
                    room[i][++j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i+1][j]!='1')dir=down;
                }
                else if(room[i-1][j]=='1'&& room[i][j+1]!='1')
                {
                    room[i][++j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i-1][j]!='1')dir=up;
                }
                else if(room[i+1][j]!='1' && room[i][j+1]!='1' && room[i-1][j]!='1')
                {
                    room[i][++j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                }
                if((room[i+1][j]!=x && room[i-1][j]==x) || room[i][j+1]=='1' || room[i+1][j]=='R') dir=down;
                if((room[i+1][j]==x && room[i-1][j]!=x) || (room[i][j+1]=='1' && room[i+1][j]=='1') || room[i-1][j]=='R') dir=up;
                if(room[i-1][j]=='R' || room[i+1][j]=='R') pen=1;
                break;
            }
            case down:
            {
                if(room[i][j+1]=='1' && room[i][j-1]=='1' && room[i+1][j]!='1')
                {
                    room[++i][j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i][j+1]!='1')dir=right;
                    else if(room[i][j-1]!='1') dir=left;
                }
                if(room[i][j+1]=='1' && room[i+1][j]!='1')
                {
                    room[++i][j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i][j+1]!='1')dir=right;
                }
                else if(room[i][j-1]=='1' && room[i+1][j]!='1')
                {
                    room[++i][j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                    if(room[i][j-1]!='1')dir=left;
                }
                else if(room[i+1][j]!='1' && room[i][j+1]!='1' && room[i][j-1]!='1')
                {
                    room[++i][j]=x;
                    elec--;
                    row[index]=i;
                    column[index]=j;
                    index++;
                }
                if((room[i][j-1]!=x && room[i][j+1]==x) || room[i+1][j]=='1' || room[i][j-1]=='R') dir=left;
                if((room[i][j-1]==x && room[i][j+1]!=x) || (room[i+1][j]=='1' && room[i][j-1]=='1') || room[i][j+1]=='R') dir=right;
                if(room[i][j-1]=='R' || room[i][j+1]=='R') pen=1;
                break;
            }
        }
    }
    cout<<index+1<<endl;
    for(int k=0;k<index;k++)
        cout<<row[k]<<" "<<column[k]<<endl;
    return 0;
}

/*
Main Question: How to detect shortcut to R?
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
11001110011
110011R0011
11001111011
10000000011
11111111111

1111111111
1000100001
1000100001
1000100001
1011111101
1000000001
1111R11111
*/

