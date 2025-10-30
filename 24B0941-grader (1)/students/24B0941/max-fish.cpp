#include "max-fish.h"

////////////////////////////////////////////////////////////////////////////

// You can add more functions here
bool validate(int r,int c,int i,int j,vector<vector<int>> grid,vector<vector<bool>>  visited){
if(i>=0 && i<r && j>=0  && j<c && !visited[i][j] && grid[i][j])return true;
return false;
}
void Visit(vector<vector<int>>  grid,int i,int j,int & total,int r,int c,vector<vector<bool>> & visited){
  visited[i][j]=true;
  total+=grid[i][j];
  if(validate(r,c,i-1,j,grid,visited))Visit(grid,i-1,j,total,r,c,visited);
  if(validate(r,c,i+1,j,grid,visited))Visit(grid,i+1,j,total,r,c,visited);
  if(validate(r,c,i,j-1,grid,visited))Visit(grid,i,j-1,total,r,c,visited);
  if(validate(r,c,i,j+1,grid,visited))Visit(grid,i,j+1,total,r,c,visited);
}
////////////////////////////////////////////////////////////////////////////

// Write your code inside the findMaxFish function
int Solution::findMaxFish(vector<vector<int>> &grid)
{
  int r=grid.size();
  int c=grid[0].size();
  int result=0;
  int total;
  vector<vector<bool>> visited(r,vector<bool>(c,false));
  for(int i=0;i<r;i++){
    for(int j=0;j<c;j++){
      if(!visited[i][j] && grid[i][j]){
        total=0;
        Visit(grid,i,j,total,r,c,visited);
        result=result>total?result:total;
      }
    }
  }
  return result; //Dummy
}
