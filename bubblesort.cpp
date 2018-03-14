#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <chrono>

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

#ifdef __cplusplus
extern "C" {
#endif

	void generateMergeSortData (int* arr, size_t n);
  	void checkMergeSortResult (int* arr, size_t n);
#ifdef __cplusplus
}
#endif

int main (int argc, char* argv[]) {
int n,nbthreads;
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
  
  if (argc < 3) {
    std::cerr<<"Usage: "<<argv[0]<<" <n> <nbthreads>"<<std::endl;
    return -1;
  }
  
  n = atoi(argv[1]);
  nbthreads = atoi(argv[2]);
  int* arr = new int[n];
  generateMergeSortData (arr, n);
  int *array = new int[n];
  for(int i=0; i<n;i++)		array[i]= arr[i];
  int granularity = atoi(argv[3]);
  int temp;
  omp_set_num_threads(nbthreads);  
  omp_set_schedule(omp_sched_dynamic,granularity);

  //Sequential code and time
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    
  bubbleSort(array, n);
  
  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start;
  
  std::cerr<<elapsed_seconds.count()<<std::endl;

  checkMergeSortResult(array,n);
  //write code here
  std::chrono::time_point<std::chrono::system_clock> start1, end1;
  start1 = std::chrono::system_clock::now();  
  
  for(int i =0; i<n-1; i++){
  #pragma omp parallel for schedule(runtime) private(temp)
	for(int j =0; j <n-1; j= j+2){
 	if(arr[j] > arr[j+1]){
	temp = arr[j+1];
	arr[j+1] = arr[j];
	arr[j] = temp;	
	}     	
	}
  #pragma omp parallel for schedule(runtime) private(temp)
	for(int j = 1; j<n-1; j = j+2){
	if(arr[j] > arr[j+1]){
	temp = arr[j+1];
	arr[j+1] = arr[j];
	arr[j] = temp;
	}  	
	}
  }
 

  end1 = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds1 = end1-start1;
  std::cerr<< elapsed_seconds1.count() << "s\n";
  
  checkMergeSortResult (arr, n);
  delete[] arr;
  delete[] array;
return 0;
}
 
