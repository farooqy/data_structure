#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include <stdbool.h>
#define N 8
typedef struct node//when use radix sort,data should be saved in list, this is node define of the list 
{
	int data;
	struct node *next;
}LI;

void mergerSort(int *list, int size);
void mergeLR(int *A, int *L, int leftSize, int *R, int rightSize);
void getData(int *a);
void showData(int *a);
void quickSort( int a[], int l, int r);
int partition( int a[], int l, int r) ;
void heapSort(int A[], int n);
void BuildMaxHeap(int A[], int n);
void MaxHeapify(int A[], int n, int i);
void radixSort(int * array, int size);
int findLargestNum(int * array, int size);
void swap(int* x, int* y);
int main()
{
  int L[N];
  printf("MERGE SORT\n");
  getData(L);
	clock_t t;
	t = clock();
  mergerSort(L,N );
	t =  clock()-t;
	double time_taken = ((double) t)/CLOCKS_PER_SEC;
  showData(L);
	printf("IT TOOK %f SECONDS TO SORT USING MERGE\n",time_taken);
  
  printf("\nQUICK SORT\n");
  getData(L);
	t = clock();
  quickSort(L, 0, N-1);
	t =  clock()-t;
	time_taken = ((double) t)/CLOCKS_PER_SEC;
  showData(L);
	printf("IT TOOK %f SECONDS TO SORT USING QUICK SORT\n",time_taken);
	
  int M[N];
  printf("\nHEAP SORT\n");
  getData(M);
	t = clock();
  heapSort(M, N);
	t =  clock()-t;
	time_taken = ((double) t)/CLOCKS_PER_SEC;
  showData(L);
	printf("IT TOOK %f SECONDS TO SORT USING HEAP SORT\n",time_taken);
  
  int RAD[N];
  printf("\nRADIX SORT\n");
  getData(RAD);
	t = clock();
  radixSort(RAD, N);
	t =  clock()-t;
	time_taken = ((double) t)/CLOCKS_PER_SEC;
  showData(L);
	printf("IT TOOK %f SECONDS TO SORT USING RADIX SORT\n",time_taken);
}
int findLargestNum(int * array, int size)
{
  
  int i;
  int largestNum = -1;
  
  for(i = 0; i < size; i++){
    if(array[i] > largestNum)
      largestNum = array[i];
  }
  
  return largestNum;
}

// Radix Sort
void radixSort(int * array, int size)
{
  
  //printf("\n\nRunning Radix Sort on Unsorted List!\n\n");

  // Base 10 is used
  int i;
  int semiSorted[size];
  int significantDigit = 1;
  int largestNum = findLargestNum(array, size);
  
  // Loop until we reach the largest significant digit
  while (largestNum / significantDigit > 0){
    
    //printf("\tSorting: %d's place ", significantDigit);
    //printArray(array, size);
    
    int bucket[10] = { 0 };
    
    // Counts the number of "keys" or digits that will go into each bucket
    for (i = 0; i < size; i++)
      bucket[(array[i] / significantDigit) % 10]++;
    
    /**
     * Add the count of the previous buckets,
     * Acquires the indexes after the end of each bucket location in the array
		 * Works similar to the count sort algorithm
     **/
    for (i = 1; i < 10; i++)
      bucket[i] += bucket[i - 1];
    
    // Use the bucket to fill a "semiSorted" array
    for (i = size - 1; i >= 0; i--)
      semiSorted[--bucket[(array[i] / significantDigit) % 10]] = array[i];
    
    
    for (i = 0; i < size; i++)
      array[i] = semiSorted[i];
    
    // Move to next significant digit
    significantDigit *= 10;
    
    //printf("\n\tBucket: ");
    //printArray(bucket, 10);
  }
}
void MaxHeapify(int *A, int n, int i)
{
    int largest = i;  // Initialize largest as root
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right  = 2*i + 2
  
    // If left child is larger than root
    if (l < n && A[l] > A[largest])
        largest = l;
    // If right child is larger than largest so far
    if (r < n && A[r] > A[largest])
        largest = r;
  
    // If largest is not root
    if (largest != i)
    {
        //swap A[i] with A[largest]
        swap(&A[i], &A[largest]);
        // Recursively Max-Heapify the affected sub-tree
        MaxHeapify(A, n, largest);
    }
}
  
// Build-Max-Heap (rearrange array)
//Converting array A to Max-Heap
void BuildMaxHeap(int *A, int n)
{
    int i;
    for (i=(n/2)-1;i>=0;i--){
        MaxHeapify(A, n, i);
        }
}
// main function to do Heap Sort
void heapSort(int *A, int n)
{
    int i;
    BuildMaxHeap(A, n);
    // One by one extract an element from heap
    //and get the sorted array
    for (i=n-1; i>=0; i--)
    {
        // Move top root element to end element
        swap(&A[0], &A[i]);
        //And reduce size of heap
        int heap_size= i;
        // call max heapify on the reduced heap
        MaxHeapify(A, heap_size, 0);
    }
}
  
/*  function to print an array */
void getData(int *a)
{
	int i;
	srand(time(0));
  printf("RANDOM DATA IS: ");
	for(i=0;i<N;i++)
  {a[i]=rand()%100; printf("%d ",a[i]);}
  printf("\n");
}
void showData(int *a)
{
  int i;
  printf("SORTED DATA: ");
  for(i =0; i<N; i++)
    printf("%d ",a[i]);
  printf("\n");
}
void quickSort( int a[], int l, int r)
{
   int j;
   if( l < r ) 
   {
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
}
int partition( int a[], int l, int r)
{
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
   while( 1)
   {
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}
void mergerSort(int *list, int size)
{
  int middle_index = size /2;
  if(size < 2) return;
  
  int *left_part = malloc(sizeof(int));
  int *right_part = malloc(sizeof(int));
  int i =0;
  for(i; i<middle_index; i++)
    left_part[i] = list[i];
  for(i=middle_index; i<size; i++)
    right_part[i-middle_index] = list[i];
  
  mergerSort(left_part, middle_index);
  mergerSort(right_part,size-middle_index);
  mergeLR(list, left_part, middle_index, right_part, size-middle_index);
  free(left_part);
  free(right_part);
}
void mergeLR(int *A, int *L, int leftSize, int *R, int rightSize)
{
  int i,j,k;
  i =0; j=0; k=0;
  while(i<leftSize && j <rightSize)
  {
    if(L[i] < R[j]) A[k++] = L[i++];
    else A[k++] =  R[j++];
  }
  while(i < leftSize) A[k++] = L[i++];
  while(j < rightSize) A[k++] = R[j++];
}
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
