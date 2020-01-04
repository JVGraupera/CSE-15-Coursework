#include<stdio.h>
#include<stdlib.h>
#include"IntegerQueue.h" 

int main(){

   int i, j;
   char* strA;
   char* strB;

   IntegerQueue A = newIntegerQueue();
   IntegerQueue B = newIntegerQueue();

   printf("%s\n", isEmpty(A)?"true":"false");
   printf("%s\n", isEmpty(B)?"true":"false");

   enqueue(A, 5);
   enqueue(A, 3);
   enqueue(A, 9);
   enqueue(A, 7);
   enqueue(A, 8);

   printf("%s\n", isEmpty(A)?"true":"false");

   strA = IntegerQueueToString(A);
   printf("%s\n", strA);
   free(strA);

   printf("%d\n", peek(A));
   dequeue(A);
   printf("length A = %d\n", length(A));
   dequeue(A);
   dequeue(A);
   printf("%d\n", peek(A));

   strA = IntegerQueueToString(A);
   printf("%s\n", strA);
   free(strA);

   enqueue(B, 7);
   enqueue(B, 8);

   strB = IntegerQueueToString(B);
   printf("%s\n", strB);
   free(strB);

   printf("%s\n", equals(A, B)?"true":"false");

   enqueue(A, 12);
   enqueue(B, 13);

   strA = IntegerQueueToString(A);
   printf("%s\n", strA);
   free(strA);

   strB = IntegerQueueToString(B);
   printf("%s\n", strB);
   free(strB);

   printf("%s\n", equals(A, B)?"true":"false");
   
   //printf("length A = %d\n", length(A));
   dequeueAll(A);
   //printf("length A = %d\n", length(A));
   dequeueAll(B);
   printf("%s\n", isEmpty(A)?"true":"false");
   printf("%s\n", isEmpty(B)?"true":"false");

   freeIntegerQueue(&A);
   freeIntegerQueue(&B);

   A = newIntegerQueue();
   B = newIntegerQueue();

   for(i=0; i<10; i++){
      enqueue(A, i);
   }

   strA = IntegerQueueToString(A);
   strB = IntegerQueueToString(B);
   printf("A: %s\n", strA);
   printf("B: %s\n", strB);
   free(strA);
   free(strB);
   i = 0;
   while( !isEmpty(A)){
      j = dequeue(A);
     // printf("%d\n", j);
      enqueue(B, j);
      //printf("A: %s\n", strA);
      //printf("B: %s\n", strB);
      if( j%3==0 ){
         j = dequeue(B);
         enqueue(A, j);
      }
      strA = IntegerQueueToString(A);
      strB = IntegerQueueToString(B);
      printf("A: %s\n", strA);
      printf("B: %s\n", strB);
      free(strA);
      free(strB);
      i++;
   }

   freeIntegerQueue(&A);
   freeIntegerQueue(&B);

   return EXIT_SUCCESS;
}
