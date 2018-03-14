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

int nbthreads;
int n;

void merge(int *arr, int lo, int mid, int high)
{
    int size = high - lo +1;
    int* temp =(int*) malloc(sizeof(int) * size); 
    int i = lo;
    int j = mid+1;
    int k=0;
    int b;
    

    while(i<=mid && j<=high){
    if(arr[i] < arr[j])		temp[k++] = arr[i++];
	
    else if(arr[i] >= arr[j])	temp[k++] = arr[j++];   

    while(i<=mid)		temp[k++] = arr[i++];

    while(j<=high)		temp[k++] = arr[j++];
    
    int start ;
    for(start =lo; start<= high; start++)
   	arr[start] = temp[start - lo];
    free(temp);
}


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
  
  if (argc < 3) {
    std::cerr<<"Usage: "<<argv[0]<<" <n> <nbthreads>"<<std::endl;
    return -1;
  }
  n = atoi(argv[1]);
  int *arr = new int[n];
  nbthreads = atoi(argv[2]);
  omp_set_num_threads(nbthreads);
  omp_set_nested(0);

  generateMergeSortData (arr, n);
  
  //write code here
  /* sort them */
   std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();  
     
 int step;

        /* sort both halves in parallel */
        #pragma omp parallel
        {
       for(step = 2; step<= n; step = step*2){
       #pragma omp single
        {
        for(int a= 0; a<n; a = a+step){

                #pragma omp task
                {
                if((a+step) <=n)        merge(array, a, (2*a+ step-1)/2, a+step-1);
                else
                {  if((n-a)>= (step/2))
                merge(array, a , a + (step/2)-1, n-1);
                }
                }
        }
	}
	}
        }

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cerr<< elapsed_seconds.count() << "s\n";
    
     
  
  checkMergeSortResult (arr, n);
  
  delete[] arr;

  return 0;
}







