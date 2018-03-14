#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <stdlib.h>
#include <chrono>

#ifdef __cplusplus
extern "C" {
#endif

  void generateMergeSortData (int* arr, size_t n);
  void checkMergeSortResult (int* arr, size_t n);

  
#ifdef __cplusplus
}
#endif



void bubbleSort(int *a, int n){

	for(int i=0; i<n;i++){
	for(int j=0; j<n;j++){
 	if(a[j] < a[j-1]){
	int temp = a[j-1];
	a[j-1] = a[j];
	a[j] = temp;
	}	
	}
}
}

int main (int argc, char* argv[]) {

  if (argc < 2) {
    std::cerr<<"usage: "<<argv[0]<<" <n>"<<std::endl;
    return -1;
  }
  
  int n = atoi(argv[1]);
  int *arr = new int[n];
  generateMergeSortData(arr, atoi(argv[1]));
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    
  bubbleSort(arr, n);
  
  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start;
  
  std::cerr<<elapsed_seconds.count()<<std::endl;

  checkMergeSortResult(arr, n);
  
  return 0;
}
