CFLAGS=-O3 -std=c11 -g -fopenmp
CXXFLAGS=-O3 -std=c++11 -g -fopenmp
LDFLAGS=-fopenmp
ARCHIVES=libintegrate.a libfunctions.a libgen.a 
LD=g++

all: reduce mergesort bubblesort_seq bubblesort LCS_seq LCS

reduce: reduce.o
	$(LD) $(LDFLAGS) reduce.o $(ARCHIVES) -o reduce

mergesort: mergesort.o
	$(LD) $(LDFLAGS) mergesort.o $(ARCHIVES) -o mergesort

bubblesort_seq: bubblesort_seq.o
	$(LD) $(LDFLAGS) bubblesort_seq.o $(ARCHIVES) -o bubblesort_seq	

bubblesort: bubblesort.o
	$(LD) $(LDFLAGS) bubblesort.o $(ARCHIVES) -o bubblesort	

LCS_seq: LCS_seq.o
	$(LD) $(LDFLAGS) LCS_seq.o $(ARCHIVES) -o LCS_seq	

LCS: LCS.o
	$(LD) $(LDFLAGS) LCS.o $(ARCHIVES) -o LCS	


libfunctions.a: functions.o
	ar rcs libfunctions.a functions.o

libintegrate.a: sequential_lib.o
	ar rcs libintegrate.a sequential_lib.o

libgen.a: gen_lib.o
	ar rcs libgen.a gen_lib.o

test_reduce: reduce
	./test_reduce.sh




clean:
	-rm *.o

