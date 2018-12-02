#include <iostream>
#include <fstream>
#include <queue>
#include <string.h>
#define left 1
#define up 2
#define right 3
#define down 4
using namespace std;
char room[2000][2000];
int row[]={-1,0,0,1};
int col[]={0,-1,1,0};
int pos_x[1000000]={0};
int pos_y[1000000]={0};
int step_x[1000000]={0};
int step_y[1000000]={0};
int arr[2][1000000]={0};
int solution[2][1000000]={0};
int dis[1000000]={0};
struct Node
{
    int x,y,dist;
};
bool isValid(int **mat,bool **visited,int row,int col,int n,int m)
{
	return (row>=1) && (row<n+1) && (col>=1) && (col<m+1) && !mat[row][col] && !visited[row][col];
}
int BFS1(int **mat,int i,int j,int x,int y,int n,int m)
{
	bool **visited;
	visited=new bool*[n];
	for(int a=0;a<n;a++)
        visited[a]=new bool[m];
	for(int a=0;a<n;a++)
    {
        for(int b=0;b<m;b++)
            visited[a][b]=false;
    }
    queue<Node> q;
    visited[i][j]=true;
    q.push({i,j,0});
    int mini=INT_MAX;
    while (!q.empty())
	{
	    Node node=q.front();
		q.pop();
		int i=node.x,j=node.y,dist=node.dist;
		if (i==x && j==y)
		{
			mini=dist;
			break;
		}
		for (int k=0;k<4;k++)
		{
		    if (isValid(mat,visited,i+row[k],j+col[k],n,m))
			{
			    visited[i+row[k]][j+col[k]]= true;
				q.push({i+row[k],j+col[k],dist+1});
			}
		}
	}
	for(int a=0;a<n;a++)
        delete[] visited[a];
    delete[] visited;
	return mini;
}
void BFS(int **mat,int i,int j,int x,int y,int n,int m)
{
	bool **visited;
	visited=new bool*[n];
	for(int a=0;a<n;a++)
        visited[a]=new bool[m];
    for(int a=0;a<n;a++)
    {
        for(int b=0;b<m;b++)
            visited[a][b]=false;
    }
    int index=0;
	queue<Node> q;
	visited[i][j]=true;
	q.push({i,j,0});
	while (!q.empty())
	{
		Node node = q.front();
		q.pop();
		int i = node.x, j = node.y, dist = node.dist;
		arr[0][index]=i;
		arr[1][index]=j;
		dis[index]=dist;
		index++;
		if (i==x && j==y) break;
        for (int k=0;k<4;k++)
		{
			if (isValid(mat,visited,i+row[k],j+col[k],n,m))
			{
				visited[i+row[k]][j+col[k]] = true;
				q.push({i+row[k],j+col[k],dist+1});
			}
		}
	}
	int sol=0;
	for(int k=1;k<index;k++)
    {
        if(dis[k]!=dis[k-1] && dis[k]!=dis[k+1])
        {
            solution[0][sol]=arr[0][k];
            solution[1][sol]=arr[1][k];
            sol++;
            continue;
        }
        else if(dis[k]!=dis[k+1]) sol++;
        for(int l=k+1;l<index;l++)
        {
            if(dis[k]==dis[l])
            {
                if(BFS1((int**)mat,arr[0][k],arr[1][k],x,y,n,m)<BFS1((int**)mat,arr[0][l],arr[1][l],x,y,n,m))
                {
                    solution[0][sol]=arr[0][k];
                    solution[1][sol]=arr[1][k];
                }
                else
                {
                    solution[0][sol]=arr[0][l];
                    solution[1][sol]=arr[1][l];
                }
            }
            else break;
        }
    }
    for(int k=0;k<sol;k++)
    {
        int l=solution[0][k];
        int r=solution[1][k];
        mat[l][r]=2;
    }
    for(int a=0;a<n;a++)
        delete[] visited[a];
    delete[] visited;
}
int main(int argc,char *argv[])
{
    string str="argv[1]";
    string str1="/floor.data";
    string str2="/final.path";
    string in,out;
    in.append(str);
    in.append(str1);
    out.append(str);
    out.append(str2);
    ifstream infile;
    ofstream outfile(out.c_str());
    infile.open(in.c_str());
    int n,m,battery;
    int p_row,p_col,dust=0,step=0,en=0;
    int **mat;
    char x='*',y='-';
    infile>>n>>m>>battery;
    int elec=battery;
    mat=new int*[n+2];
    for(int i=0;i<=n+2;i++)
        mat[i]=new int[m+2];
    for(int i=0;i<=n+1;i++)
    {
        for(int j=0;j<=m+1;j++)
        {
            room[i][j]='1';
            mat[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            infile>>room[i][j];
            mat[i][j]=room[i][j]-48;
            if(room[i][j]=='R')
            {
                mat[i][j]=0;
                p_row=i;
                p_col=j;
            }
            else if(room[i][j]=='0')
            {
                pos_x[dust]=i;
                pos_y[dust]=j;
                dust++;
            }
        }
    }
    int total=dust;
    int dir=left;
    int i=p_row,j=p_col;
    while(dust!=0)
    {
        if(elec!=battery/2 && !en)
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
                        step_x[step]=j-1;
                        step_y[step]=i-1;
                        step++;
                        elec--;
                        for(int k=0;k<total;k++)
                        {
                            if(pos_x[k]==i && pos_y[k]==j)
                            {
                                pos_x[k]=-1;
                                pos_y[k]=-1;
                            }
                        }
                    }
                    else if((room[i-1][j]!='0' && room[i][j-1]=='1') || (room[i-1][j]=='1' && room[i][j-1]=='1') || (room[i][j-1]!='0' && room[i+1][j]=='0')) dir=down;
                    else if(room[i][j-1]=='1' || (room[i][j-1]=='1' && room[i+1][j]=='1') || (room[i][j-1]!='0' && room[i-1][j]=='0') || room[i][j-1]=='R') dir=up;
                    else if((room[i-1][j]=='1' && room[i][j-1]=='1' && room[i+1][j]=='1') || (room[i][j-1]!='0' && room[i][j+1]=='0')) dir=right;
                    else
                    {
                        room[i][--j]=x;
                        step_x[step]=j-1;
                        step_y[step]=i-1;
                        step++;
                        elec--;
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
                        step_x[step]=j-1;
                        step_y[step]=i-1;
                        step++;
                        elec--;
                        for(int k=0;k<total;k++)
                        {
                            if(pos_x[k]==i && pos_y[k]==j)
                            {
                                pos_x[k]=-1;
                                pos_y[k]=-1;
                            }
                        }
                    }
                    else if((room[i-1][j]=='1' && room[i][j+1]=='1') || (room[i-1][j]!='0' && room[i][j-1]=='0')) dir=left;
                    else if((room[i-1][j]=='1' && room[i][j+1]=='1' && room[i][j-1]=='1') || (room[i-1][j]!='0' && room[i+1][j]=='0')) dir=down;
                    else if(room[i-1][j]=='1' || (room[i-1][j]=='1' && room[i][j-1]=='1') || (room[i-1][j]!='0' && room[i][j+1]=='0') || room[i-1][j]=='R') dir=right;
                    else
                    {
                        room[--i][j]=x;
                        step_x[step]=j-1;
                        step_y[step]=i-1;
                        step++;
                        elec--;
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
                        step_x[step]=j-1;
                        step_y[step]=i-1;
                        step++;
                        elec--;
                        for(int k=0;k<total;k++)
                        {
                            if(pos_x[k]==i && pos_y[k]==j)
                            {
                                pos_x[k]=-1;
                                pos_y[k]=-1;
                            }
                        }
                    }
                    else if((room[i][j+1]=='1' && room[i+1][j]=='1') || (room[i][j+1]!='0' && room[i-1][j]=='0')) dir=up;
                    else if((room[i][j+1]=='1' && room[i+1][j]=='1' && room[i-1][j]=='1') || (room[i][j+1]!='0' && room[i][j-1]=='0')) dir=left;
                    else if(room[i][j+1]=='1' || (room[i][j+1]=='1' && room[i-1][j]=='1') || (room[i][j+1]!='0' && room[i+1][j]=='0') || room[i][j+1]=='R') dir=down;
                    else
                    {
                        room[i][++j]=x;
                        step_x[step]=j-1;
                        step_y[step]=i-1;
                        step++;
                        elec--;
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
                        step_x[step]=j-1;
                        step_y[step]=i-1;
                        step++;
                        elec--;
                        for(int k=0;k<total;k++)
                        {
                            if(pos_x[k]==i && pos_y[k]==j)
                            {
                                pos_x[k]=-1;
                                pos_y[k]=-1;
                            }
                        }
                    }
                    else if((room[i+1][j]=='1' && room[i][j-1]=='1') || (room[i+1][j]!='0' && room[i][j+1]=='0')) dir=right;
                    else if((room[i+1][j]=='1' && room[i][j-1]=='1' && room[i][j+1]=='1') || (room[i+1][j]!='0' && room[i-1][j]=='0')) dir=up;
                    else if(room[i+1][j]=='1' || (room[i+1][j]=='1' && room[i][j+1]=='1') || (room[i+1][j]!='0' && room[i][j-1]=='0') || room[i+1][j]=='R') dir=left;
                    else
                    {
                        room[++i][j]=x;
                        step_x[step]=j-1;
                        step_y[step]=i-1;
                        step++;
                        elec--;
                    }
                    break;
                }
            }
        }
        else
        {
            BFS((int**)mat,i,j,p_row,p_col,n,m);
            while((i!=p_row || j!=p_col) && elec!=0)
            {
                mat[i][j]=0;
                room[p_row][p_col]='R';
                switch(dir)
                {
                case left:
                    {
                        if(mat[i][j-1]==2)
                        {
                            room[i][j]=y;
                            if(room[i][j-1]=='0')
                            {
                                for(int k=0;k<total;k++)
                                {
                                    if(pos_x[k]==i && pos_y[k]==j-1)
                                    {
                                        pos_x[k]=-1;
                                        pos_y[k]=-1;
                                    }
                                }
                                --dust;
                            }
                            room[i][--j]=x;
                            step_x[step]=j-1;
                            step_y[step]=i-1;
                            step++;
                            mat[i][j]=0;
                            elec--;
                        }
                        else if(mat[i+1][j]==2) dir=down;
                        else if(mat[i-1][j]==2) dir=up;
                        else if(mat[i][j+1]==2) dir=right;
                        break;
                    }
                case up:
                    {
                        if(mat[i-1][j]==2)
                        {
                            room[i][j]=y;
                            if(room[i-1][j]=='0')
                            {
                                for(int k=0;k<total;k++)
                                {
                                    if(pos_x[k]==i-1 && pos_y[k]==j)
                                    {
                                        pos_x[k]=-1;
                                        pos_y[k]=-1;
                                    }
                                }
                                --dust;
                            }
                            room[--i][j]=x;
                            step_x[step]=j-1;
                            step_y[step]=i-1;
                            step++;
                            mat[i][j]=0;
                            elec--;
                        }
                        else if(mat[i][j+1]==2) dir=right;
                        else if(mat[i][j-1]==2) dir=left;
                        else if(mat[i+1][j]==2) dir=down;
                        break;
                    }
                case right:
                    {
                        if(mat[i][j+1]==2)
                        {
                            room[i][j]=y;
                            if(room[i][j+1]=='0')
                            {
                                for(int k=0;k<total;k++)
                                {
                                    if(pos_x[k]==i && pos_y[k]==j+1)
                                    {
                                        pos_x[k]=-1;
                                        pos_y[k]=-1;
                                    }
                                }
                                --dust;
                            }
                            room[i][++j]=x;
                            step_x[step]=j-1;
                            step_y[step]=i-1;
                            step++;
                            mat[i][j]=0;
                            elec--;
                        }
                        else if(mat[i+1][j]==2) dir=down;
                        else if(mat[i-1][j]==2) dir=up;
                        else if(mat[i][j-1]==2) dir=left;
                        break;
                    }
                case down:
                    {
                        if(mat[i+1][j]==2)
                        {
                            room[i][j]=y;
                            if(room[i+1][j]=='0')
                            {
                                for(int k=0;k<total;k++)
                                {
                                    if(pos_x[k]==i+1 && pos_y[k]==j)
                                    {
                                        pos_x[k]=-1;
                                        pos_y[k]=-1;
                                    }
                                }
                                --dust;
                            }
                            room[++i][j]=x;
                            step_x[step]=j-1;
                            step_y[step]=i-1;
                            step++;
                            mat[i][j]=0;
                            elec--;
                        }
                        else if(mat[i][j+1]==2) dir=right;
                        else if(mat[i][j-1]==2) dir=left;
                        else if(mat[i-1][j]==2) dir=up;
                        break;
                    }
                }
            }
            mat[i][j]=0;
            elec=battery;
            int ans_x=0,ans_y=0;
            for(int k=0;k<total;k++)
            {
                if(pos_x[k]==-1 && pos_y[k]==-1) continue;
                else
                {
                    for(int l=k+1;l<total;l++)
                    {
                        if(pos_x[l]==-1 && pos_y[l]==-1) continue;
                        else
                        {
                            if(BFS1((int **)mat,p_row,p_col,pos_x[k],pos_y[k],n,m)<BFS1((int **)mat,p_row,p_col,pos_x[l],pos_y[l],n,m))
                            {
                                ans_x=pos_x[k];
                                ans_y=pos_y[k];
                            }
                            else
                            {
                                ans_x=pos_x[l];
                                ans_y=pos_y[l];
                            }
                        }
                    }
                }
            }
            BFS(mat,p_row,p_col,ans_x,ans_y,n,m);
            while((i!=ans_x || j!=ans_y) && elec!=0)
            {
                mat[i][j]=0;
                room[p_row][p_col]='R';
                switch(dir)
                {
                case left:
                    {
                        if(mat[i][j-1]==2)
                        {
                            room[i][j]=y;
                            if(room[i][j-1]=='0')
                            {
                                for(int k=0;k<total;k++)
                                {
                                    if(pos_x[k]==i && pos_y[k]==j-1)
                                    {
                                        pos_x[k]=-1;
                                        pos_y[k]=-1;
                                    }
                                }
                                --dust;
                            }
                            room[i][--j]=x;
                            step_x[step]=j-1;
                            step_y[step]=i-1;
                            step++;
                            mat[i][j]=0;
                            elec--;
                        }
                        else if(mat[i+1][j]==2) dir=down;
                        else if(mat[i-1][j]==2) dir=up;
                        else if(mat[i][j+1]==2) dir=right;
                        break;
                    }
                case up:
                    {
                        if(mat[i-1][j]==2)
                        {
                            room[i][j]=y;
                            if(room[i-1][j]=='0')
                            {
                                for(int k=0;k<total;k++)
                                {
                                    if(pos_x[k]==i-1 && pos_y[k]==j)
                                    {
                                        pos_x[k]=-1;
                                        pos_y[k]=-1;
                                    }
                                }
                                --dust;
                            }
                            room[--i][j]=x;
                            step_x[step]=j-1;
                            step_y[step]=i-1;
                            step++;
                            mat[i][j]=0;
                            elec--;
                        }
                        else if(mat[i][j+1]==2) dir=right;
                        else if(mat[i][j-1]==2) dir=left;
                        else if(mat[i+1][j]==2) dir=down;
                        break;
                    }
                case right:
                    {
                        if(mat[i][j+1]==2)
                        {
                            room[i][j]=y;
                            if(room[i][j+1]=='0')
                            {
                                for(int k=0;k<total;k++)
                                {
                                    if(pos_x[k]==i && pos_y[k]==j+1)
                                    {
                                        pos_x[k]=-1;
                                        pos_y[k]=-1;
                                    }
                                }
                                --dust;
                            }
                            room[i][++j]=x;
                            step_x[step]=j-1;
                            step_y[step]=i-1;
                            step++;
                            mat[i][j]=0;
                            elec--;
                        }
                        else if(mat[i+1][j]==2) dir=down;
                        else if(mat[i-1][j]==2) dir=up;
                        else if(mat[i][j-1]==2) dir=left;
                        break;
                    }
                case down:
                    {
                        if(mat[i+1][j]==2)
                        {
                            room[i][j]=y;
                            if(room[i+1][j]=='0')
                            {
                                for(int k=0;k<total;k++)
                                {
                                    if(pos_x[k]==i+1 && pos_y[k]==j)
                                    {
                                        pos_x[k]=-1;
                                        pos_y[k]=-1;
                                    }
                                }
                                --dust;
                            }
                            room[++i][j]=x;
                            step_x[step]=j-1;
                            step_y[step]=i-1;
                            step++;
                            mat[i][j]=0;
                            elec--;
                        }
                        else if(mat[i][j+1]==2) dir=right;
                        else if(mat[i][j-1]==2) dir=left;
                        else if(mat[i-1][j]==2) dir=up;
                        break;
                    }
                }
            }
            en=0;
        }
    }
    BFS(mat,i,j,p_row,p_col,n,m);
    while((i!=p_row || j!=p_col) && elec!=0)
    {
        mat[i][j]=0;
        room[p_row][p_col]='R';
        switch(dir)
        {
        case left:
            {
                if(mat[i][j-1]==2)
                {
                    room[i][j]=y;
                    room[i][--j]=x;
                    step_x[step]=j-1;
                    step_y[step]=i-1;
                    step++;
                    mat[i][j]=0;
                    elec--;
                }
                else if(mat[i+1][j]==2) dir=down;
                else if(mat[i-1][j]==2) dir=up;
                else if(mat[i][j+1]==2) dir=right;
                break;
            }
        case up:
            {
                if(mat[i-1][j]==2)
                {
                    room[i][j]=y;
                    room[--i][j]=x;
                    step_x[step]=j-1;
                    step_y[step]=i-1;
                    step++;
                    mat[i][j]=0;
                    elec--;
                }
                else if(mat[i][j+1]==2) dir=right;
                else if(mat[i][j-1]==2) dir=left;
                else if(mat[i+1][j]==2) dir=down;
                break;
            }
        case right:
            {
                if(mat[i][j+1]==2)
                {
                    room[i][j]=y;
                    room[i][++j]=x;
                    step_x[step]=j-1;
                    step_y[step]=i-1;
                    step++;
                    mat[i][j]=0;
                    elec--;
                }
                else if(mat[i+1][j]==2) dir=down;
                else if(mat[i-1][j]==2) dir=up;
                else if(mat[i][j-1]==2) dir=left;
                break;
            }
        case down:
            {
                if(mat[i+1][j]==2)
                {
                    room[i][j]=y;
                    room[++i][j]=x;
                    step_x[step]=j-1;
                    step_y[step]=i-1;
                    step++;
                    mat[i][j]=0;
                    elec--;
                }
                else if(mat[i][j+1]==2) dir=right;
                else if(mat[i][j-1]==2) dir=left;
                else if(mat[i-1][j]==2) dir=up;
                break;
            }
        }
    }
    for(int a=0;a<=n+2;a++)
        delete[] mat[a];
    delete[] mat;
    infile.close();
    outfile<<step<<endl;
    for(int i=0;i<step;i++)
    {
        outfile<<step_y[i]<<" "<<step_x[i]<<endl;
    }
    outfile.close();
    return 0;
}
                      
