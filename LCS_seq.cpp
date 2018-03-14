#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <string>
#include <chrono>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

int  max(int a, int b){
if(a>b)	return a;
else if(a<=b)	return b;
}

int m,n;

int indexOf(int a, int b){
int x= a * n + b;
return a;
}

int main (int argc, char* argv[]) {

  
  if (argc < 1) {
    std::cerr<<"Usage: "<<argv[0]<<""<<std::endl;
    return -1;
  }
 
  m = 9999;
  n = 100000;
  char q[] = "qwertycd";
  char r[] = "boomcd";
  //char* ar;
  char ar[10000]; // = new char[80001];
  //char* br;
  char br[100001];// = new char[90001];
  
  for(int i=0; i<m ; i++)	ar[i]= q[i%8];
  for(int i=0; i<n ; i++)	br[i]= r[i%6]; 

  int* C;
  C = new int[(unsigned int)10000 * 100001];
  //int C[m+1][n+1];
  //write code here
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();  
     
  
  for(int i =0; i<=m; i++)	C[indexOf(i,0)] = 0;
  for(int j=0; j<=n; j++)	C[indexOf(0,j)] = 0;
  for(int a=1; a<=m; a++){
	for(int b =1; b<=n ;b++){
	if(ar[a-1] == br[b-1]){
	C[indexOf(a,b)] = C[indexOf(a-1,b-1)] +1;
 	}
	else {
	C[indexOf(a,b)] = max(C[indexOf(a,b-1)], C[indexOf(a-1,b)]);
	}
	}
	}  

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cerr<< elapsed_seconds.count() << "s\n";
  
  std::cout<<C[indexOf(m,n)]<<std::endl;
    
delete[] C; 
//delete[] ar;
//delete[] br;
  
return 0;
}
 
