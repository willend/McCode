#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <assert.h>

#define min(a,b) ((a)<(b)?(a):(b))

void mergesort(double *X, int n, int *index)
{
  for(int i=0;i<n;i++) index[i] = i; /* Initialize index to 0,1,...,n */
  
  for(int step=1;step<n; step *= 2){
    for(int i=0;i<n; i+=2*step){
      int m = i+step, r = min(n,i+2*step), segment_length = r-i; /* Mid-point and right boundary */

      if(m>=r) continue;      	/* If right list is empty, sequence is already sorted */

#if TEST_SORT
      printf("Step %d:%d: Merging pre-sorted segments: [", step,i);
      for(int k=i;k<m;k++) printf("%g%s",X[k],k+1<m?", ":"] and [");
      for(int k=m;k<r;k++) printf("%g%s",X[k],k+1<r?", ":"]\n");      
#endif

      int j = 0, j0 = i, j1 = m;      
      double sorted[segment_length];
      int    sorted_index[segment_length];

      /* Merge the two adjacent sorted lists X[i:m] and X[m:r] */
      double t0 = X[j0], t1 = X[j1];
      while(j<segment_length){
	if(t0 < t1){
	  sorted_index[j] = index[j0];	  
	  sorted[j] = t0;	   /* Left element t0 is smallest, so place it */
	  if(j0+1<m) t0 = X[++j0]; /* Pick out next element in left list to place */
	  else 	     t0 = DBL_MAX; /* We're done with left list */
	} else {
	  sorted_index[j] = index[j1];	  
	  sorted[j] = t1;          /* Right element t1 is smallest, so place it */
	  if(j1+1<r) t1 = X[++j1]; /* Pick out next element in right list to place */
	  else       t1 = DBL_MAX; /* We're done with right list */
	}
	j++;
      }

#if TEST_SORT
      printf("%d'th merged segment: ",i); for(int j=0;j<segment_length;j++) printf("%g ",sorted[j]); printf("\n");
      printf("%d'th sorted_index: ",i); for(int j=0;j<segment_length;j++) printf("%d ",sorted_index[j]); printf("\n");	         
#endif
      
      for(int j=0;j<segment_length;j++){
	X[i+j] = sorted[j];
	index[i+j] = sorted_index[j];
      }
      
    } /* i-loop    */
  }   /* step-loop */
}


int main()
{
  double garbled[23] = {19,3,12,9,13,10,11,1,2,4,5,6,7,21,22,8,18,16,17,14,15,20,23};
  int    index[23];
  
  for(int i=0;i<23;i++) printf("%g ",garbled[i]); printf("\n");
  
  mergesort(garbled,23,index);

  for(int i=0;i<23;i++) printf("%g ",garbled[i]); printf("\n");
  for(int i=0;i<23;i++) printf("%d ",index[i]); printf("\n");  

  return 0;
}
