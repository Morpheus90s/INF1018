#include <stdio.h>
void foo (int a[], int n);

int main (void) {
   int arr[5] = {1, 2, 0, 4, 0};
   foo(arr, 5);
   
   for(int i = 0; i < 5; i++) {
       printf("%d ", arr[i]);
   }
   printf("\n");
   return 0;
}
