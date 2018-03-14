#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
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

int *C = new int[(unsigned int) 10000 * 100001];


int m, n;
int indexOf(int x, int y){
int a = x*n + y;
return a;
}

int  max(int a, int b){
if(a>b)	return a;
else if(a<=b)	return b;
}

  std::chrono::time_point<std::chrono::system_clock> start, end;

int main (int argc, char* argv[]) {

  //forces openmp to create the threads beforehand

#pragma omp parallel
  {
    int fd = open (argv[0], O_RDONLY);
    if (fd != -1) {
      close (fd);
    }
    else {
      std::cerr<<"something is amiss"<<std::endl;
    }
  }
  
 if (argc < 2) {
   std::cerr<<"Usage: "<<argv[0]<<" <granularity>"<<std::endl;
   return -1;
  }
  
  omp_set_num_threads(16);
  int gran = atoi(argv[1]);
  omp_set_schedule(omp_sched_dynamic, gran);
  m = 9999;
  n = 100000;
  int p = m+n;
  char q[] = "qwertycd";
  char r[] = "boomcd";
  //char* ar;
  //ar = new char[m+1];
  char ar[10000];
  //char* br;
  //br = new char[n+1];  
  char br[100001];
  
  for(int i=0; i<m ; i++)	ar[i]= q[i%8];
  for(int i=0; i<n ; i++)	br[i]= r[i%6]; 

  //int *C;
//  C = new int[(unsigned int) 60001 * 80001];
  //write code here
  start = std::chrono::system_clock::now();
  
  #pragma omp parallel 
  {
  #pragma omp for schedule(runtime)
  for(int i =0; i<=m; i++)	C[indexOf(i,0)] = 0;
  }  
  #pragma omp parallel
  {
  #pragma omp for schedule(runtime) 
  for(int j=0; j<=n; j++)	C[indexOf(0,j)] = 0;
  }

  for(int sum = 2 ; sum<=p ; sum++){
  #pragma omp parallel 
  {

  #pragma omp for schedule(runtime) 
  for(int j = 1; j< sum; j++){
  if((j<=m)&&(sum-j<=n)){
  if(ar[j-1] == br[sum-j-1]){
	C[(j*n) +sum-j] = C[(j-1)*n + sum-j-1] +1;
 	}
	else {
	C[(j*n)+sum-j] = max(C[(j*n)+sum-j-1], C[(j-1)*n +sum-j]);
	}
  }
  }
  }
  }  
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cerr<< elapsed_seconds.count() << "s\n";
  std::cout<< C[indexOf(m,n)]<<std::endl;



  delete[] C;
  //delete[] ar,
//  delete[] br;
return 0;
}
 
