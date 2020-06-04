#include <iostream>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#define N 4
#define M 7
static int c=0; 
static int block=1;
static int check=0;

bool validCell(int, int);											// Check if cell (x, y) is valid or not
void countPaths(int[N][M], int, int, int[N][M]);
void printPath(int[N][M]);

int main(){

	char maze[N][M] =  {{'s','1','1','1','1','1','0'},
						{'1','0','0','1','1','0','1'},
						{'1','0','0','0','1','0','1'},
						{'1','1','1','e','1','1','1'}};
	
	int Maze[N][M];
	memset(Maze, 0, sizeof Maze);
	
	for(int i=0;i<N;i++){								//converting input array from char to int
		for(int j=0;j<M;j++){
			if(maze[i][j] == 's'){
				Maze[i][j]=3; 
			}
			else if(maze[i][j] == 'e'){
				Maze[i][j]=4;
			}
			else{
				Maze[i][j]=(char)maze[i][j];
				if(Maze[i][j] == 49){
					Maze[i][j]=1;
				}
				else{
					Maze[i][j]=0;
				}
			}
		}
	}
	int x,y;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(Maze[i][j] == 3){
				x=i;
				y=j;	
			}
		}
	}
	
	int visited[N][M];										// 2D matrix to keep track of cells involved in current path
	memset(visited, 0, sizeof visited);
	
	countPaths(Maze, x, y, visited);
	
	if(!check){
		cout<<"No Paths Found!";
	}
	return 0;
}

bool validCell(int x, int y){
	if (x < 0 || y < 0 || x >= N || y >= M)
		return false;

	return true;
}

void printPath(int alreadyVisited[N][M]){
	int cost=0;	
	vector<int> temp;
	
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(alreadyVisited[i][j]!=0){
				temp.push_back(alreadyVisited[i][j]);
			}
		}
	}
	
	sort(temp.begin(),temp.end());
	
	cout<<"Path#"<<c++<<" = {";	
	for(int i=0;i<temp.size();i++){
		for(int j=0;j<N;j++){
			for(int k=0;k<M;k++){
				if(temp[i] == alreadyVisited[j][k]){
					cout<<"("<<j<<","<<k<<")";
					cost++;
				}
			}
		}
	}
	cout<<"}  "<<"Cost="<<--cost;
	cout<<endl;
}

void countPaths(int maze[N][M], int x, int y, int alreadyVisited[N][M]){
	
	int a,b;
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(maze[i][j] == 4){
				a=i;
				b=j;	
			}
		}
	}
	
	if (maze[x][y] == 4){ 								// if destination (bottom-rightmost cell) is found, increment the path count	
		alreadyVisited[x][y] = 999;
		printPath(alreadyVisited);
		block=1;	
		check++;
		//return;
	}

	alreadyVisited[x][y] = block++;							// mark current cell as visited
	
	
	if (validCell(x, y) && maze[x][y]){ 			// if current cell is a valid and open cell, 
	
		
		if (x + 1 < N && !alreadyVisited[x + 1][y])           //go down
			countPaths(maze, x + 1, y, alreadyVisited);
			
	
		if (x - 1 >= 0 && !alreadyVisited[x - 1][y])		  //go up
			countPaths(maze, x - 1, y, alreadyVisited);
			
		
		if (y + 1 < M && !alreadyVisited[x][y + 1])			//go right
			countPaths(maze, x, y + 1, alreadyVisited);
			
	
		if (y - 1 >= 0 && !alreadyVisited[x][y - 1])		//go left
			countPaths(maze, x, y - 1, alreadyVisited);
	}
	
	
	alreadyVisited[x][y] = 0;				// backtrack from current cell and remove it from current path
}
