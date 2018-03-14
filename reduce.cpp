#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>


#ifdef __cplusplus
extern "C" {
#endif

  void generateReduceData (int* arr, size_t n);
  
#ifdef __cplusplus
}
#endif


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
    std::cerr<<"Usage: "<<argv[0]<<std::endl;
    return -1;
  }

  int n = atoi(argv[1]);
  int *arr = new int[n];
  //omp_set_nested(1);	// Enables nested parallelism.
  generateReduceData (arr, atoi(argv[1]));
  omp_set_num_threads(16);
  omp_set_schedule(omp_sched_dynamic, 1000);
  int result_seq =0;
  int result=0;
  
  std::chrono::time_point<std::chrono::system_clock> start1, end1;
  start1 = std::chrono::system_clock::now();
  for(int i =0; i<n; i++){
  result_seq = result_seq + arr[i];
  }
  end1 = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds1 = end1-start1;
  std::cerr<< elapsed_seconds1.count() << "s\n";



  //write code here
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  #pragma omp parallel
  {
  #pragma omp for reduction(+:result) schedule(runtime)
  for (int i=0;i<atoi(argv[1]);i++) 
  {
   #pragma omp task
 		result=result+arr[i];
  }
  }
   
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;
  std::cerr<< elapsed_seconds.count() << "s\n";
  std::cout <<result<< std::endl;

  
  delete[] arr;

  return 0;
}
