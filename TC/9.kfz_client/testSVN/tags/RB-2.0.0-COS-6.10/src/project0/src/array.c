#include <stdio.h>

#define MAX 16

void accept_input(int *arr, int n) {
   int i;
   for (i = 0; i < n; ++i) 
   scanf("%d", &arr[i]);
}

void display(int *arr, int n) {
   int i;
   for (i = 0; i < n; ++i) 
   printf("|%d| ", arr[i]);

   printf("\n");
}

int main(void) {
   int i, n, arr[MAX];

   printf("Enter the total number of elements: ");
   scanf("%d", &n);

   /* handle array overflow condition */
   if (n > MAX) {
      fprintf(stderr, "Number of elements must be less than %d\n", MAX);
      return 1;
   }

   printf("Enter the elements\n");
   accept_input(arr, n);

   printf("Array has following elements\n");
   display(arr, n);

   return 0;
}
//第一个里测试里程碑，从主干打分支，在分支上开发后提交，在主干上合并该分支，删除该分支，再从主干上打标签 RB-2.0.0-COS-6.10
