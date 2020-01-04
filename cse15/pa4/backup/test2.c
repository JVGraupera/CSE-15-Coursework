//-----------------------------------------------------------------------------
// IntegerQueueClient.c
// Test client for the IntegerQueue ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"IntegerQueue.h" 

int main(){

   int i, j;
   char* strA;
   char* strB;

   IntegerQueue A = newIntegerQueue();
   IntegerQueue B = newIntegerQueue();

   printf("A empty: %s\n", isEmpty(A)?"true":"false");
   printf("B empty: %s\n", isEmpty(B)?"true":"false");
    
   for(i = 1; i <= 50; i++){
      enqueue(A, i);
      enqueue(B, i);
   }
   
   strA = IntegerQueueToString(A);
   printf("A\n%s\n", strA);
   free(strA);
   strB = IntegerQueueToString(B);
   printf("B\n%s\n", strB);
   free(strB);
   printf("A length = %d\n", length(A));
   printf("B length = %d\n", length(B));
   
   for(i = 0; i < 50; i++){
      printf("dequeue %d from B into A\n", peek(B));
      enqueue(A, dequeue(B));
   }
   printf("A empty: %s\n", isEmpty(A)?"true":"false");
   printf("B empty: %s\n", isEmpty(B)?"true":"false");
   strA = IntegerQueueToString(A);
   printf("A\n%s\n", strA);
   free(strA);
   strB = IntegerQueueToString(B);
   printf("B\n%s\n", strB);
   printf("A length = %d\n", length(A));
   printf("B length = %d\n", length(B));
   printf("A dequeueAll\n");
   printf("A empty: %s\n", isEmpty(A)?"true":"false");
   printf("B empty: %s\n", isEmpty(B)?"true":"false");
   strA = IntegerQueueToString(A);
   printf("A\n%s\n", strA);
   free(strA);
   strB = IntegerQueueToString(B);
   printf("B\n%s\n", strB);
   printf("A length = %d\n", length(A));
   printf("B length = %d\n", length(B));
   freeIntegerQueue(&A);
   freeIntegerQueue(&B);
   return EXIT_SUCCESS;
}
   

